/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   print_type.c                                    :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/11/17 18:00:59 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/20 03:37:03 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "strace.h"


static uint8_t	read_data_from_memory(pid_t child, unsigned long long int value,
	int size, void *local_buffer)
{
	int8_t				ret;
	const struct iovec	local = {.iov_base = local_buffer, .iov_len = size};
	const struct iovec	remote = {.iov_base = (void *)value, .iov_len = size};

	if ((ret = process_vm_readv(child, &local, 1, &remote, 1, 0)) < 0) {
		perror("ft_strace: process_vm_readv");
		exit(1);
	}
	if (ret < size)
		((char *)local_buffer)[ret] = '\0';
	return ret;
}


static uint32_t	print_undef(__unused pid_t child,
	__unused unsigned long long int value)
{
	return 0;
}


static uint32_t	print_int(__unused pid_t child, unsigned long long int value)
{
	return dprintf(2, "%d", (int)value);
}


static uint32_t	print_long(__unused pid_t child, unsigned long long int value)
{
	return dprintf(2, "%ld", (long int)value);
}


static uint32_t	print_ulong(__unused pid_t child, unsigned long long int value)
{
	return dprintf(2, "%lld", (unsigned long long int)value);
}

static uint32_t	print_float(__unused pid_t child, unsigned long long int value)
{
	return dprintf(2, "%Lf", (long double)value);
}


static uint32_t	print_ptr(__unused pid_t child, unsigned long long int value)
{
	if (value == 0)
		return dprintf(2, "NULL");
	else
		return dprintf(2, "%#lx", (uintptr_t)value);
}


static uint32_t	print_str(pid_t child, unsigned long long int value)
{
	char		buffer[BUFFER_SIZE] = {0};
	uint32_t	ret = 0;
	int8_t		i = 0;
	int8_t		size;

	if (value == 0) {
		return dprintf(2, "NULL");
	} else {
		size = read_data_from_memory(child, value, BUFFER_SIZE, buffer);
		ret += dprintf(2, "\"");
		while ((isprint(*buffer) && buffer[i] && i < size)
			|| (!isprint(*buffer) && i < size)
		) {
			if (isprint(buffer[i]))
				ret += dprintf(2, "%c", buffer[i]);
			else
				ret += dprintf(2, "\\%hho", buffer[i]);
			i++;
		}
		ret += dprintf(2, "\"");
		if (i == BUFFER_SIZE)
			ret += dprintf(2, "...");
	}
	return ret;
}


static uint32_t	print_flag_open(__unused pid_t child,
	unsigned long long int value)
{
	bool		first = true;
	uint32_t	ret = 0;
	static const struct type_flag	flags[] = {
		[ 0] = {.flag = O_RDONLY, .name = "O_RDONLY"},
		[ 1] = {.flag = O_WRONLY, .name = "O_WRONLY"},
		[ 2] = {.flag = O_RDWR, .name = "O_RDWR"},
		[ 3] = {.flag = O_CREAT, .name = "O_CREAT"},
		[ 4] = {.flag = O_EXCL, .name = "O_EXCL"},
		[ 5] = {.flag = O_NOCTTY, .name = "O_NOCTTY"},
		[ 6] = {.flag = O_TRUNC, .name = "O_TRUNC"},
		[ 7] = {.flag = O_APPEND, .name = "O_APPEND"},
		[ 8] = {.flag = O_NONBLOCK, .name = "O_NONBLOCK"},
		[ 9] = {.flag = O_DSYNC, .name = "O_DSYNC"},
		[10] = {.flag = FASYNC, .name = "FASYNC"},
		[11] = {.flag = O_CLOEXEC, .name = "O_CLOEXEC"},
		[12] = {.flag = O_DIRECTORY, .name = "O_DIRECTORY"},
		[13] = {.flag = O_NOFOLLOW, .name = "O_NOFOLLOW"},
		[14] = {.flag = O_SYNC, .name = "O_SYNC"},
		[15] = {.flag = O_ASYNC, .name = "O_ASYNC"},
		[16] = {.flag = O_DIRECT, .name = "O_DIRECT"},
		[17] = {.flag = O_NOATIME, .name = "O_NOATIME"},
		[18] = {.flag = O_PATH, .name = "O_PATH"},
		[19] = {.flag = O_RSYNC, .name = "O_RSYNC"},
		[20] = {.flag = O_ACCMODE, .name = "O_ACCMODE"},
	};

	for (long unsigned int i = 0; i < sizeof(flags) / sizeof(flags[0]); i++)
	{
		if (((int)value & flags[i].flag)
			|| (flags[i].flag == 0 && !((int)value & flags[i].flag) ))
		{
			if (!first)
				ret += dprintf(2, "|");
			else
				first = false;
			ret += dprintf(2, "%s", flags[i].name);
		}
	}
	return ret;
}


