/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   strace.c                                        :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/11/14 01:35:35 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/18 17:44:28 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "strace.h"


int8_t	child(char *filename, char **av, char **envp)
{
	execve(filename, av, envp);
	free(filename);
	printf("strace: exec: %s\n", strerror(errno));
	exit(1);
}


static void	strace(char **av, char **envp)
{
	char	*filename;
	uint8_t	class;
	pid_t	pid;

	filename = path_finding(*av, envp);
	if (!filename)
		goto err;
	class = arch(filename, *av);
	if ((pid = fork()) < 0)
		goto err;
	if (pid == 0) {
		child(filename, av, envp);
	} else {
		free(filename);
		process(pid, class);
	}
	return;
err:
	printf("strace: %s: %s\n", av[0], strerror(errno));
	if (filename)
		free(filename);
	exit(1);
}


int	main(int ac, char **av, char **envp)
{
	if (ac == 1)
		printf("strace: must have PROG [ARGS]\n");
	else
		strace(av + 1, envp);
	return 0;
}
