/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   process.c                                       :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/11/16 01:37:20 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/16 02:58:11 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "strace.h"


int8_t	process(pid_t child)
{
	long orig_eax;

	wait(NULL);
//	orig_eax = ptrace(PTRACE_PEEKUSER, child, 4 * ORIG_RAX, NULL);
	printf("The child made a system call %ld\n", orig_eax);
    ptrace(PTRACE_CONT, child, NULL, NULL);
	printf("child finished\n");
	return SUCCESS;
}