static uint32_t	print_prot_mmap(__unused pid_t child, unsigned long long int value)
{
	bool		first = true;
	uint32_t	ret = 0;
	static const struct type_flag	flags[] = {
		[0] = {.flag = PROT_READ, .name = "PROT_READ"},
		[1] = {.flag = PROT_WRITE, .name = "PROT_WRITE"},
		[2] = {.flag = PROT_EXEC, .name = "PROT_EXEC"},
		[3] = {.flag = PROT_NONE, .name = "PROT_NONE"},
		[4] = {.flag = PROT_GROWSDOWN, .name = "PROT_GROWSDOWN"},
		[5] = {.flag = PROT_GROWSUP, .name = "PROT_GROWSUP"},
	};

	for (long unsigned int i = 0; i < sizeof(flags) / sizeof(flags[0]); i++)
	{
		if ((int)value & flags[i].flag)
		{
			if (!first)
				ret += dprintf(2, "|");
			else
				first = false;
			ret += dprintf(2, "%s", flags[i].name);
		}
	}
	if (first && !((int)value & PROT_NONE))
		ret += dprintf(2, "%s", "PROT_NONE");
	return ret;
}


static uint32_t	print_flag_mmap(__unused pid_t child, unsigned long long int value)
{
	bool		first = true;
	uint32_t	ret = 0;
	static const struct type_flag	flags[] = {
		[ 0] = {.flag = MAP_SHARED, .name = "MAP_SHARED"},
		[ 1] = {.flag = MAP_PRIVATE, .name = "MAP_PRIVATE"},
		[ 2] = {.flag = MAP_FIXED, .name = "MAP_FIXED"},
		[ 3] = {.flag = MAP_ANONYMOUS, .name = "MAP_ANONYMOUS"},
		[ 4] = {.flag = MAP_GROWSDOWN, .name = "MAP_GROWSDOWN"},
		[ 5] = {.flag = MAP_DENYWRITE, .name = "MAP_DENYWRITE"},
		[ 6] = {.flag = MAP_EXECUTABLE, .name = "MAP_EXECUTABLE"},
		[ 7] = {.flag = MAP_LOCKED, .name = "MAP_LOCKED"},
		[ 8] = {.flag = MAP_NORESERVE, .name = "MAP_NORESERVE"},
		[ 9] = {.flag = MAP_POPULATE, .name = "MAP_POPULATE"},
		[10] = {.flag = MAP_NONBLOCK, .name = "MAP_NONBLOCK"},
		[11] = {.flag = MAP_STACK, .name = "MAP_STACK"},
		[12] = {.flag = MAP_HUGETLB, .name = "MAP_HUGETLB"},
		[13] = {.flag = MAP_SYNC, .name = "MAP_SYNC"},
		[14] = {.flag = MAP_FIXED_NOREPLACE, .name = "MAP_FIXED_NOREPLACE"},
	};

	for (long unsigned int i = 0; i < sizeof(flags) / sizeof(flags[0]); i++)
	{
		if (((int)value & flags[i].flag)
			|| (flags[i].flag == 0 && !((int)value & flags[i].flag) ))
		{
			if (!first)
				ret += dprintf(2, "|");
			else
				first = false;
			ret += dprintf(2, "%s", flags[i].name);
		}
	}
	return ret;
}


