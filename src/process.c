/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   process.c                                       :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/11/16 01:37:20 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/20 03:48:47 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "strace.h"


static int8_t	wait_signal(pid_t child, int *status)
{
	waitpid(child, status, 0);
	if (WIFEXITED(*status) || WIFSIGNALED(*status))
		return EXITED;
	return SUCCESS;
}


static void	next_syscall(pid_t child)
{
	if (ptrace(PTRACE_SYSCALL, child, NULL, NULL) < 0) {
		perror("ft_strace: ptrace PTRACE_SYSCALL");
		exit(1);
	}
}


static void	getregset(bool is_ret, pid_t child, void *regs, uint8_t arch,
	struct iovec *iov, struct syscall_s syscall[])
{

	if (ptrace(PTRACE_GETREGSET, child, NT_PRSTATUS, iov) < 0) {
		perror("ft_strace: ptrace PTRACE_GETREGSET");
		exit(1);
	}
	if (arch == ELFCLASS32) {
		print_syscall32(
			syscall[(*(struct user_regs_struct32 *)regs).orig_eax],
			regs,
			child,
			is_ret
		);
	} else {
		print_syscall64(
			syscall[(*(struct user_regs_struct64 *)regs).orig_rax],
			regs,
			child,
			is_ret
		);
	}
}


static void	loop64(pid_t child, uint8_t arch)
{
	int							status;
	struct iovec				iov;
	struct user_regs_struct64	regs_64;
	struct syscall_s			syscall64[] = SYSCALL_64;

	iov.iov_base = &regs_64;
	iov.iov_len = sizeof(regs_64);
	if (wait_signal(child, &status) == EXITED)
		return;
	while (1) {
		next_syscall(child);
		if (wait_signal(child, &status) == EXITED)
            break;
		getregset(0, child, &regs_64, arch, &iov, syscall64);
		next_syscall(child);
		if (wait_signal(child, &status) == EXITED)
            break;
		getregset(1, child, &regs_64, arch, &iov, syscall64);
	}
}


static void	loop32(pid_t child, uint8_t arch)
{
	int							status;
	struct iovec				iov;
	struct user_regs_struct32	regs_32;
	struct syscall_s			syscall32[] = SYSCALL_32;

	iov.iov_base = &regs_32;
	iov.iov_len = sizeof(regs_32);
	if (wait_signal(child, &status) == EXITED)
		return;
	while (1) {
		next_syscall(child);
		if (wait_signal(child, &status) == EXITED)
            break;
		getregset(0, child, &regs_32, arch, &iov, syscall32);
		next_syscall(child);
		if (wait_signal(child, &status) == EXITED)
            break;
		getregset(1, child, &regs_32, arch, &iov, syscall32);
	}
}


void	process(pid_t child, uint8_t arch)
{
	if (ptrace(PTRACE_SEIZE, child, NULL, NULL, PTRACE_O_TRACEEXEC) < 0) {
		perror("ft_strace: ptrace PTRACE_SEIZE");
		exit(1);
	}
	if (ptrace(PTRACE_INTERRUPT, child, NULL, NULL, NULL) < 0) {
		perror("ft_strace: ptrace PTRACE_INTERRUPT");
		exit(1);
	}
	if (arch == ELFCLASS32)
		loop32(child, arch);
	else
		loop64(child, arch);
	dprintf(2, " = ?\n");
}
