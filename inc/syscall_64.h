#ifndef __SYSCALL_64_H__
# define __SYSCALL_64_H__

# define NB_SYSCALL_64 335


# define SYSCALL_64 { \
	[  0] = {"read", 3, {INT, PTR, INT, 0, 0, 0}, INT}, \
	[  1] = {"write", 3, {INT, STR, INT, 0, 0, 0}, INT}, \
	[  2] = {"open", 3, {STR, FLAG_OPEN, 0, 0, 0, 0}, INT}, \
	[  3] = {"close", 1, {INT, 0, 0, 0, 0, 0}, INT}, \
	[  4] = {"stat", 2, {STR, STRUCT_STAT, 0, 0, 0, 0}, INT}, \
	[  5] = {"fstat", 2, {INT, STRUCT_STAT, 0, 0, 0, 0}, INT}, \
	[  6] = {"lstat", 2, {STR, STRUCT_STAT, 0, 0, 0, 0}, INT}, \
	[  7] = {"poll", 3, {STRUCT_POLL, ULONG, INT, 0, 0, 0}, INT}, \
	[  8] = {"lseek", 3, {INT, PTR, INT, 0, 0, 0}, PTR}, \
	[  9] = {"mmap", 6, {PTR, ULONG, FLAG_PROT, FLAG_MMAP, INT, PTR}, PTR}, \
	[ 10] = {"mprotect", 3, {PTR, ULONG, INT, 0, 0, 0}, INT}, \
	[ 11] = {"munmap", 2, {PTR, ULONG, 0, 0, 0, 0}, INT}, \
	[ 12] = {"brk", 1, {PTR, 0, 0, 0, 0, 0}, PTR}, \
	[ 13] = {"rt_sigaction", 3, {SIGNAL, STRUCT_SIGACT, STRUCT_SIGACT, 0, 0, 0}, INT}, \
	[ 14] = {"rt_sigprocmask", 4, {INT, STRUCT_SIGSET, STRUCT_SIGSET, 0, 0, 0}, INT}, \
	[ 15] = {"rt_sigreturn", 0, {0, 0, 0, 0, 0, 0}, INT}, \
	[ 16] = {"ioctl", 3, {INT, ULONG, 0, 0, 0, 0}, INT}, \
	[ 17] = {"pread64", 4, {INT, PTR, ULONG, PTR, 0, 0}, ULONG}, \
	[ 18] = {"pwrite64", 4, {INT, PTR, ULONG, PTR, 0, 0}, ULONG}, \
	[ 19] = {"readv", 3, {INT, STRUCT_IOVEC, INT, 0, 0, 0}, ULONG}, \
	[ 20] = {"writev", 3, {INT, STRUCT_IOVEC, INT, 0, 0, 0}, ULONG}, \
	[ 21] = {"access", 2, {STR, INT, 0, 0, 0, 0}, INT}, \
	[ 22] = {"pipe", 1, {PIPE, INT, 0, 0, 0, 0}, INT}, \
	[ 23] = {"select", 5, {INT, STRUCT_FDSET, STRUCT_FDSET, STRUCT_FDSET, STRUCT_TIMEVAL, 0}, INT}, \
	[ 24] = {"sched_yield", 0, {0, 0, 0, 0, 0, 0}, INT}, \
	[ 25] = {"mremap", 5, {PTR, ULONG, ULONG, INT, PTR, 0}, PTR}, \
	[ 26] = {"msync", 3, {PTR, ULONG, INT, 0, 0, 0}, INT}, \
	[ 27] = {"mincore", 3, {PTR, ULONG, STR, 0, 0, 0}, INT}, \
	[ 28] = {"madvise", 3, {PTR, ULONG, INT, 0, 0, 0}, INT}, \
	[ 29] = {"shmget", 3, {KEY, ULONG, INT, 0, 0, 0}, INT}, \
	[ 30] = {"shmat", 3, {INT, PTR, INT, 0, 0, 0}, INT}, \
	[ 31] = {"shmctl", 3, {INT, INT, STRUCT_SHMID, 0, 0, 0}, INT}, \
	[ 32] = {"dup", 1, {INT, 0, 0, 0, 0, 0}, INT}, \
	[ 33] = {"dup2", 2, {INT, INT, 0, 0, 0, 0}, INT}, \
	[ 34] = {"pause", 0, {0, 0, 0, 0, 0, 0}, INT}, \
	[ 35] = {"nanosleep", 2, {STRUCT_TIMESPEC, STRUCT_TIMESPEC, 0, 0, 0, 0}, INT}, \
	[ 36] = {"getitimer", 2, {INT, STRUCT_TIMEVAL, 0, 0, 0, 0}, INT}, \
	[ 37] = {"alarm", 1, {ULONG, 0, 0, 0, 0, 0}, ULONG}, \
	[ 38] = {"setitimer", 3, {INT, STRUCT_TIMEVAL, STRUCT_TIMEVAL, 0, 0, 0}, INT}, \
	[ 39] = {"getpid", 0, {0, 0, 0, 0, 0, 0}, INT}, \
	[ 40] = {"sendfile", 4, {INT, INT, PTR, ULONG, 0, 0}, ULONG}, \
	[ 41] = {"socket", 3, {INT, INT, INT, 0, 0, 0}, INT}, \
	[ 42] = {"connect", 3, {INT, STRUCT_SOCKADDR, ULONG, 0, 0, 0}, INT}, \
	[ 43] = {"accept", 3, {INT, STRUCT_SOCKADDR, ULONG, 0, 0, 0}, INT}, \
	[ 44] = {"sendto", 6, {INT, PTR, ULONG, INT, STRUCT_SOCKADDR, ULONG}, ULONG}, \
	[ 45] = {"recvfrom", 6, {INT, PTR, ULONG, INT, STRUCT_SOCKADDR, ULONG}, ULONG}, \
	[ 46] = {"sendmsg", 3, {INT, STRUCT_MSGHDR, INT, 0, 0, 0}, ULONG}, \
	[ 47] = {"recvmsg", 3, {INT, STRUCT_MSGHDR, INT, 0, 0, 0}, ULONG}, \
	[ 48] = {"shutdown", 2, {INT, INT, 0, 0, 0, 0}, INT}, \
	[ 49] = {"bind", 3, {INT, STRUCT_SOCKADDR, ULONG, 0, 0, 0}, INT}, \
	[ 50] = {"listen", 2, {INT, INT, 0, 0, 0, 0}, INT}, \
	[ 51] = {"getsockname", 3, {INT, STRUCT_SOCKADDR, ULONG, 0, 0, 0}, INT}, \
	[ 52] = {"getpeername", 3, {INT, STRUCT_SOCKADDR, ULONG, 0, 0, 0}, INT}, \
	[ 53] = {"socketpair", 4, {INT, INT, INT, SV, 0, 0}, INT}, \
	[ 54] = {"setsockopt", 5, {INT, INT, INT, PTR, ULONG, 0}, INT}, \
	[ 55] = {"getsockopt", 5, {INT, INT, INT, PTR, ULONG, 0}, INT}, \
	[ 56] = {"clone", 5, {PTR, PTR, INT, INT, PTR, 0}, INT}, \
	[ 57] = {"fork", 0, {0, 0, 0, 0, 0, 0}, INT}, \
	[ 58] = {"vfork", 0, {0, 0, 0, 0, 0, 0}, INT}, \
	[ 59] = {"execve", 3, {STR, ARGV, ENVP, 0, 0, 0}, INT}, \
	[ 60] = {"exit", 1, {INT, 0, 0, 0, 0, 0}, 0}, \
	[ 61] = {"wait4", 4, {INT, PTR, INT, STRUCT_RUSAGE, 0, 0}, INT}, \
	[ 62] = {"kill", 2, {INT, INT, 0, 0, 0, 0}, INT}, \
	[ 63] = {"uname", 1, {STRUCT_UTSNAME, 0, 0, 0, 0, 0}, INT}, \
	[ 64] = {"semget", 3, {KEY, INT, INT, 0, 0, 0}, INT}, \
	[ 65] = {"semop", 3, {INT, STRUCT_SEMBUF, ULONG, STRUCT_TIMESPEC, 0, 0}, INT}, \
	[ 66] = {"semctl", 4, {INT, INT, INT, 0, 0, 0}, INT}, \
	[ 67] = {"shmdt", 1, {PTR, 0, 0, 0, 0, 0}, INT}, \
	[ 68] = {"msgget", 2, {KEY, INT, 0, 0, 0, 0}, INT}, \
	[ 69] = {"msgsnd", 4, {INT, PTR, ULONG, INT, 0, 0}, INT}, \
	[ 70] = {"msgrcv", 5, {INT, PTR, ULONG, ULONG, INT, 0}, ULONG}, \
	[ 71] = {"msgctl", 3, {INT, INT, STRUCT_MSGID, 0, 0, 0}, INT}, \
	[ 72] = {"fcntl", 3, {INT, INT, 0, 0, 0, 0}, INT}, \
	[ 73] = {"flock", 2, {INT, INT, 0, 0, 0, 0}, INT}, \
	[ 74] = {"fsync", 1, {INT, 0, 0, 0, 0, 0}, INT}, \
	[ 75] = {"fdatasync", 1, {INT, 0, 0, 0, 0, 0}, INT}, \
	[ 76] = {"truncate", 2, {STR, PTR, 0, 0, 0, 0}, INT}, \
	[ 77] = {"ftruncate", 2, {INT, PTR, 0, 0, 0, 0}, INT}, \
	[ 78] = {"getdents", 3, {ULONG, STRUCT_LINUX_DIR, ULONG, 0, 0, 0}, ULONG}, \
	[ 79] = {"getcwd", 2, {PTR, ULONG, 0, 0, 0, 0}, STR}, \
	[ 80] = {"chdir", 1, {STR, 0, 0, 0, 0, 0}, INT}, \
	[ 81] = {"fchdir", 1, {INT, 0, 0, 0, 0, 0}, INT}, \
	[ 82] = {"rename", 2, {STR, STR, 0, 0, 0, 0}, INT}, \
	[ 83] = {"mkdir", 2, {STR, MODE, 0, 0, 0, 0}, INT}, \
	[ 84] = {"rmdir", 1, {STR, 0, 0, 0, 0, 0}, INT}, \
	[ 85] = {"creat", 2, {STR, MODE, 0, 0, 0, 0}, INT}, \
	[ 86] = {"link", 2, {STR, STR, 0, 0, 0, 0}, INT}, \
	[ 87] = {"unlink", 1, {STR, 0, 0, 0, 0, 0}, INT}, \
	[ 88] = {"symlink", 2, {STR, STR, 0, 0, 0, 0}, INT}, \
	[ 89] = {"readlink", 3, {STR, STR, ULONG, 0, 0, 0}, ULONG}, \
	[ 90] = {"chmod", 2, {STR, MODE, 0, 0, 0, 0}, INT}, \
	[ 91] = {"fchmod", 2, {INT, MODE, 0, 0, 0, 0}, 0}, \
	[ 92] = {"chown", 3, {STR, INT, INT, 0, 0, 0}, INT}, \
	[ 93] = {"fchown", 3, {INT, INT, INT, 0, 0, 0}, INT}, \
	[ 94] = {"lchown", 3, {STR, INT, INT, 0, 0, 0}, INT}, \
	[ 95] = {"umask", 1, {MODE, 0, 0, 0, 0, 0}, MODE}, \
	[ 96] = {"gettimeofday", 2, {STRUCT_TIMEVAL, STRUCT_TIMEZONE, 0, 0, 0, 0}, INT}, \
	[ 97] = {"getrlimit", 2, {INT, STRUCT_RLIMIT, 0, 0, 0, 0}, INT}, \
	[ 98] = {"getrusage", 2, {INT, STRUCT_RUSAGE, 0, 0, 0, 0}, INT}, \
	[ 99] = {"sysinfo", 1, {STRUCT_SYSINFO, 0, 0, 0, 0, 0}, INT}, \
	[100] = {"times", 1, {STRUCT_TMS, 0, 0, 0, 0, 0}, CLOCK}, \
	[101] = {"ptrace", 4, {PTRACE, INT, PTR, PTR, 0, 0}, LONG}, \
	[102] = {"getuid", 0, {0, 0, 0, 0, 0, 0}, INT}, \
	[103] = {"syslog", 3, {INT, STR, 0, 0, 0, 0}, INT}, \
	[104] = {"getgid", 0, {0, 0, 0, 0, 0, 0}, INT}, \
	[105] = {"setuid", 1, {INT, 0, 0, 0, 0, 0}, INT}, \
	[106] = {"setgid", 1, {INT, 0, 0, 0, 0, 0}, INT}, \
	[107] = {"geteuid", 0, {0, 0, 0, 0, 0, 0}, INT}, \
	[108] = {"getegid", 0, {0, 0, 0, 0, 0, 0}, INT}, \
	[109] = {"setpgid", 2, {INT, INT, 0, 0, 0, 0}, INT}, \
	[110] = {"getppid", 0, {0, 0, 0, 0, 0, 0}, INT}, \
	[111] = {"getpgrp", 0, {0, 0, 0, 0, 0, 0}, INT}, \
	[112] = {"setsid", 0, {0, 0, 0, 0, 0, 0}, INT}, \
	[113] = {"setreuid", 2, {INT, INT, 0, 0, 0, 0}, INT}, \
	[114] = {"setregid", 2, {INT, INT, 0, 0, 0, 0}, INT}, \
	[115] = {"getgroups", 2, {INT, ID_T, 0, 0, 0, 0}, INT}, \
	[116] = {"setgroups", 2, {INT, ID_T, 0, 0, 0, 0}, INT}, \
	[117] = {"setresuid", 3, {INT, INT, INT, 0, 0, 0}, INT}, \
	[118] = {"getresuid", 3, {PTR, PTR, PTR, 0, 0, 0}, INT}, \
	[119] = {"setresgid", 3, {INT, INT, INT, 0, 0, 0}, INT}, \
	[120] = {"getresgid", 3, {PTR, PTR, PTR, 0, 0, 0}, INT}, \
	[121] = {"getpgid", 1, {INT, 0, 0, 0, 0, 0}, INT}, \
	[122] = {"setfsuid", 1, {INT, 0, 0, 0, 0, 0}, INT}, \
	[123] = {"setfsgid", 1, {INT, 0, 0, 0, 0, 0}, INT}, \
	[124] = {"getsid", 1, {INT, 0, 0, 0, 0, 0}, INT}, \
	[125] = {"capget", 2, {PTR, PTR, 0, 0, 0, 0}, INT}, \
	[126] = {"capset", 2, {PTR, PTR, 0, 0, 0, 0}, INT}, \
	[127] = {"rt_sigpending", 2, {STRUCT_SIGSET, 0, 0, 0, 0, 0}, INT}, \
	[128] = {"rt_sigtimedwait", 4, {STRUCT_SIGSET, STRUCT_SIGINF, 0, 0, 0, 0}, INT}, \
	[129] = {"rt_sigqueueinfo", 3, {INT, INT, STRUCT_SIGINF, 0, 0, 0}, INT}, \
	[130] = {"rt_sigsuspend", 2, {STRUCT_SIGSET, 0, 0, 0, 0, 0}, INT}, \
	[131] = {"sigaltstack", 2, {STRUCT_SIGSTACK, STRUCT_SIGSTACK, 0, 0, 0, 0}, INT}, \
	[132] = {"utime", 2, {STR, STRUCT_UTIMBUF, 0, 0, 0, 0}, INT}, \
	[133] = {"mknod", 3, {STR, MODE, ULONG, 0, 0, 0}, INT}, \
	[134] = {"uselib", 1, {STR, 0, 0, 0, 0, 0}, INT}, \
	[135] = {"personality", 1, {ULONG, 0, 0, 0, 0, 0}, INT}, \
	[136] = {"ustat", 2, {INT, STRUCT_USTAT, 0, 0, 0, 0}, INT}, \
	[137] = {"statfs", 2, {STR, STRUCT_STATFS, 0, 0, 0, 0}, INT}, \
	[138] = {"fstatfs", 2, {INT, STRUCT_STATFS, 0, 0, 0, 0}, INT}, \
	[139] = {"sysfs", 3, {INT, INT, ULONG, 0, 0, 0}, INT}, \
	[140] = {"getpriority", 2, {INT, INT, 0, 0, 0, 0}, INT}, \
	[141] = {"setpriority", 3, {INT, INT, INT, 0, 0, 0}, INT}, \
	[142] = {"sched_setparam", 2, {INT, STRUCT_SCHED_PARAM, 0, 0, 0, 0}, INT}, \
	[143] = {"sched_getparam", 2, {INT, STRUCT_SCHED_PARAM, 0, 0, 0, 0}, INT}, \
	[144] = {"sched_setscheduler", 3, {INT, INT, STRUCT_SCHED_PARAM, 0, 0, 0}, INT}, \
	[145] = {"sched_getscheduler", 1, {INT, 0, 0, 0, 0, 0}, INT}, \
	[146] = {"sched_get_priority_max", 1, {INT, 0, 0, 0, 0, 0}, INT}, \
	[147] = {"sched_get_priority_min", 1, {INT, 0, 0, 0, 0, 0}, INT}, \
	[148] = {"sched_rr_get_interval", 2, {INT, STRUCT_TIMESPEC, 0, 0, 0, 0}, INT}, \
	[149] = {"mlock", 2, {PTR, ULONG, 0, 0, 0, 0}, INT}, \
	[150] = {"munlock", 2, {PTR, ULONG, 0, 0, 0, 0}, INT}, \
	[151] = {"mlockall", 1, {INT, 0, 0, 0, 0, 0}, INT}, \
	[152] = {"munlockall", 0, {0, 0, 0, 0, 0, 0}, INT}, \
	[153] = {"vhangup", 0, {0, 0, 0, 0, 0, 0}, INT}, \
	[154] = {"modify_ldt", 3, {INT, PTR, ULONG, 0, 0, 0}, INT}, \
	[155] = {"pivot_root", 2, {STR, STR, 0, 0, 0, 0}, INT}, \
	[156] = {"_sysctl", 1, {STRUCT_SYSCTL, 0, 0, 0, 0, 0}, INT}, \
	[157] = {"prctl", 5, {INT, ULONG, ULONG, ULONG, ULONG, 0}, INT}, \
	[158] = {"arch_prctl", 2, {PTR, PTR, 0, 0, 0, 0}, INT}, \
	[159] = {"adjtimex", 1, {STRUCT_TIMEX, 0, 0, 0, 0, 0}, INT}, \
	[160] = {"setrlimit", 2, {INT, STRUCT_RLIMIT, 0, 0, 0, 0}, INT}, \
	[161] = {"chroot", 1, {STR, 0, 0, 0, 0, 0}, INT}, \
	[162] = {"sync", 0, {0, 0, 0, 0, 0, 0}, INT}, \
	[163] = {"acct", 1, {STR, 0, 0, 0, 0, 0}, INT}, \
	[164] = {"settimeofday", 2, {STRUCT_TIMEVAL, STRUCT_TIMEZONE, 0, 0, 0, 0}, INT}, \
	[165] = {"mount", 5, {STR, STR, STR, ULONG, PTR, 0}, INT}, \
	[166] = {"umount2", 2, {STR, INT, 0, 0, 0, 0}, INT}, \
	[167] = {"swapon", 2, {STR, INT, 0, 0, 0, 0}, INT}, \
	[168] = {"swapoff", 1, {STR, 0, 0, 0, 0, 0}, INT}, \
	[169] = {"reboot", 4, {INT, INT, INT, PTR, 0, 0}, 0}, \
	[170] = {"sethostname", 2, {STR, ULONG, 0, 0, 0, 0}, INT}, \
	[171] = {"setdomainname", 2, {STR, ULONG, 0, 0, 0, 0}, INT}, \
	[172] = {"iopl", 1, {INT, 0, 0, 0, 0, 0}, INT}, \
	[173] = {"ioperm", 3, {ULONG, ULONG, INT, 0, 0, 0}, INT}, \
	[174] = {"create_module", 2, {STR, ULONG, 0, 0, 0, 0}, PTR}, \
	[175] = {"init_module", 3, {PTR, ULONG, STR, 0, 0, 0}, INT}, \
	[176] = {"delete_module", 2, {STR, INT, 0, 0, 0, 0}, INT}, \
	[177] = {"get_kernel_syms", 1, {STRUCT_KERNEL_SYM, 0, 0, 0, 0, 0}, INT}, \
	[178] = {"query_module", 5, {STR, INT, PTR, ULONG, ULONG, 0}, INT}, \
	[179] = {"quotactl", 4, {INT, STR, INT, PTR, 0, 0}, INT}, \
	[180] = {"nfsservctl", 3, {INT, STRUCT_NFSCTL_ARG, STRUCT_NFSCTL_RES, 0, 0, 0}, LONG}, \
	[181] = {"getpmsg", 5, {INT, STRUCT_STRBUF, STRUCT_STRBUF, INT, PTR, 0}, INT}, \
	[182] = {"putpmsg", 5, {INT, STRUCT_STRBUF, STRUCT_STRBUF, INT, PTR, 0}, INT}, \
	[183] = {"afs_syscall", 0, {0, 0, 0, 0, 0, 0}, INT}, \
	[184] = {"tuxcall", 0, {0, 0, 0, 0, 0, 0}, INT}, \
	[185] = {"security", 0, {0, 0, 0, 0, 0, 0}, INT}, \
	[186] = {"gettid", 0, {0, 0, 0, 0, 0, 0}, INT}, \
	[187] = {"readahead", 3, {INT, INT, ULONG, 0, 0, 0}, LONG}, \
	[188] = {"setxattr", 5, {STR, STR, PTR, ULONG, INT, 0}, INT}, \
	[189] = {"lsetxattr", 5, {STR, STR, PTR, ULONG, INT, 0}, INT}, \
	[190] = {"fsetxattr", 5, {INT, STR, PTR, ULONG, INT, 0}, INT}, \
	[191] = {"getxattr", 4, {STR, STR, PTR, ULONG, 0, 0}, LONG}, \
	[192] = {"lgetxattr", 4, {STR, STR, PTR, ULONG, 0, 0}, LONG}, \
	[193] = {"fgetxattr", 4, {INT, STR, PTR, ULONG, 0, 0}, LONG}, \
	[194] = {"listxattr", 3, {STR, STR, ULONG, 0, 0, 0}, LONG}, \
	[195] = {"llistxattr", 3, {STR, STR, ULONG, 0, 0, 0}, LONG}, \
	[196] = {"flistxattr", 3, {INT, STR, ULONG, 0, 0, 0}, LONG}, \
	[197] = {"removexattr", 2, {STR, STR, 0, 0, 0, 0}, INT}, \
	[198] = {"lremovexattr", 2, {STR, STR, 0, 0, 0, 0}, INT}, \
	[199] = {"fremovexattr", 2, {INT, STR, 0, 0, 0, 0}, INT}, \
	[200] = {"tkill", 2, {INT, INT, 0, 0, 0, 0}, INT}, \
	[201] = {"time", 1, {PTR, 0, 0, 0, 0, 0}, LONG}, \
	[202] = {"futex", 6, {PTR, INT, INT, STRUCT_TIMESPEC, PTR, INT}, INT}, \
	[203] = {"sched_setaffinity", 3, {INT, ULONG, STRUCT_CPU_SET, 0, 0, 0}, INT}, \
	[204] = {"sched_getaffinity", 3, {INT, ULONG, STRUCT_CPU_SET, 0, 0, 0}, INT}, \
	[205] = {"set_thread_area", 1, {STRUCT_USER_DESC, 0, 0, 0, 0, 0}, INT}, \
	[206] = {"io_setup", 2, {ULONG, PTR, 0, 0, 0, 0}, INT}, \
	[207] = {"io_destroy", 1, {INT, 0, 0, 0, 0, 0}, INT}, \
	[208] = {"io_getevents", 5, {INT, LONG, LONG, STRUCT_IO_EVENT, STRUCT_TIMESPEC, 0}, INT}, \
	[209] = {"io_submit", 3, {INT, LONG, PTR, 0, 0, 0}, INT}, \
	[210] = {"io_cancel", 3, {INT, STRUCT_IOCB, STRUCT_IO_EVENT, 0, 0, 0}, INT}, \
	[211] = {"get_thread_area", 1, {STRUCT_USER_DESC, 0, 0, 0, 0, 0}, INT}, \
	[212] = {"lookup_dcookie", 3, {ULONG, STR, ULONG, 0, 0, 0}, INT}, \
	[213] = {"epoll_create", 1, {INT, 0, 0, 0, 0, 0}, INT}, \
	[214] = {"epoll_ctl_old", 0, {0, 0, 0, 0, 0, 0}, INT}, \
	[215] = {"epoll_wait_old", 0, {0, 0, 0, 0, 0, 0}, INT}, \
	[216] = {"remap_file_pages", 5, {PTR, ULONG, INT, ULONG, INT, 0}, INT}, \
	[217] = {"getdents64", 3, {ULONG, STRUCT_LINUX_DIRENT64, ULONG, 0, 0, 0}, ULONG}, \
	[218] = {"set_tid_address", 1, {INT, 0, 0, 0, 0, 0}, LONG}, \
	[219] = {"restart_syscall", 0, {0, 0, 0, 0, 0, 0}, INT}, \
	[220] = {"semtimedop", 4, {INT, STRUCT_SEMBUF, ULONG, STRUCT_TIMESPEC, 0, 0}, INT}, \
	[221] = {"fadvise64", 4, {INT, ULONG, ULONG, INT, 0, 0}, INT}, \
	[222] = {"timer_create", 3, {INT, STRUCT_SIGEVENT, PTR, 0, 0, 0}, INT}, \
	[223] = {"timer_settime", 4, {INT, INT, STRUCT_ITIMERSPEC, STRUCT_ITIMERSPEC, 0, 0}, INT}, \
	[224] = {"timer_gettime", 2, {INT, STRUCT_ITIMERSPEC, 0, 0, 0, 0}, INT}, \
	[225] = {"timer_getoverrun", 1, {INT, 0, 0, 0, 0, 0}, INT}, \
	[226] = {"timer_delete", 1, {INT, 0, 0, 0, 0, 0}, INT}, \
	[227] = {"clock_settime", 2, {CLOCK, STRUCT_TIMESPEC, 0, 0, 0, 0}, INT}, \
	[228] = {"clock_gettime", 2, {CLOCK, STRUCT_TIMESPEC, 0, 0, 0, 0}, INT}, \
	[229] = {"clock_getres", 2, {CLOCK, STRUCT_TIMESPEC, 0, 0, 0, 0}, INT}, \
	[230] = {"clock_nanosleep", 4, {CLOCK, INT, STRUCT_TIMESPEC, STRUCT_TIMESPEC, 0, 0}, INT}, \
	[231] = {"exit_group", 1, {INT, 0, 0, 0, 0, 0}, 0}, \
	[232] = {"epoll_wait", 4, {INT, STRUCT_EPOLL_EVENT, INT, INT, 0, 0}, INT}, \
	[233] = {"epoll_ctl", 4, {INT, INT, INT, STRUCT_EPOLL_EVENT, 0, 0}, INT}, \
	[234] = {"tgkill", 3, {INT, INT, INT, 0, 0, 0}, INT}, \
	[235] = {"utimes", 2, {STR, STRUCT_TIMEVAL, 0, 0, 0, 0}, INT}, \
	[236] = {"vserver", 0, {0, 0, 0, 0, 0, 0}, INT}, \
	[237] = {"mbind", 6, {PTR, ULONG, INT, PTR, ULONG, ULONG}, INT}, \
	[238] = {"set_mempolicy", 3, {INT, PTR, ULONG, 0, 0, 0}, INT}, \
	[239] = {"get_mempolicy", 5, {PTR, PTR, ULONG, ULONG, ULONG, 0}, INT}, \
	[240] = {"mq_open", 4, {STR, INT, MODE, STRUCT_MQ_ATTR, 0, 0}, INT}, \
	[241] = {"mq_unlink", 1, {STR, 0, 0, 0, 0, 0}, INT}, \
	[242] = {"mq_timedsend", 5, {INT, STR, ULONG, ULONG, STRUCT_TIMESPEC, 0}, INT}, \
	[243] = {"mq_timedreceive", 5, {INT, STR, ULONG, ULONG, STRUCT_TIMESPEC, 0}, ULONG}, \
	[244] = {"mq_notify", 2, {INT, STRUCT_SIGEVENT, 0, 0, 0, 0}, INT}, \
	[245] = {"mq_getsetattr", 3, {INT, STRUCT_MQ_ATTR, STRUCT_MQ_ATTR, 0, 0, 0}, INT}, \
	[246] = {"kexec_load", 4, {ULONG, ULONG, STRUCT_KEXEC_SEGMENT, ULONG, 0, 0}, LONG}, \
	[247] = {"waitid", 4, {INT, INT, STRUCT_SIGINFO, INT, 0, 0}, INT}, \
	[248] = {"add_key", 5, {STR, STR, PTR, ULONG, INT, 0}, LONG}, \
	[249] = {"request_key", 4, {STR, STR, STR, INT, 0, 0}, LONG}, \
	[250] = {"keyctl", 2, {INT, VARARGS, 0, 0, 0, 0}, LONG}, \
	[251] = {"ioprio_set", 3, {INT, INT, INT, 0, 0, 0}, INT}, \
	[252] = {"ioprio_get", 2, {INT, INT, 0, 0, 0, 0}, INT}, \
	[253] = {"inotify_init", 0, {0, 0, 0, 0, 0, 0}, INT}, \
	[254] = {"inotify_add_watch", 3, {INT, STR, ULONG, 0, 0, 0}, INT}, \
	[255] = {"inotify_rm_watch", 2, {INT, INT, 0, 0, 0, 0}, INT}, \
	[256] = {"migrate_pages", 4, {INT, ULONG, PTR, PTR, 0, 0}, LONG}, \
	[257] = {"openat", 3, {INT, STR, INT, 0, 0, 0}, INT}, \
	[258] = {"mkdirat", 3, {INT, STR, MODE, 0, 0, 0}, INT}, \
	[259] = {"mknodat", 4, {INT, STR, MODE, ULONG, 0, 0}, INT}, \
	[260] = {"fchownat", 5, {INT, STR, INT, INT, INT, 0}, INT}, \
	[261] = {"futimesat", 3, {INT, STR, STRUCT_TIMEVAL, 0, 0, 0}, INT}, \
	[262] = {"newfstatat", 4, {INT, STR, STRUCT_STAT, INT, 0, 0}, INT}, \
	[263] = {"unlinkat", 3, {INT, STR, INT, 0, 0, 0}, INT}, \
	[264] = {"renameat", 4, {INT, STR, INT, STR, 0, 0}, INT}, \
	[265] = {"linkat", 5, {INT, STR, INT, STR, INT, 0}, INT}, \
	[266] = {"symlinkat", 3, {STR, INT, STR, 0, 0, 0}, INT}, \
	[267] = {"readlinkat", 4, {INT, STR, STR, ULONG, 0, 0}, INT}, \
	[268] = {"fchmodat", 3, {INT, STR, MODE, 0, 0, 0}, INT}, \
	[269] = {"faccessat", 3, {INT, STR, INT, 0, 0, 0}, INT}, \
	[270] = {"pselect6", 6, {INT, PTR, PTR, PTR, STRUCT_TIMESPEC, PTR}, INT}, \
	[271] = {"ppoll", 5, {STRUCT_POLLFD, ULONG, STRUCT_TIMESPEC, STRUCT_SIGSET, ULONG, 0}, INT}, \
	[272] = {"unshare", 1, {INT, 0, 0, 0, 0, 0}, INT}, \
	[273] = {"set_robust_list", 2, {STRUCT_ROBUST_LIST_HEAD, ULONG, 0, 0, 0, 0}, LONG}, \
	[274] = {"get_robust_list", 3, {INT, STRUCT_ROBUST_LIST_HEAD, ULONG, 0, 0, 0}, LONG}, \
	[275] = {"splice", 6, {INT, PTR, INT, PTR, ULONG, ULONG}, LONG}, \
	[276] = {"tee", 4, {INT, INT, ULONG, ULONG, 0, 0}, LONG}, \
	[277] = {"sync_file_range", 4, {INT, ULONG, ULONG, ULONG, 0, 0}, LONG}, \
	[278] = {"vmsplice", 4, {INT, STRUCT_IOVEC, ULONG, ULONG, 0, 0}, LONG}, \
	[279] = {"move_pages", 6, {INT, ULONG, PTR, INT, INT, INT}, LONG}, \
	[280] = {"utimensat", 4, {INT, STR, STRUCT_TIMESPEC, INT, 0, 0}, INT}, \
	[281] = {"epoll_pwait", 6, {INT, STRUCT_EPOLL_EVENT, INT, INT, STRUCT_SIGSET, ULONG}, INT}, \
	[282] = {"signalfd", 3, {INT, PTR, INT, 0, 0, 0}, INT}, \
	[283] = {"timerfd_create", 2, {INT, INT, 0, 0, 0, 0}, INT}, \
	[284] = {"eventfd", 1, {INT, 0, 0, 0, 0, 0}, INT}, \
	[285] = {"fallocate", 4, {INT, INT, ULONG, ULONG, 0, 0}, INT}, \
	[286] = {"timerfd_settime", 4, {INT, INT, STRUCT_ITIMERSPEC, STRUCT_ITIMERSPEC, 0, 0}, INT}, \
	[287] = {"timerfd_gettime", 2, {INT, STRUCT_ITIMERSPEC, 0, 0, 0, 0}, INT}, \
	[288] = {"accept4", 4, {INT, STRUCT_SOCKADDR, ULONG, INT, 0, 0}, INT}, \
	[289] = {"signalfd4", 4, {INT, PTR, ULONG, INT, 0, 0}, INT}, \
	[290] = {"eventfd2", 2, {INT, INT, 0, 0, 0, 0}, INT}, \
	[291] = {"epoll_create1", 1, {INT, 0, 0, 0, 0, 0}, INT}, \
	[292] = {"dup3", 3, {INT, INT, INT, 0, 0, 0}, INT}, \
	[293] = {"pipe2", 2, {INT, INT, 0, 0, 0, 0}, INT}, \
	[294] = {"inotify_init1", 1, {INT, 0, 0, 0, 0, 0}, INT}, \
	[295] = {"preadv", 4, {INT, STRUCT_IOVEC, ULONG, ULONG, 0, 0}, LONG}, \
	[296] = {"pwritev", 4, {INT, STRUCT_IOVEC, ULONG, ULONG, 0, 0}, LONG}, \
	[297] = {"rt_tgsigqueueinfo", 4, {INT, INT, INT, STRUCT_SIGINFO, 0, 0}, INT}, \
	[298] = {"perf_event_open", 5, {STRUCT_PERF_EVENT_ATTR, INT, INT, INT, ULONG, 0}, INT}, \
	[299] = {"recvmmsg", 5, {INT, STRUCT_MMSGHDR, ULONG, ULONG, STRUCT_TIMESPEC, 0}, INT}, \
	[300] = {"fanotify_init", 2, {ULONG, ULONG, 0, 0, 0, 0}, INT}, \
	[301] = {"fanotify_mark", 5, {INT, ULONG, ULONG, INT, STR, 0}, INT}, \
	[302] = {"prlimit64", 4, {INT, INT, STRUCT_RLIMIT, STRUCT_RLIMIT, 0, 0}, INT}, \
	[303] = {"name_to_handle_at", 5, {INT, STR, STRUCT_FILE_HANDLE, INT, INT, 0}, INT}, \
	[304] = {"open_by_handle_at", 3, {INT, STRUCT_FILE_HANDLE, INT, 0, 0, 0}, INT}, \
	[305] = {"clock_adjtime", 2, {CLOCK, STRUCT_TIMEX, 0, 0, 0, 0}, INT}, \
	[306] = {"syncfs", 1, {INT, 0, 0, 0, 0, 0}, INT}, \
	[307] = {"sendmmsg", 4, {INT, STRUCT_MMSGHDR, ULONG, ULONG, 0, 0}, INT}, \
	[308] = {"setns", 2, {INT, INT, 0, 0, 0, 0}, INT}, \
	[309] = {"getcpu", 3, {PTR, PTR, STRUCT_GETCPU_CACHE, 0, 0, 0}, INT}, \
	[310] = {"process_vm_readv", 6, {INT, STRUCT_IOVEC, ULONG, STRUCT_IOVEC, ULONG, ULONG}, LONG}, \
	[311] = {"process_vm_writev", 6, {INT, STRUCT_IOVEC, ULONG, STRUCT_IOVEC, ULONG, ULONG}, LONG}, \
	[312] = {"kcmp", 5, {INT, INT, INT, ULONG, ULONG, 0}, INT}, \
	[313] = {"finit_module", 3, {INT, STR, INT, 0, 0, 0}, INT}, \
	[314] = {"sched_setattr", 3, {INT, STRUCT_SCHED_ATTR, ULONG, 0, 0, 0}, INT}, \
	[315] = {"sched_getattr", 4, {INT, STRUCT_SCHED_ATTR, ULONG, ULONG, 0, 0}, INT}, \
	[316] = {"renameat2", 5, {INT, STR, INT, STR, ULONG, 0}, INT}, \
	[317] = {"seccomp", 3, {ULONG, ULONG, PTR, 0, 0, 0}, INT}, \
	[318] = {"getrandom", 3, {STR, ULONG, ULONG, 0, 0, 0}, INT}, \
	[319] = {"memfd_create", 2, {STR, ULONG, 0, 0, 0, 0}, INT}, \
	[320] = {"kexec_file_load", 5, {INT, INT, ULONG, STR, ULONG, 0}, LONG}, \
	[321] = {"bpf", 3, {INT, PTR, ULONG, 0, 0, 0}, INT}, \
	[322] = {"execveat", 5, {INT, STR, STR, STR, INT, 0}, INT}, \
	[323] = {"userfaultfd", 1, {INT, 0, 0, 0, 0, 0}, INT}, \
	[324] = {"membarrier", 2, {INT, INT, 0, 0, 0, 0}, INT}, \
	[325] = {"mlock2", 3, {PTR, ULONG, INT, 0, 0, 0}, INT}, \
	[326] = {"copy_file_range", 6, {INT, ULONG, INT, ULONG, ULONG, ULONG}, LONG}, \
	[327] = {"preadv2", 6, {INT, STRUCT_IOVEC, ULONG, ULONG, ULONG, INT}, LONG}, \
	[328] = {"pwritev2", 6, {INT, STRUCT_IOVEC, ULONG, ULONG, ULONG, INT}, LONG}, \
	[329] = {"pkey_mprotect", 4, {PTR, ULONG, INT, INT, 0, 0}, INT}, \
	[330] = {"pkey_alloc", 2, {ULONG, ULONG, 0, 0, 0, 0}, INT}, \
	[331] = {"pkey_free", 1, {INT, 0, 0, 0, 0, 0}, INT}, \
	[332] = {"statx", 5, {INT, STR, INT, ULONG, STRUCT_STATX, 0}, INT}, \
	[333] = {"io_pgetevents", 6, {INT, INT, INT, STRUCT_IOCB, STRUCT_TIMESPEC, STRUCT_TIMESPEC}, INT}, \
	[334] = {"rseq", 1, {PTR, 0, 0, 0, 0, 0}, INT}, \
}

#endif