static uint32_t	print_trace_flags(__unused pid_t child, unsigned long long int value)
{
	uint32_t	ret = 0;
	static const struct type_flag	flags[] = {
		[0] = {.flag = PTRACE_TRACEME, .name = "PTRACE_TRACEME"},
		[1] = {.flag = PTRACE_PEEKTEXT, .name = "PTRACE_PEEKTEXT"},
		[2] = {.flag = PTRACE_PEEKDATA, .name = "PTRACE_PEEKDATA"},
		[3] = {.flag = PTRACE_PEEKUSER, .name = "PTRACE_PEEKUSER"},
		[4] = {.flag = PTRACE_POKETEXT, .name = "PTRACE_POKETEXT"},
		[5] = {.flag = PTRACE_POKEDATA, .name = "PTRACE_POKEDATA"},
		[6] = {.flag = PTRACE_POKEUSER, .name = "PTRACE_POKEUSER"},
		[7] = {.flag = PTRACE_GETREGS, .name = "PTRACE_GETREGS"},
		[8] = {.flag = PTRACE_GETFPREGS, .name = "PTRACE_GETFPREGS"},
		[9] = {.flag = PTRACE_GETSIGINFO, .name = "PTRACE_GETSIGINFO"},
		[10] = {.flag = PTRACE_SETREGS, .name = "PTRACE_SETREGS"},
		[11] = {.flag = PTRACE_SETFPREGS, .name = "PTRACE_SETFPREGS"},
		[12] = {.flag = PTRACE_SETSIGINFO, .name = "PTRACE_SETSIGINFO"},
		[13] = {.flag = PTRACE_SETOPTIONS, .name = "PTRACE_SETOPTIONS"},
		[14] = {.flag = PTRACE_GETEVENTMSG, .name = "PTRACE_GETEVENTMSG"},
		[15] = {.flag = PTRACE_CONT, .name = "PTRACE_CONT"},
		[16] = {.flag = PTRACE_SYSCALL, .name = "PTRACE_SYSCALL"},
		[17] = {.flag = PTRACE_SINGLESTEP, .name = "PTRACE_SINGLESTEP"},
		[18] = {.flag = PTRACE_SYSEMU, .name = "PTRACE_SYSEMU"},
		[19] = {.flag = PTRACE_SYSEMU_SINGLESTEP, .name = "PTRACE_SYSEMU_SINGLESTEP"},
		[20] = {.flag = PTRACE_KILL, .name = "PTRACE_KILL"},
		[21] = {.flag = PTRACE_ATTACH, .name = "PTRACE_ATTACH"},
		[22] = {.flag = PTRACE_DETACH, .name = "PTRACE_DETACH"},
		
	};

	for (long unsigned int i = 0; i < sizeof(flags) / sizeof(flags[0]); i++)
	{
		if (value == flags[i].flag)
		{
			ret += dprintf(2, "%s", flags[i].name);
			break;
		}
	}
	return ret;
}


static uint32_t	print_dirfd(__unused pid_t child, unsigned long long int value)
{
	uint32_t	ret = 0;
	bool		first = true;
	int			new_value = (int)value;
	static const struct type_flag	flags[] = {
		[0] = {.flag = AT_FDCWD, .name = "AT_FDCWD"},
//		[1] = {.flag = AT_SYMLINK_NOFOLLOW, .name = "AT_SYMLINK_NOFOLLOW"},
//		[2] = {.flag = AT_REMOVEDIR, .name = "AT_REMOVEDIR"},
//		[3] = {.flag = AT_SYMLINK_FOLLOW, .name = "AT_SYMLINK_FOLLOW"},
//		[4] = {.flag = AT_EACCESS, .name = "AT_EACCESS"},
	};

	for (long unsigned int i = 0; i < sizeof(flags) / sizeof(flags[0]); i++)
	{
		if ( new_value & flags[i].flag)
		if ((new_value & flags[i].flag)
			|| (flags[i].flag == 0 && !(new_value & flags[i].flag) ))
		{
			if (!first)
				ret += dprintf(2, "|");
			else
				first = false;
			ret += dprintf(2, "%s", flags[i].name);
		}
	}
	if (first)
		ret += dprintf(2, "%d", (int)value);
	return ret;
}


static uint32_t	print_pipe(__unused pid_t child, unsigned long long int value)
{
	int			buffer[2];

	read_data_from_memory(child, value, 2 * sizeof(int), buffer);
	return dprintf(2, "[%d, %d]", buffer[0], buffer[1]);
}


static uint32_t	print_id(__unused pid_t child, unsigned long long int value)
{
	int			buffer[1] = {0};

	read_data_from_memory(child, value, 2 * sizeof(int), buffer);
	return dprintf(2, "[%d, ...]", buffer[0]);
}


static uint32_t	print_offset(__unused pid_t child, unsigned long long int value)
{
	return dprintf(2, "%#lx", (uintptr_t)value);
}


static uint32_t	print_argv(pid_t child, unsigned long long int value)
{
	char		*argv[1];
	uint32_t	ret = 0;
	int32_t		i = 0;

	ret += dprintf(2, "[");
	if (value == 0) {
		ret += dprintf(2, "NULL");
	} else {
		read_data_from_memory(child, value, sizeof(char *), argv);
		while (*argv) {
		i += 8;
		ret += print_str(child, (unsigned long long int)*argv);
		read_data_from_memory(child, value + i, sizeof(char *), argv);
		if (*argv)
			ret += dprintf(2, ", ");
		}
	}
	ret += dprintf(2, "]");
	return ret;
}


