/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   print_syscall.c                                 :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/11/16 23:57:49 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/19 02:52:43 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "strace.h"


static bool	is_start = false;


static void	print_errno(int code)
{
	static const char	*err[] = ERRNO_CODE;

	printf(" %s (%s)", err[code], strerror(code));
}


static bool	is_execve_or_exit(const char *name)
{
	if (strcmp(name, "execve") == 0)
		return true;
	if (strstr(name, "exit") != NULL)
		return true;
	return false;
}


void	print_syscall64(struct syscall_s syscall, uint8_t arch,
	struct user_regs_struct64 *regs, pid_t child, bool is_ret)
{
	static struct user_regs_struct64 local;
	(void)arch;
	(void)is_ret;
	(void)local;

//	TO DELETE AFTER SIGNAL HANDLING
	if (!is_start && strcmp(syscall.name, "execve") == 0)
		is_start = true;
	else if (!is_start)
		return;
/////////////////
	if ((is_ret && !is_execve_or_exit(syscall.name))
		|| (!is_ret && is_execve_or_exit(syscall.name))
	) {
		printf("%s(", syscall.name);
		for (unsigned int i = 0; i < syscall.argc; i++) {
			if (syscall.type_args[i] == 0)
				break;
			if (i == 0)
				print_type(syscall.type_args[i], child, regs->rdi, arch);
			else if (i == 1)
				print_type(syscall.type_args[i], child, regs->rsi, arch);
			else if (i == 2)
				print_type(syscall.type_args[i], child, regs->rdx, arch);
			else if (i == 3)
				print_type(syscall.type_args[i], child, regs->r10, arch);
			else if (i == 4)
				print_type(syscall.type_args[i], child, regs->r8, arch);
			else if (i == 5)
				print_type(syscall.type_args[i], child, regs->r9, arch);
			if (i < syscall.argc - 1)
				printf(", ");
		}
		printf(")");
	}
	if (is_ret) {
		printf(" = ");
		if (syscall.type_ret == INT && (int)regs->rax < 0) {
			print_type(syscall.type_ret, child, -1, arch);
			print_errno((int)regs->rax * -1);
		} else {
			print_type(syscall.type_ret, child, regs->rax, arch);
		}
		printf("\n");
	} else {
		local = *regs;
	}
}


void	print_syscall32(struct syscall_s syscall, uint8_t arch,
	struct user_regs_struct32 *regs, pid_t child, bool is_ret)
{
	(void)arch;
	(void)is_ret;
	(void)child;
//	TO DELETE AFTER SIGNAL HANDLING
	if (!is_start && strcmp(syscall.name, "execve") == 0)
		is_start = true;
	else if (!is_start)
		return;
/////////////////
	if (is_ret)
		printf(" => %ld\n", regs->eax);
	else
		printf("%s()", syscall.name);
}
