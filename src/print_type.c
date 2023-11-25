/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   print_type.c                                    :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/11/17 18:00:59 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/11/25 22:57:42 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "strace.h"


static uint32_t	read_data_from_memory(pid_t child, unsigned long long int value,
	int size, void *local_buffer)
{
	int32_t				ret = 0;
	const struct iovec	local = {.iov_base = local_buffer, .iov_len = size};
	const struct iovec	remote = {.iov_base = (void *)value, .iov_len = size};

	if ((ret = process_vm_readv(child, &local, 1, &remote, 1, 0)) < 0) {
		perror("ft_strace: process_vm_readv");
		exit(1);
		return 0;
	}
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
	int32_t		i = 0;
	int32_t		size;

	if (value == 0) {
		return dprintf(2, "NULL");
	} else {
		size = read_data_from_memory(child, value, BUFFER_SIZE, buffer);
		ret += dprintf(2, "\"");
		while ((isprint(*buffer) && buffer[i] && i < size)
			|| (*buffer && !isprint(*buffer) && i < size)
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


static uint32_t	print_flag_access(__unused pid_t child, unsigned long long int value)
{
	uint32_t	ret = 0;
	static const struct type_flag	flags[] = {
		[ 0] = {.flag = R_OK, .name = "R_OK"},
		[ 1] = {.flag = W_OK, .name = "W_OK"},
		[ 2] = {.flag = X_OK, .name = "X_OK"},
		[ 3] = {.flag = F_OK, .name = "F_OK"},
	};

	for (long unsigned int i = 0; i < sizeof(flags) / sizeof(flags[0]); i++)
	{
		if (((int)value & flags[i].flag)
			|| (flags[i].flag == 0 && !((int)value & flags[i].flag) ))
			return dprintf(2, "%s", flags[i].name);
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
		[23] = {.flag = PTRACE_GETREGSET, .name = "PTRACE_GETREGSET"},
		
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
	char		*argv = NULL;
	uint32_t	ret = 0;
	int32_t		i = 0;

	ret += dprintf(2, "[");
	if (value == 0) {
		ret += dprintf(2, "NULL");
	} else {
		read_data_from_memory(child, value, sizeof(char *), &argv);
		while (argv) {
		i += 8;
		ret += print_str(child, (unsigned long long int)argv);
		read_data_from_memory(child, value + i, sizeof(char *), &argv);
		if (argv)
			ret += dprintf(2, ", ");
		}
	}
	ret += dprintf(2, "]");
	return ret;
}


static uint32_t	print_envp(__unused pid_t child, unsigned long long int value)
{
	char		*envp = NULL;
	uint32_t	ret = 0;
	uint32_t	i = 0;
	uint32_t	y = 0;

	ret += print_ptr(child, value);
	read_data_from_memory(child, value, sizeof(char *), &envp);
	while (envp) {
		i++;
		y += 8;
		read_data_from_memory(child, value + y, sizeof(char *), &envp);
	}
	ret += dprintf(2, " /* %d vars */", i);
	return ret;
}


static uint32_t print_struct_stat(pid_t child, unsigned long long int value)
{
	struct stat	buffer;

	if (value == 0)
		return dprintf(2, "NULL");
	if (read_data_from_memory(child, value, sizeof(struct stat), &buffer) != sizeof(struct stat))
		return 0;
	return dprintf(2, "{st_dev=%#lo, st_size=%ld, ...}", buffer.st_dev, buffer.st_ino);
}


static uint32_t print_struct_sigact(pid_t child, unsigned long long int value)
{
	struct sigaction	buffer;

	if (value == 0)
		return dprintf(2, "NULL");
	if (read_data_from_memory(child, value, sizeof(struct sigaction), &buffer) != sizeof(struct sigaction))
		return 0;
	return dprintf(2, "{sa_handler=%p, ...}", buffer.sa_handler);
}


static uint32_t print_struct_iovec(pid_t child, unsigned long long int value)
{
	struct iovec	buffer;

	if (value == 0)
		return dprintf(2, "NULL");
	if (read_data_from_memory(child, value, sizeof(struct iovec), &buffer) != sizeof(struct iovec))
		return 0;
	return dprintf(2, "{iov_base=%p, iov_len=%ld}", buffer.iov_base, buffer.iov_len);
}


static uint32_t print_struct_timeval(pid_t child, unsigned long long int value)
{
	struct timeval	buffer;

	if (value == 0)
		return dprintf(2, "NULL");
	if (read_data_from_memory(child, value, sizeof(struct timeval), &buffer) != sizeof(struct timeval))
		return 0;
	return dprintf(2, "{tv_sec=%ld, tv_usec=%ld}", buffer.tv_sec, buffer.tv_usec);
}


static uint32_t print_struct_timezone(pid_t child, unsigned long long int value)
{
	struct timezone	buffer;

	if (value == 0)
		return dprintf(2, "NULL");
	if (read_data_from_memory(child, value, sizeof(struct timezone), &buffer) != sizeof(struct timezone))
		return 0;
	return dprintf(2, "{tz_minuteswest=%d, tz_dsttime=%d}", buffer.tz_minuteswest, buffer.tz_dsttime);
}


static uint32_t print_struct_timespec(pid_t child, unsigned long long int value)
{
	struct timespec	buffer;

	if (value == 0)
		return dprintf(2, "NULL");
	if (read_data_from_memory(child, value, sizeof(struct timespec), &buffer) != sizeof(struct timespec))
		return 0;
	return dprintf(2, "{tv_sec=%ld, tv_nsec=%ld}", buffer.tv_sec, buffer.tv_nsec);
}


static uint32_t print_struct_rusage(pid_t child, unsigned long long int value)
{
	struct rusage	buffer;
	uint32_t		ret = 0;

	if (value == 0)
		return dprintf(2, "NULL");
	if (read_data_from_memory(child, value, sizeof(struct rusage), &buffer) != sizeof(struct rusage))
		return 0;
	return dprintf(2, "{ru_utime={tv_sec=%ld, tv_usec=%ld}, ru_stime={tv_sec=%ld, tv_usec=%ld}",
		buffer.ru_utime.tv_sec, buffer.ru_utime.tv_usec, buffer.ru_stime.tv_sec, buffer.ru_stime.tv_usec);
	return ret;
}


static uint32_t print_struct_utsusage(pid_t child, unsigned long long int value)
{
	struct utsname	buffer;

	if (value == 0)
		return dprintf(2, "NULL");
	if (read_data_from_memory(child, value, sizeof(struct utsname), &buffer) != sizeof(struct utsname))
		return 0;
	return dprintf(2, "{sysname=\"%s\", nodename=\"%s\", ...}", buffer.sysname, buffer.nodename);
}


static uint32_t print_struct_sembuf(pid_t child, unsigned long long int value)
{
	struct sembuf	buffer;

	if (value == 0)
		return dprintf(2, "NULL");
	if (read_data_from_memory(child, value, sizeof(struct sembuf), &buffer) != sizeof(struct sembuf))
		return 0;
	return dprintf(2, "[{sem_num=%d, sem_op=%d, sem_flg=%d}]", buffer.sem_num, buffer.sem_op, buffer.sem_flg);
}


static uint32_t print_struct_msgid(pid_t child, unsigned long long int value)
{
	struct msqid_ds	buf;
	struct ipc_perm	msg;

	if (value == 0)
		return dprintf(2, "NULL");
	if (read_data_from_memory(child, value, sizeof(struct msqid_ds), &buf) != sizeof(struct msqid_ds))
		return 0;
	msg = buf.msg_perm;
	return dprintf(2, "msg_perm={uid=%u, gid=%u, mode=%u, key=%u, cuid=%u, cgid=%u}, "
					  "msg_stime=%ld, msg_rtime=%ld, msg_ctime=%ld, msg_qnum=%ld, "
					  "msg_qbytes=%ld, msg_lspid=%d, msg_lrpid=%d",
		msg.uid, msg.gid, msg.mode, msg.__key, msg.cuid, msg.cgid, buf.msg_stime,
		buf.msg_rtime, buf.msg_ctime, buf.msg_qnum, buf.msg_qbytes, buf.msg_lspid,
		buf.msg_lrpid);
}


static uint32_t print_struct_rlimit(pid_t child, unsigned long long int value)
{
	struct rlimit	buf;

	if (value == 0)
		return dprintf(2, "NULL");
	if (read_data_from_memory(child, value, sizeof(struct rlimit), &buf) != sizeof(struct rlimit))
		return 0;
	return dprintf(2, "{rlim_cur=%ld, rlim_max=%ld}", buf.rlim_cur, buf.rlim_max);
}


static uint32_t print_struct_sysinfo(pid_t child, unsigned long long int value)
{
	struct sysinfo	buf;

	if (value == 0)
		return dprintf(2, "NULL");
	if (read_data_from_memory(child, value, sizeof(struct sysinfo), &buf) != sizeof(struct sysinfo))
		return 0;
	return dprintf(2, "{uptime=%ld, loads=[%ld, %ld, %ld], totalram=%ld, "
						"freeram=%ld, sharedram=%ld, bufferram=%ld, totalswap=%ld, "
						"freeswap=%ld, procs=%d, totalhigh=%ld, freehigh=%ld, mem_unit=%d}",
		buf.uptime, buf.loads[0], buf.loads[1], buf.loads[2], buf.totalram,
		buf.freeram, buf.sharedram, buf.bufferram, buf.totalswap, buf.freeswap,
		buf.procs, buf.totalhigh, buf.freehigh, buf.mem_unit);
}


static uint32_t print_struct_siginfo(pid_t child, unsigned long long int value)
{
	siginfo_t	buf;

	if (value == 0)
		return dprintf(2, "NULL");
	if (read_data_from_memory(child, value, sizeof(siginfo_t), &buf) != sizeof(siginfo_t))
		return 0;
	return dprintf(2, "{si_signo=%d, si_code=%d, si_pid=%d, si_uid=%d, "
					  "si_status=%d, si_utime=%ld, si_stime=%ld}",
		buf.si_signo, buf.si_code, buf.si_pid, buf.si_uid, buf.si_status,
		buf.si_utime, buf.si_stime);
}


static uint32_t print_struct_tms(pid_t child, unsigned long long int value)
{
	struct tms	buf;

	if (value == 0)
		return dprintf(2, "NULL");
	if (read_data_from_memory(child, value, sizeof(struct tms), &buf) != sizeof(struct tms))
		return 0;
	return dprintf(2, "{tms_utime=%ld, tms_stime=%ld, tms_cutime=%ld, tms_cstime=%ld}",
		buf.tms_utime, buf.tms_stime, buf.tms_cutime, buf.tms_cstime);
}


static uint32_t print_struct_sigstack(pid_t child, unsigned long long int value)
{
	stack_t	buf;

	if (value == 0)
		return dprintf(2, "NULL");
	if (read_data_from_memory(child, value, sizeof(stack_t), &buf) != sizeof(stack_t))
		return 0;
	return dprintf(2, "{ss_sp=%p, ss_flags=%d, ss_size=%d}",
		buf.ss_sp, buf.ss_flags, buf.ss_flags);
}


static uint32_t print_struct_utimbuf(pid_t child, unsigned long long int value)
{
	struct utimbuf	buf;

	if (value == 0)
		return dprintf(2, "NULL");
	if (read_data_from_memory(child, value, sizeof(struct utimbuf), &buf) != sizeof(struct utimbuf))
		return 0;
	return dprintf(2, "{actime=%ld, modtime=%ld}", buf.actime, buf.modtime);
}


static uint32_t print_struct_shed_param(pid_t child, unsigned long long int value)
{
	struct sched_param	buf;

	if (value == 0)
		return dprintf(2, "NULL");
	if (read_data_from_memory(child, value, sizeof(struct sched_param), &buf) != sizeof(struct sched_param))
		return 0;
	return dprintf(2, "[%d]", buf.sched_priority);
}


uint32_t print_struct_statfs(pid_t child, unsigned long long int value)
{
	struct statfs	buf;

	if (value == 0)
		return dprintf(2, "NULL");
	if (read_data_from_memory(child, value, sizeof(struct statfs), &buf) != sizeof(struct statfs))
		return 0;
	return dprintf(2, "{f_bsize=%lu, f_blocks=%lu, f_bfree=%lu, f_bavail=%lu, "
					  "f_files=%lu, f_ffree=%lu, f_fsid=%d, f_flags=%lu, f_namelen=%lu}",
    buf.f_bsize, buf.f_blocks, buf.f_bfree, buf.f_bavail, buf.f_files,
	buf.f_ffree, buf.f_fsid.__val[0], buf.f_flags, buf.f_namelen);
}


static uint32_t print_struct_sigevent(pid_t child, unsigned long long int value)
{
	struct sigevent	buf;

	if (value == 0)
		return dprintf(2, "NULL");
	if (read_data_from_memory(child, value, sizeof(struct sigevent), &buf) != sizeof(struct sigevent))
		return 0;
	return dprintf(2, "{sigev_signo=%d, sigev_notify=%d}", buf.sigev_signo, buf.sigev_notify);
}


static uint32_t print_struct_itimerspec(pid_t child, unsigned long long int value)
{
	struct itimerspec	buffer;
	uint32_t		ret = 0;

	if (value == 0)
		return dprintf(2, "NULL");
	if (read_data_from_memory(child, value, sizeof(struct itimerspec), &buffer) != sizeof(struct itimerspec))
		return 0;
	return dprintf(2, "{it_interval={tv_sec=%ld, tv_nsec=%ld}, it_value={tv_sec=%ld, tv_nsec=%ld}",
		buffer.it_interval.tv_sec, buffer.it_interval.tv_nsec,
		buffer.it_value.tv_sec, buffer.it_value.tv_nsec);
	return ret;
}


static uint32_t print_struct_mqattr(pid_t child, unsigned long long int value)
{
	struct mq_attr	buf;
	uint32_t		ret = 0;

	if (value == 0)
		return dprintf(2, "NULL");
	if (read_data_from_memory(child, value, sizeof(struct mq_attr), &buf) != sizeof(struct mq_attr))
		return 0;
	return dprintf(2, "{mq_flags=%ld, mq_maxmsg=%ld, mq_msgsize=%ld, mq_curmsgs=%ld}",
		buf.mq_flags, buf.mq_maxmsg, buf.mq_msgsize, buf.mq_curmsgs);
	return ret;
}


static uint32_t print_struct_perfeventattr(pid_t child, unsigned long long int value)
{
	struct perf_event_attr	buf;

	if (value == 0)
		return dprintf(2, "NULL");
	if (read_data_from_memory(child, value, sizeof(struct perf_event_attr), &buf) != sizeof(struct perf_event_attr))
		return 0;
	return dprintf(2, "{type=%d, size=%d, config=%lld, sample_period=%lld, "
					  "sample_type=%lld, read_format=%lld, disabled=%d, exclude_kernel=%d, "
					  "exclude_hv=%d, exclude_idle=%d, precise_ip=%d}",
		buf.type, buf.size, buf.config, buf.sample_period, buf.sample_type,
		buf.read_format, buf.disabled, buf.exclude_kernel, buf.exclude_hv,
		buf.exclude_idle, buf.precise_ip);
}


static uint32_t print_struct_pollfd(pid_t child, unsigned long long int value)
{
	struct pollfd	buffer;

	if (value == 0)
		return dprintf(2, "NULL");
	if (read_data_from_memory(child, value, sizeof(struct pollfd), &buffer) != sizeof(struct pollfd))
		return 0;
	return dprintf(2, "[{fd=%d, events=%d},]", buffer.fd, buffer.events);
}


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
	[FLAG_ACCESS] = print_flag_access,
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
	[VARARGS] = print_str,
	[STRUCT_STAT] = print_struct_stat,
	[STRUCT_SIGACT] = print_struct_sigact,
	[STRUCT_SIGSET] = print_ptr,
	[STRUCT_SIGINF] = print_ptr,
	[STRUCT_IOVEC] = print_struct_iovec,
	[STRUCT_FDSET] = print_ptr,
	[STRUCT_TIMEVAL] = print_struct_timeval,
	[STRUCT_TIMEZONE] = print_struct_timezone,
	[STRUCT_TIMESPEC] = print_struct_timespec,
	[STRUCT_SHMID] = print_ptr,
	[STRUCT_SOCKADDR] = print_ptr,
	[STRUCT_MSGHDR] = print_ptr,
	[STRUCT_RUSAGE] = print_struct_rusage,
	[STRUCT_UTSNAME] = print_struct_utsusage,
	[STRUCT_SEMBUF] = print_struct_sembuf,
	[STRUCT_MSGID] = print_struct_msgid,
	[STRUCT_LINUX_DIR] = print_ptr,
	[STRUCT_RLIMIT] = print_struct_rlimit,
	[STRUCT_SYSINFO] = print_struct_sysinfo,
	[STRUCT_SIGINFO] = print_struct_siginfo,
	[STRUCT_TMS] = print_struct_tms,
	[STRUCT_SIGSTACK] = print_struct_sigstack,
	[STRUCT_UTIMBUF] = print_struct_utimbuf,
	[STRUCT_USTAT] = print_ptr,
	[STRUCT_STATFS] = print_ptr,
	[STRUCT_SCHED_PARAM] = print_struct_shed_param,
	[STRUCT_SYSCTL] = print_ptr,
	[STRUCT_TIMEX] = print_ptr,
	[STRUCT_KERNEL_SYM] = print_ptr,
	[STRUCT_NFSCTL_ARG] = print_ptr,
	[STRUCT_NFSCTL_RES] = print_ptr,
	[STRUCT_STRBUF] = print_ptr,
	[STRUCT_USER_DESC] = print_ptr,
	[STRUCT_IO_EVENT] = print_ptr,
	[STRUCT_IOCB] = print_ptr,
	[STRUCT_SIGEVENT] = print_struct_sigevent,
	[STRUCT_ITIMERSPEC] = print_struct_itimerspec,
	[STRUCT_EPOLL_EVENT] = print_ptr,
	[STRUCT_MQ_ATTR] = print_struct_mqattr,
	[STRUCT_KEXEC_SEGMENT] = print_ptr,
	[STRUCT_PERF_EVENT_ATTR] = print_struct_perfeventattr,
	[STRUCT_MMSGHDR] = print_ptr,
	[STRUCT_FILE_HANDLE] = print_ptr,
	[STRUCT_GETCPU_CACHE] = print_ptr,
	[STRUCT_SCHED_ATTR] = print_ptr,
	[STRUCT_STATX] = print_ptr,
	[STRUCT_PTREGS] = print_ptr,
	[STRUCT_POLLFD] = print_struct_pollfd,
	[STRUCT_ROBUST_LIST_HEAD] = print_str,
	[STRUCT_OLDKERNELSTAT] = print_struct_stat,
	[STRUCT_VM86] = print_ptr, 
	[STRUCT_VM86PLUS] = print_ptr,
	[STRUCT_NEWUTSNAME] = print_ptr,
};


uint32_t	print_type(enum type_e flag, pid_t child, unsigned long long int value)
{
	if (flag <= STRUCT_NEWUTSNAME)
		return f[flag](child, value);
	return 0;
}