static uint32_t	print_envp(__unused pid_t child, unsigned long long int value)
{
	char		*envp[1];
	uint32_t	ret = 0;
	int			i = 0;
	int			y = 0;

	ret += print_ptr(child, value);
	read_data_from_memory(child, value, sizeof(char *), envp);
	while (*envp) {
		i++;
		y += 8;
		read_data_from_memory(child, value + y, sizeof(char *), envp);
	}
	ret += dprintf(2, " /* %d vars */", i);
	return ret;
}


uint32_t	print_type(enum type_e flag, pid_t child, unsigned long long int value)
{
	static uint32_t (*f[])(pid_t, unsigned long long int) = {
		[UNDEF] = print_undef,
		[INT] = print_int,
		[LONG] = print_long,
		[ULONG] = print_ulong,
		[PTR] = print_ptr,
		[STR] = print_str,
		[CONST_STR] = print_str,
		[FLAG_OPEN] = print_flag_open,
		[FLAG_OPENAT] = print_flag_open,
		[FLAG_PROT] = print_prot_mmap,
		[FLAG_MMAP] = print_flag_mmap,
		[OFF] = print_offset, 
		[DIRFD] = print_dirfd, 
		[PIPE] = print_pipe,
		[MODE] = print_flag_open,
		[CLOCK] = print_float,
		[PTRACE] = print_trace_flags,
		[ID_T] = print_id,
		[ARGV] = print_argv,
		[ENVP] = print_envp,
	};
//		[VARARGS]
//		[STRUCT_STAT] // Struct types
//		[STRUCT_POLL]
//		[STRUCT_SIGACT]
//		[STRUCT_SIGSET]
//		[STRUCT_SIGINF]
//		[STRUCT_IOVEC]
//		[STRUCT_FDSET]
//		[STRUCT_TIMEVAL]
//		[STRUCT_TIMEZONE]
//		[STRUCT_TIMESPEC]
//		[STRUCT_SHMID]
//		[STRUCT_SOCKADDR]
//		[STRUCT_MSGHDR]
//		[STRUCT_RUSAGE]
//		[STRUCT_UTSNAME]
//		[STRUCT_SEMBUF]
//		[STRUCT_MSGID]
//		[STRUCT_LINUX_DIR]
//		[STRUCT_RLIMIT]
//		[STRUCT_SYSINFO]
//		[STRUCT_SIGINFO]
//		[STRUCT_TMS]
//		[STRUCT_SIGSTACK]
//		[STRUCT_UTIMBUF]
//		[STRUCT_USTAT]
//		[STRUCT_STATFS]
//		[STRUCT_SCHED_PARAM]
//		[STRUCT_SYSCTL]
//		[STRUCT_TIMEX]
//		[STRUCT_KERNEL_SYM]
//		[STRUCT_NFSCTL_ARG]
//		[STRUCT_NFSCTL_RES]
//		[STRUCT_STRBUF]
//		[STRUCT_CPU_SET]
//		[STRUCT_USER_DESC]
//		[STRUCT_IO_EVENT]
//		[STRUCT_IOCB]
//		[STRUCT_LINUX_DIRENT64]
//		[STRUCT_SIGEVENT]
//		[STRUCT_ITIMERSPEC]
//		[STRUCT_EPOLL_EVENT]
//		[STRUCT_MQ_ATTR]
//		[STRUCT_KEXEC_SEGMENT]
//		[STRUCT_PERF_EVENT_ATTR]
//		[STRUCT_MMSGHDR]
//		[STRUCT_FILE_HANDLE]
//		[STRUCT_GETCPU_CACHE]
//		[STRUCT_SCHED_ATTR]
//		[STRUCT_STATX]
//		[STRUCT_PTREGS]
//		[STRUCT_POLLFD]
//		[STRUCT_ROBUST_LIST_HEAD]
//		[STRUCT_OLDKERNELSTAT]
//		[STRUCT_VM86]
//		[STRUCT_VM86PLUS]
//		[STRUCT_NEWUTSNAME]
//	};
//	if ((arch ==  ELFCLASS32 && flag < NB_SYSCALL_32)
//			|| (arch ==  ELFCLASS64 && flag < NB_SYSCALL_64))
//		f[flag](value, arch);
	if (flag < VARARGS)
		return f[flag](child, value);
	return 0;
}
