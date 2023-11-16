/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   strace.h                                        :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/11/14 01:37:25 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/16 02:54:15 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


#ifndef __STRACE_H__
# define __STRACE_H__

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/ptrace.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>

# include <sys/wait.h>


# define SUCCESS 0
# define FAILURE -1


int8_t	process(pid_t child);
char	*path_finding(const char *filename, char **envp);
char	**split(char const *s, char c);


#endif
