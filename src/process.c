/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   process.c                                       :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/11/16 01:37:20 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/16 16:37:15 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "strace.h"


int8_t	process(pid_t child, uint8_t arch)
{
//	long orig_eax;
	(void)child;
	(void)arch;

	wait(NULL);
//	orig_eax = ptrace(PTRACE_PEEKUSER, child, 4 * ORIG_RAX, NULL);
//	printf("The child made a system call %ld\n", orig_eax);
//    ptrace(PTRACE_CONT, child, NULL, NULL);
	printf("child finished\n");
	return SUCCESS;
	goto err;
err:
	return FAILURE;
}
