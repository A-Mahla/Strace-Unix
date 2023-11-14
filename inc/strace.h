/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   strace.h                                        :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/11/14 01:37:25 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/14 02:49:49 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


#ifndef __STRACE_H__
# define __STRACE_H__

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>


# define SUCCESS 0
# define FAILURE -1


char	*path_finding(const char *filename, char **envp);
char	**split(char const *s, char c);


#endif
