/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   print_type.c                                    :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/11/17 18:00:59 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/18 04:26:52 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "strace.h"


static void	print_undef(unsigned long long int value, uint8_t arch)
{
	(void)arch;
	(void)value;
}


static void	print_int(unsigned long long int value, uint8_t arch)
{
	(void)arch;
	printf("%d", (int)value);
}


static void	print_long(unsigned long long int value, uint8_t arch)
{
	(void)arch;
	printf("%ld", (long int)value);
}


static void	print_ulong(unsigned long long int value, uint8_t arch)
{
	(void)arch;
	printf("%lld", (unsigned long long int)value);
}


static void	print_ptr(unsigned long long int value, uint8_t arch)
{
	(void)arch;
	printf("%#lx", (uintptr_t)value);
}


static void	print_str(unsigned long long int value, uint8_t arch)
{
	(void)arch;
	printf("%s", (char *)&value);
}


static void	print_flag_open(unsigned long long int value, uint8_t arch)
{
	(void)arch;
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
		[13] = {.flag = O_DIRECTORY, .name = "O_DIRECTORY"},
		[14] = {.flag = O_NOFOLLOW, .name = "O_NOFOLLOW"},
		[16] = {.flag = O_CLOEXEC, .name = "O_CLOEXEC"},
		[17] = {.flag = O_SYNC, .name = "O_SYNC"},
		[20] = {.flag = O_NDELAY, .name = "O_NDELAY"},
	};
	bool first = true;

	for (long unsigned int i = 0; i < sizeof(flags) / sizeof(flags[0]); i++)
	{
		if (value & flags[i].flag)
		{
			if (!first)
				printf("|");
			else
				first = false;
			printf("%s", flags[i].name);
		}
	}
	
}


static void	print_prot_mmap(unsigned long long int value, uint8_t arch)
{
	(void)arch;
	static const struct type_flag	flags[] = {
		[0] = {.flag = PROT_READ, .name = "PROT_READ"},
		[1] = {.flag = PROT_WRITE, .name = "PROT_WRITE"},
		[2] = {.flag = PROT_EXEC, .name = "PROT_EXEC"},
		[3] = {.flag = PROT_NONE, .name = "PROT_NONE"},
		[4] = {.flag = PROT_GROWSDOWN, .name = "PROT_GROWSDOWN"},
		[5] = {.flag = PROT_GROWSUP, .name = "PROT_GROWSUP"},
	};
	bool first = true;

	for (long unsigned int i = 0; i < sizeof(flags) / sizeof(flags[0]); i++)
	{
		if (value & flags[i].flag)
		{
			if (!first)
				printf("|");
			else
				first = false;
			printf("%s", flags[i].name);
		}
	}
	
}


static void	print_flag_mmap(unsigned long long int value, uint8_t arch)
{
	(void)arch;
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
	bool first = true;
//	(void)value;

	for (long unsigned int i = 0; i < sizeof(flags) / sizeof(flags[0]); i++)
	{
		if (value & flags[i].flag)
		{
			if (!first)
				printf("|");
			else
				first = false;
			printf("%s", flags[i].name);
		}
//		printf("\n%s => %lld", flags[i].name, flags[i].flag);
	}
//	printf("\n%s => %d", "value", (int)value);
//	printf("\n");
}


void	print_type(enum type_e flag, unsigned long long int value, uint8_t arch)
{
	static void (*f[])(unsigned long long int, uint8_t) = {
		[UNDEF] = print_undef,
		[INT] = print_int,
		[LONG] = print_long,
		[ULONG] = print_ulong,
		[PTR] = print_ptr,
		[STR] = print_str,
		[FLAG_OPEN] = print_flag_open,
		[FLAG_OPENAT] = print_flag_open,
		[FLAG_PROT] = print_prot_mmap,
		[FLAG_MMAP] = print_flag_mmap,
	};
//		[PIPE] // Special types
//		[SV]
//		[KEY]
//		[MODE]
//		[CLOCK]
//		[PTRACE]
//		[ID_T]
//		[DEV]
//		[TIME]
//		[SIGNAL]
//		[ARGV]
//		[ENVP]
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
	if ((arch ==  ELFCLASS32 && flag < PIPE)
			|| (arch ==  ELFCLASS64 && flag < PIPE))
		f[flag](value, arch);
}
