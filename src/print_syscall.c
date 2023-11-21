/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   print_syscall.c                                 :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/11/16 23:57:49 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/21 04:43:11 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "strace.h"


static bool	is_start = false;


static void	print_errno(int code)
{
	static const char	*err[] = ERRNO_CODE;

	dprintf(2, " %s (%s)", err[code], strerror(code));
}


static bool	is_execve_or_exit(const char *name)
{
	if (strcmp(name, "execve") == 0)
		return true;
	if (strstr(name, "exit") != NULL)
		return true;
	return false;
}


static void	padding(uint32_t ret)
{
	uint8_t	pad = 38;

	if (ret > 38)
		return;
	for (int i = pad - ret; i >= 0; i--) {
		write(1, " ", 1);
	}
}


void	print_syscall64(struct syscall_s syscall,
	struct user_regs_struct64 *regs, pid_t child, bool is_ret)
{
	uint32_t	ret = 0;

//	TO DELETE AFTER SIGNAL HANDLING
	if (!is_start && strcmp(syscall.name, "execve") == 0)
		is_start = true;
	if (!is_start)
		return;
/////////////////
	if ((is_ret && !is_execve_or_exit(syscall.name))
		|| (!is_ret && is_execve_or_exit(syscall.name))
	) {
		ret += dprintf(2, "%s(", syscall.name);
		for (unsigned int i = 0; i < syscall.argc; i++) {
			if (syscall.type_args[i] == 0)
				break;
			if (i == 0)
				ret += print_type(syscall.type_args[i], child, regs->rdi);
			else if (i == 1)
				ret += print_type(syscall.type_args[i], child, regs->rsi);
			else if (i == 2)
				ret += print_type(syscall.type_args[i], child, regs->rdx);
			else if (i == 3)
				ret += print_type(syscall.type_args[i], child, regs->r10);
			else if (i == 4)
				ret += print_type(syscall.type_args[i], child, regs->r8);
			else if (i == 5)
				ret += print_type(syscall.type_args[i], child, regs->r9);
			if (i < syscall.argc - 1)
				ret += dprintf(2, ", ");
		}
		ret += dprintf(2, ")");
		padding(ret);
	}
	if (is_ret) {
		dprintf(2, " = ");
		if (syscall.type_ret == INT && (int)regs->rax < 0) {
			print_type(syscall.type_ret, child, -1);
			print_errno((int)regs->rax * -1);
		} else {
			print_type(syscall.type_ret, child, regs->rax);
		}
		dprintf(2, "\n");
	}
}


void	print_syscall32(struct syscall_s syscall,
	struct user_regs_struct32 *regs, pid_t child, bool is_ret)
{
	uint32_t	ret = 0;

	if (regs->orig_eax < NB_SYSCALL_32
			&& strcmp(syscall.name, "no_syscall") == 0)
		return;
//	TO DELETE AFTER SIGNAL HANDLING
	if (!is_start && strcmp(syscall.name, "execve") == 0)
		is_start = true;
	else if (!is_start)
		return;
/////////////////

	if ((is_ret && !is_execve_or_exit(syscall.name))
		|| (!is_ret && is_execve_or_exit(syscall.name))
	) {
		ret += dprintf(2, "%s(", syscall.name);
		for (unsigned int i = 0; i < syscall.argc; i++) {
			if (syscall.type_args[i] == 0)
				break;
			if (i == 0)
				ret += print_type(syscall.type_args[i], child, regs->ebx);
			else if (i == 1)
				ret += print_type(syscall.type_args[i], child, regs->ecx);
			else if (i == 2)
				ret += print_type(syscall.type_args[i], child, regs->edx);
			else if (i == 3)
				ret += print_type(syscall.type_args[i], child, regs->esi);
			else if (i == 4)
				ret += print_type(syscall.type_args[i], child, regs->edi);
			else if (i == 5)
				ret += print_type(syscall.type_args[i], child, regs->ebp);
			if (i < syscall.argc - 1)
				ret += dprintf(2, ", ");
		}
		ret += dprintf(2, ")");
		padding(ret);
	}
	if (is_ret) {
		dprintf(2, " = ");
		if (syscall.type_ret == INT && (int)regs->eax < 0) {
			print_type(syscall.type_ret, child, -1);
			print_errno((int)regs->eax * -1);
		} else {
			print_type(syscall.type_ret, child, regs->eax);
		}
		dprintf(2, "\n");
	}
}
