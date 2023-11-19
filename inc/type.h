#ifndef TYPE_H
# define TYPE_H

# include "syscall_64.h"
# include "syscall_32.h"


struct user_regs_struct64
{
	__extension__ unsigned long long int r15;
	__extension__ unsigned long long int r14;
	__extension__ unsigned long long int r13;
	__extension__ unsigned long long int r12;
	__extension__ unsigned long long int rbp;
	__extension__ unsigned long long int rbx;
	__extension__ unsigned long long int r11;
	__extension__ unsigned long long int r10;
	__extension__ unsigned long long int r9;
	__extension__ unsigned long long int r8;
	__extension__ unsigned long long int rax;
	__extension__ unsigned long long int rcx;
	__extension__ unsigned long long int rdx;
	__extension__ unsigned long long int rsi;
	__extension__ unsigned long long int rdi;
	__extension__ unsigned long long int orig_rax;
	__extension__ unsigned long long int rip;
	__extension__ unsigned long long int cs;
	__extension__ unsigned long long int eflags;
	__extension__ unsigned long long int rsp;
	__extension__ unsigned long long int ss;
	__extension__ unsigned long long int fs_base;
	__extension__ unsigned long long int gs_base;
	__extension__ unsigned long long int ds;
	__extension__ unsigned long long int es;
	__extension__ unsigned long long int fs;
	__extension__ unsigned long long int gs;
};

struct user_regs_struct32
{
	long int ebx;
	long int ecx;
	long int edx;
	long int esi;
	long int edi;
	long int ebp;
	long int eax;
	long int xds;
	long int xes;
	long int xfs;
	long int xgs;
	long int orig_eax;
	long int eip;
	long int xcs;
	long int eflags;
	long int esp;
	long int xss;
};


struct type_flag
{
	unsigned long long int 	flag;
	const char				*name;
};


enum type_e
{
	UNDEF = 0,
	INT, // Primitive types
	LONG,
	ULONG,
	PTR,
	STR,
	CONST_STR,
	FLAG_OPEN, // FLag types
	FLAG_OPENAT,
	FLAG_PROT,
	FLAG_MMAP,
	OFF,
	DIRFD,
	PIPE, // Special types
	SV,
	KEY,
	MODE,
	CLOCK,
	PTRACE,
	ID_T,
	DEV,
	TIME,
	SIGNAL,
	ARGV,
	ENVP,
	VARARGS,
	STRUCT_STAT, // Struct types
	STRUCT_POLL,
	STRUCT_SIGACT,
	STRUCT_SIGSET,
	STRUCT_SIGINF,
	STRUCT_IOVEC,
	STRUCT_FDSET,
	STRUCT_TIMEVAL,
	STRUCT_TIMEZONE,
	STRUCT_TIMESPEC,
	STRUCT_SHMID,
	STRUCT_SOCKADDR,
	STRUCT_MSGHDR,
	STRUCT_RUSAGE,
	STRUCT_UTSNAME,
	STRUCT_SEMBUF,
	STRUCT_MSGID,
	STRUCT_LINUX_DIR,
	STRUCT_RLIMIT,
	STRUCT_SYSINFO,
	STRUCT_SIGINFO,
	STRUCT_TMS,
	STRUCT_SIGSTACK,
	STRUCT_UTIMBUF,
	STRUCT_USTAT,
	STRUCT_STATFS,
	STRUCT_SCHED_PARAM,
	STRUCT_SYSCTL,
	STRUCT_TIMEX,
	STRUCT_KERNEL_SYM,
	STRUCT_NFSCTL_ARG,
	STRUCT_NFSCTL_RES,
	STRUCT_STRBUF,
	STRUCT_CPU_SET,
	STRUCT_USER_DESC,
	STRUCT_IO_EVENT,
	STRUCT_IOCB,
	STRUCT_LINUX_DIRENT64,
	STRUCT_SIGEVENT,
	STRUCT_ITIMERSPEC,
	STRUCT_EPOLL_EVENT,
	STRUCT_MQ_ATTR,
	STRUCT_KEXEC_SEGMENT,
	STRUCT_PERF_EVENT_ATTR,
	STRUCT_MMSGHDR,
	STRUCT_FILE_HANDLE,
	STRUCT_GETCPU_CACHE,
	STRUCT_SCHED_ATTR,
	STRUCT_STATX,
	STRUCT_PTREGS,
	STRUCT_POLLFD,
	STRUCT_ROBUST_LIST_HEAD,
	STRUCT_OLDKERNELSTAT,
	STRUCT_VM86,
	STRUCT_VM86PLUS,
	STRUCT_NEWUTSNAME,
};


struct syscall_s
{
	char			*name;
	unsigned int	argc;
	enum type_e		type_args[6];
	enum type_e		type_ret;
};


#endif
