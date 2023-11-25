/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   signals.c                                       :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/11/23 22:41:41 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/25 03:33:09 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "strace.h"


static sigset_t	signal_mask;


char	*find_signal(int signal)
{
	static char	*signals[] = SYS_SIGNAME;

	for (int i = 0; i < SYS_SIGNAME_COUNT; i++) {
		if (i == signal)
			return signals[i];
	}
	return "SIGRT_2";
}


const char	*find_sicode(int signal, int si_code)
{
	 static struct type_flag	default_si_codes[] = SI_CODE;
	 static struct type_flag	ill_si_codes[] = ILL_SI_CODE;
	 static struct type_flag	fpe_si_codes[] = FPE_SI_CODE;
	 static struct type_flag	segv_si_codes[] = SEGV_SI_CODE;
	 static struct type_flag	bus_si_codes[] = BUS_SI_CODE;
	 static struct type_flag	trap_si_codes[] = TRAP_SI_CODE;
	 static struct type_flag	cld_si_codes[] = CLD_SI_CODE;
	 static struct type_flag	poll_si_codes[] = POLL_SI_CODE;
	 struct type_flag			*si_codes = default_si_codes;

	if (signal == SIGILL && si_code > 0)
		si_codes = ill_si_codes;
	else if (signal == SIGFPE && si_code > 0)
		si_codes = fpe_si_codes;
	else if (signal == SIGSEGV && si_code > 0)
		si_codes = segv_si_codes;
	else if (signal == SIGBUS && si_code > 0)
		si_codes = bus_si_codes;
	else if (signal == SIGTRAP && si_code > 0)
		si_codes = trap_si_codes;
	else if (signal == SIGCHLD && si_code > 0)
		si_codes = cld_si_codes;
	else if (signal == SIGPOLL && si_code > 0)
		si_codes = poll_si_codes;
	for (int i = 0; si_codes[i].name; i++) {
		if ((int)si_codes[i].flag == si_code)
			return si_codes[i].name;
	}
	return NULL;
}


void	block_signals(void)
{
	sigemptyset(&signal_mask);
	sigaddset(&signal_mask, SIGINT);
	sigaddset(&signal_mask, SIGTERM);
	sigaddset(&signal_mask, SIGQUIT);
	sigaddset(&signal_mask, SIGTSTP);
	sigaddset(&signal_mask, SIGTTIN);
	sigaddset(&signal_mask, SIGCHLD);
	sigaddset(&signal_mask, SIGHUP);
	sigaddset(&signal_mask, SIGPIPE);
	sigaddset(&signal_mask, SIGALRM);
	sigaddset(&signal_mask, SIGUSR1);
	sigaddset(&signal_mask, SIGUSR2);
	sigaddset(&signal_mask, SIGCONT);
	sigaddset(&signal_mask, SIGSTOP);
	sigaddset(&signal_mask, SIGKILL);
	sigaddset(&signal_mask, SIGWINCH);
	sigprocmask(SIG_SETMASK, &signal_mask, NULL);
}


void	unblock_signals(void)
{
	sigemptyset(&signal_mask);
	sigprocmask(SIG_SETMASK, &signal_mask, NULL);
}


void	stopped_process(pid_t child, bool is_ret)
{
	int	status;

	next_syscall(child);
	wait_signal(child, &status, is_ret);
}


void	print_signal_struct(siginfo_t sig, char *signame)
{
	dprintf(2, "--- %1$s {si_signo=%1$s, si_code=%2$s, ",
		signame, find_sicode(sig.si_signo, sig.si_code));
	if (sig.si_signo == SIGSEGV && sig.si_code > 0)
		dprintf(2, "si_addr=%p} ---\n", sig.si_addr);
	else if (sig.si_signo == SIGCHLD && sig.si_code > 0)
		dprintf(2, "si_status=%d, si_utime=%ld, si_stime=%ld} ---\n",
			sig.si_status, sig.si_utime, sig.si_stime);
	else
		dprintf(2, "si_pid=%d, si_uid=%d} ---\n", sig.si_pid, sig.si_uid);
	if (sig.si_signo == SIGSTOP || sig.si_signo == SIGTSTP
		|| sig.si_signo == SIGTTIN)
		dprintf(1, "+++ stopped by %s +++\n", signame);
	else if (sig.si_signo != SIGCHLD && sig.si_signo != SIGCONT
		&& sig.si_signo != SIGURG && sig.si_signo != SIGWINCH)
		dprintf(1, "+++ killed by %s +++\n", signame);
}


void	print_signal(pid_t child, int status, bool is_ret)
{
	siginfo_t	sig;
	char		*signame;

	if (WTERMSIG(status) == SIGKILL) {
		if (is_ret)
			dprintf(2, " = ?\n");
		dprintf(1, "+++ killed by SIGKILL +++\n");
		unblock_signals();
		raise(WTERMSIG(status));
	} else if (ptrace(PTRACE_GETSIGINFO, child, 0, &sig) < 0) {
		perror("ft_strace: ptrace PTRACE_GETSIGINFO");
		exit(1);
	}
	signame = find_signal(sig.si_signo);
	if (sig.si_signo == SIGTRAP && sig.si_code == 5)
		return;
	if (is_ret)
		dprintf(2, " = ?\n");
	if (sig.si_code == SI_KERNEL)
		dprintf(1, "strace: Process %d detached\n", child);
	else
		print_signal_struct(sig, signame);
	unblock_signals();
	if (sig.si_signo != SIGCHLD && sig.si_signo != SIGCONT
		&& sig.si_signo != SIGURG && sig.si_signo != SIGWINCH)
		raise(sig.si_signo);
	else
		stopped_process(child, is_ret);
}
