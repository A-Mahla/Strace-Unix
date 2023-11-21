/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   strace.c                                        :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/11/14 01:35:35 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/21 04:36:14 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "strace.h"


int8_t	child(char *filename, char **av, char **envp)
{
	execve(filename, av, envp);
	free(filename);
	dprintf(2, "strace: exec: %s\n", strerror(errno));
	exit(1);
}


static void	strace(char **av, char **envp)
{
	struct stat	statbuf;
	char		*filename;
	pid_t		pid;

	filename = path_finding(*av, envp);
	if (!filename)
		goto err;
	if (stat(filename, &statbuf) < 0) {
		dprintf(2, "strace: Can't stat '%s': %s\n", *av, strerror(errno));
		goto exit_failure;
	}
	if ((pid = fork()) < 0)
		goto err;
	if (pid == 0) {
		child(filename, av, envp);
	} else {
		free(filename);
		process(pid);
	}
	return;
err:
	dprintf(2, "strace: %s: %s\n", av[0], strerror(errno));
exit_failure:
	if (filename)
		free(filename);
	exit(1);
}


int	main(int ac, char **av, char **envp)
{
	if (ac == 1)
		dprintf(2, "strace: must have PROG [ARGS]\n");
	else
		strace(av + 1, envp);
	return 0;
}
