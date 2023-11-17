/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   process.c                                       :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/11/16 01:37:20 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/17 02:08:24 by amahla ###       ########     ########   */
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


static int8_t	next_syscall(pid_t child)
{
	if (ptrace(PTRACE_SYSCALL, child, NULL, NULL) < 0) {
		perror("ft_strace: ptrace PTRACE_SYSCALL");
		return FAILURE;
	}
	return SUCCESS;
}


static int8_t	getregset(bool is_ret, pid_t child, void *regs, uint8_t arch,
	struct iovec *iov, struct syscall_s syscall[])
{

	if (ptrace(PTRACE_GETREGSET, child, NT_PRSTATUS, iov) < 0) {
		perror("ft_strace: ptrace PTRACE_GETREGSET");
		return FAILURE;
	}
	if (arch == ELFCLASS32) {
		print_syscall(
			syscall[(*(struct user_regs_struct32 *)regs).orig_eax],
			arch,
			(unsigned long long int)(*(struct user_regs_struct32 *)regs).eax,
			is_ret
		);
	} else {
		print_syscall(
			syscall[(*(struct user_regs_struct64 *)regs).orig_rax],
			arch,
			(unsigned long long int)(*(struct user_regs_struct64 *)regs).rax,
			is_ret
		);
	}
	return SUCCESS;
}


static int8_t	loop64(pid_t child, uint8_t arch)
{
	int							status;
	struct iovec				iov;
	struct user_regs_struct64	regs_64;
	struct syscall_s			syscall64[] = SYSCALL_64;

	iov.iov_base = &regs_64;
	iov.iov_len = sizeof(regs_64);
	if (wait_signal(child, &status) == EXITED)
		return SUCCESS;
	while (1) {
		if (next_syscall(child) == FAILURE)
			return FAILURE;
		if (wait_signal(child, &status) == EXITED)
            break;
		if (getregset(0, child, &regs_64, arch, &iov, syscall64) == FAILURE)
			return FAILURE;
		if (next_syscall(child) == FAILURE)
			return FAILURE;
		if (wait_signal(child, &status) == EXITED)
            break;
		if (getregset(1, child, &regs_64, arch, &iov, syscall64) == FAILURE)
			return FAILURE;
	}
	return SUCCESS;
}


static int8_t	loop32(pid_t child, uint8_t arch)
{
	int							status;
	struct iovec				iov;
	struct user_regs_struct32	regs_32;
	struct syscall_s			syscall32[] = SYSCALL_32;

	iov.iov_base = &regs_32;
	iov.iov_len = sizeof(regs_32);
	if (wait_signal(child, &status) == EXITED)
		return SUCCESS;
	while (1) {
		if (next_syscall(child) == FAILURE)
			return FAILURE;
		if (wait_signal(child, &status) == EXITED)
            break;
		if (getregset(0, child, &regs_32, arch, &iov, syscall32) == FAILURE)
			return FAILURE;
		if (next_syscall(child) == FAILURE)
			return FAILURE;
		if (wait_signal(child, &status) == EXITED)
            break;
		if (getregset(1, child, &regs_32, arch, &iov, syscall32) == FAILURE)
			return FAILURE;
	}
	return SUCCESS;
}


int8_t	process(pid_t child, uint8_t arch)
{
	(void)arch;
	if (ptrace(PTRACE_SEIZE, child, NULL, NULL, NULL) < 0) {
		perror("ft_strace: ptrace PTRACE_SEIZE");
		return FAILURE;
	}
	if (ptrace(PTRACE_INTERRUPT, child, NULL, NULL, NULL) < 0) {
		perror("ft_strace: ptrace PTRACE_INTERRUPT");
		return FAILURE;
	}
//	if (ptrace(PTRACE_SETOPTIONS, child, NULL, PTRACE_O_TRACEEXEC) < 0)
//		return FAILURE;
//	if (ptrace(PTRACE_LISTEN, child, NULL, NULL, NULL) < 0)
//		return FAILURE;
	if (arch == ELFCLASS32) {
		if (loop32(child, arch) == FAILURE)
			return FAILURE;
	} else {
		if (loop64(child, arch) == FAILURE)
			return FAILURE;
	}
	printf("child finished\n");
	return SUCCESS;
}
