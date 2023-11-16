/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   strace.c                                        :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/11/14 01:35:35 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/16 02:54:38 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "strace.h"


void	child(char *filename, char **av, char **envp)
{
	ptrace(PTRACE_TRACEME, 0, NULL, NULL);
	execve(filename, av, envp);
	free(filename);
	printf("strace: %s: %s\n", av[0], strerror(errno));
	exit(1);
}


int8_t	strace(char **av, char **envp)
{
	char		*filename;
	struct stat	statbuf;
	pid_t		pid;

	filename = path_finding(*av, envp);
	if (!filename)
		goto err;
	if (stat(filename, &statbuf) < 0) {
		printf("strace: Can't stat '%s': %s\n", av[0], strerror(errno));
		return FAILURE;
	}
	if ((pid = fork()) < 0)
		goto err;
	if (pid == 0) {
		child(filename, av, envp);
	} else {
		if (process(pid) == FAILURE)
			return FAILURE;
	}
	return SUCCESS;
err:
	printf("strace: %s: %s\n", av[0], strerror(errno));
	return FAILURE;
}


int	main(int ac, char **av, char **envp)
{
	if (ac == 1) {
		printf("strace: must have PROG [ARGS]");
	} else {
		if (strace(av + 1, envp) == FAILURE)
			return 1;
	}
	return 0;
}
