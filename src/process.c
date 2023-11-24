/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   process.c                                       :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/11/16 01:37:20 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/25 00:05:26 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "strace.h"


static void	wait_signal(pid_t child, int *status, bool is_ret)
{
	waitpid(child, status, 0);
	if (WIFEXITED(*status)) {
		if (is_ret)
			dprintf(2, " = ?\n");
		dprintf(2, "+++ exited with %d +++\n", WEXITSTATUS(*status));
		exit(WEXITSTATUS(*status));
	} else if (WIFSIGNALED(*status)) {
		dprintf(2, "+++ killed by %s +++\n\n", find_signal(WTERMSIG(*status)));
		exit(WTERMSIG(*status));
	} else if (WIFSTOPPED(*status)) {
		if (WSTOPSIG(*status) == SIGTRAP)
			return;
		print_signal_struct(child);
		exit(WSTOPSIG(*status) + 128);
	}
}


static void	next_syscall(pid_t child)
{
	if (ptrace(PTRACE_SYSCALL, child, NULL, NULL) < 0) {
		perror("ft_strace: ptrace PTRACE_SYSCALL");
		exit(1);
	}
}


static struct syscall_s	find_syscall(uint32_t orig_eax,
	struct syscall_s syscall64[], struct syscall_s syscall32[])
{
	char	*to_find = syscall32[orig_eax].name;
	int i = 0;

	for (i = 0; i < NB_SYSCALL_64; i++) {
		if (strcmp(to_find, syscall64[i].name) == 0)
			return syscall64[i];
	}
	return syscall32[orig_eax];
}


static void	getregset(bool is_ret, pid_t child, void *regs,
	struct iovec *iov, struct syscall_s syscall64[], struct syscall_s syscall32[])
{
	if (ptrace(PTRACE_GETREGSET, child, NT_PRSTATUS, iov) < 0) {
		perror("ft_strace: ptrace PTRACE_GETREGSET");
		exit(1);
	}
	if (iov->iov_len == sizeof(struct user_regs_struct32)) {
		if ((*(struct user_regs_struct32 *)regs).orig_eax >= NB_SYSCALL_32)
			return;
		print_syscall32(
			find_syscall(
				(*(struct user_regs_struct32 *)regs).orig_eax,
				syscall64,
				syscall32
			),
			regs,
			child,
			is_ret
		);
	} else {
		if ((*(struct user_regs_struct64 *)regs).orig_rax >= NB_SYSCALL_64)
			return;
		print_syscall64(
			syscall64[(*(struct user_regs_struct64 *)regs).orig_rax],
			regs,
			child,
			is_ret
		);
	}
}


static void	loop(pid_t child)
{
	int							status;
	struct iovec				iov;
	struct user_regs_struct64	regs;
	struct syscall_s			syscall64[] = SYSCALL_64;
	struct syscall_s			syscall32[] = SYSCALL_32;

	iov.iov_base = &regs;
	iov.iov_len = sizeof(regs);
	wait_signal(child, &status, false);
	while (1) {
		next_syscall(child);
		wait_signal(child, &status, false);
		getregset(false, child, &regs, &iov, syscall64, syscall32);
		next_syscall(child);
		wait_signal(child, &status, true);
		getregset(true, child, &regs, &iov, syscall64, syscall32);
	}
}


void	process(pid_t child)
{
	if (ptrace(PTRACE_SEIZE, child, NULL, NULL, PTRACE_O_TRACEEXEC) < 0) {
		perror("ft_strace: ptrace PTRACE_SEIZE");
		exit(1);
	}
	if (ptrace(PTRACE_INTERRUPT, child, NULL, NULL, NULL) < 0) {
		perror("ft_strace: ptrace PTRACE_INTERRUPT");
		exit(1);
	}
	block_signals();
	loop(child);
}
