/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   strace.h                                        :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/11/14 01:37:25 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/21 22:43:39 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


#ifndef __STRACE_H__
# define __STRACE_H__


# define _GNU_SOURCE
# define SUCCESS 0
# define FAILURE -1
# define EXITED 1
# define BUFFER_SIZE 32
# define __unused __attribute__((unused))


# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <elf.h>
# include <errno.h>
# include <signal.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sched.h>
# include <ctype.h>
# include <utime.h>
# include <time.h>
# include <mqueue.h>
# include <linux/perf_event.h>
# include <sys/uio.h>
# include <poll.h>
# include <sys/user.h>
# include <sys/wait.h>
# include <sys/mman.h>
# include <sys/uio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/ptrace.h>
# include <sys/time.h>
# include <sys/socket.h>
# include <sys/resource.h>
# include <sys/utsname.h>
# include <sys/sem.h>
# include <sys/sysinfo.h>
# include <sys/msg.h>
# include <sys/wait.h>
# include <sys/times.h>
# include <sys/vfs.h>
# include <sys/epoll.h>
# include "syscall_32.h"
# include "syscall_64.h"
# include "signals.h"
# include "type.h"
# include "errno_code.h"


void		print_syscall64(struct syscall_s syscall,
				struct user_regs_struct64 *regs, pid_t child, bool is_ret);
void		print_syscall32(struct syscall_s syscall,
				struct user_regs_struct32 *regs, pid_t child, bool is_ret);
uint32_t	print_type(enum type_e flag, pid_t child, unsigned long long int value);
void		process(pid_t child);
char		*path_finding(const char *filename, char **envp);
uint8_t		arch(char *filename, char *av);
char		**split(char const *s, char c);
void		free_split(char **split);
void		putnbr(long long int nb);


#endif
