/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   print_syscall.c                                 :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/11/16 23:57:49 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/17 01:49:59 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "strace.h"


void	print_syscall(struct syscall_s syscall, uint8_t arch,
	unsigned long long int rax, bool is_ret)
{
	static bool	is_start = false;

	(void)arch;
	(void)is_ret;
	if (!is_start && strcmp(syscall.name, "execve") == 0)
		is_start = true;
	else if (!is_start)
		return;
	if (is_ret) {
		printf(" => %lld\n", (long long int)rax);
	} else {
		printf("%s()", syscall.name);
	}
}
