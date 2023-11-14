/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   strace.c                                        :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/11/14 01:35:35 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/14 03:52:18 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "strace.h"


int8_t	strace(char **av, char **envp)
{
	char *filename = path_finding(*av, envp);
	if (!filename)
		goto exit_err_enomem;
	execve(filename, av, envp);
	printf("strace: %s: %s\n", av[0], strerror(errno));
	free(filename);
	exit(-errno);
exit_err_enomem:
	if (errno == ENOMEM)
		printf("strace: %s: %s\n", av[0], strerror(errno));
	exit(-ENOMEM);
}


int	main(int ac, char **av, char **envp)
{
	if (ac == 1)
		printf("strace: must have PROG [ARGS]");
	else
		strace(av + 1, envp);
	return 0;
}
