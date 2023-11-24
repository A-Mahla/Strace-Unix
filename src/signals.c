/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   signals.c                                       :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/11/23 22:41:41 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/24 12:28:23 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "strace.h"


char	*find_signal(int signal)
{
	static char	*signals[] = SYS_SIGNAME;

	for (int i = 0; i < SYS_SIGNAME_COUNT; i++) {
		if (i == signal)
			return signals[i];
	}
	return NULL;
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

	if (signal == SIGILL)
		si_codes = ill_si_codes;
	else if (signal == SIGFPE)
		si_codes = fpe_si_codes;
	else if (signal == SIGSEGV)
		si_codes = segv_si_codes;
	else if (signal == SIGBUS)
		si_codes = bus_si_codes;
	else if (signal == SIGTRAP)
		si_codes = trap_si_codes;
	else if (signal == SIGCHLD)
		si_codes = cld_si_codes;
	else if (signal == SIGPOLL)
		si_codes = poll_si_codes;
	for (int i = 0; si_codes[i].name; i++) {
		if ((int)si_codes[i].flag == si_code)
			return si_codes[i].name;
	}
	return NULL;
}


void	block_signals(void)
{
	sigset_t	signal_mask;

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
	sigset_t	signal_mask;

	sigemptyset(&signal_mask);
	sigprocmask(SIG_SETMASK, &signal_mask, NULL);
}


void	print_signal_struct(pid_t child)
{
	siginfo_t	sig;
	char		*signame;

	if (ptrace(PTRACE_GETSIGINFO, child, 0, &sig) < 0) {
		perror("ft_strace: ptrace PTRACE_SYSCALL");
		exit(1);
	}
	signame = find_signal(sig.si_signo);
	if (sig.si_code == SI_TKILL) {
		dprintf(2, "--- %1$s {si_signo=%1$s, si_code=%2$s, si_pid=%3$d, si_uid=%4$d} ---\n",
			signame, find_sicode(sig.si_signo, sig.si_code), sig.si_pid, sig.si_uid);
		dprintf(1, "+++ killed by %1$s +++\n", signame);
	} else {
		dprintf(1, "strace: Process %d detached\n", child);
	}
}
