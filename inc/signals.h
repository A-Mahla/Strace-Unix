#ifndef __SIGNALS_H__
# define __SIGNALS_H__

# define SYS_SIGNAME_COUNT 33

# define SYS_SIGNAME { \
	[0] = "", \
	[1] = "SIGHUP", \
	[2] = "SIGINT", \
	[3] = "SIGQUIT", \
	[4] = "SIGILL", \
	[5] = "SIGTRAP", \
	[6] = "SIGABRT", \
	[7] = "SIGBUS", \
	[8] = "SIGFPE", \
	[9] = "SIGKILL", \
	[10] = "SIGUSR1", \
	[11] = "SIGSEGV", \
	[12] = "SIGUSR2", \
	[13] = "SIGPIPE", \
	[14] = "SIGALRM", \
	[15] = "SIGTERM", \
	[16] = "SIGSTKFLT", \
	[17] = "SIGCHLD", \
	[18] = "SIGCONT", \
	[19] = "SIGSTOP", \
	[20] = "SIGTSTP", \
	[21] = "SIGTTIN", \
	[22] = "SIGTTOU", \
	[23] = "SIGURG", \
	[24] = "SIGXCPU", \
	[25] = "SIGXFSZ", \
	[26] = "SIGVTALRM", \
	[27] = "SIGPROF", \
	[28] = "SIGWINCH", \
	[29] = "SIGIO", \
	[30] = "SIGPWR", \
	[31] = "SIGSYS", \
	[32] = "SIGRTMIN", \
	[33] = NULL \
}

# define SI_CODE { \
	[0] = {SI_USER, "SI_USER"}, \
	[1] = {SI_KERNEL, "SI_KERNEL"}, \
	[2] = {SI_QUEUE, "SI_QUEUE"}, \
	[3] = {SI_TIMER, "SI_TIMER"}, \
	[4] = {SI_MESGQ, "SI_MESGQ"}, \
	[5] = {SI_ASYNCIO, "SI_ASYNCIO"}, \
	[6] = {SI_SIGIO, "SI_SIGIO"}, \
	[7] = {SI_TKILL, "SI_TKILL"}, \
	[8] = {0, NULL} \
}

# define ILL_SI_CODE { \
	[0] = {ILL_ILLOPC, "ILL_ILLOPC"}, \
	[1] = {ILL_ILLOPN, "ILL_ILLOPN"}, \
	[2] = {ILL_ILLADR, "ILL_ILLADR"}, \
	[3] = {ILL_ILLTRP, "ILL_ILLTRP"}, \
	[4] = {ILL_PRVOPC, "ILL_PRVOPC"}, \
	[5] = {ILL_PRVREG, "ILL_PRVREG"}, \
	[6] = {ILL_COPROC, "ILL_COPROC"}, \
	[7] = {ILL_BADSTK, "ILL_BADSTK"}, \
	[8] = {0, NULL} \
}

# define FPE_SI_CODE { \
	[0] = {FPE_INTDIV, "FPE_INTDIV"}, \
	[1] = {FPE_INTOVF, "FPE_INTOVF"}, \
	[2] = {FPE_FLTDIV, "FPE_FLTDIV"}, \
	[3] = {FPE_FLTOVF, "FPE_FLTOVF"}, \
	[4] = {FPE_FLTUND, "FPE_FLTUND"}, \
	[5] = {FPE_FLTRES, "FPE_FLTRES"}, \
	[6] = {FPE_FLTINV, "FPE_FLTINV"}, \
	[7] = {FPE_FLTSUB, "FPE_FLTSUB"}, \
	[8] = {0, NULL} \
}

# define SEGV_SI_CODE { \
	[0] = {SEGV_MAPERR, "SEGV_MAPERR"}, \
    [1] = {SEGV_ACCERR, "SEGV_ACCERR"}, \
	[2] = {0, NULL} \
}

# define BUS_SI_CODE { \
	[0] = {BUS_ADRALN, "BUS_ADRALN"}, \
	[1] = {BUS_ADRERR, "BUS_ADRERR"}, \
	[2] = {BUS_OBJERR, "BUS_OBJERR"}, \
	[3] = {0, NULL} \
}

# define TRAP_SI_CODE { \
	[0] = {TRAP_BRKPT, "TRAP_BRKPT"}, \
	[1] = {TRAP_TRACE, "TRAP_TRACE"}, \
	[2] = {0, NULL} \
}

# define CLD_SI_CODE { \
	[0] = {CLD_EXITED, "CLD_EXITED"}, \
	[1] = {CLD_KILLED, "CLD_KILLED"}, \
	[2] = {CLD_DUMPED, "CLD_DUMPED"}, \
	[3] = {CLD_TRAPPED, "CLD_TRAPPED"}, \
	[4] = {CLD_STOPPED, "CLD_STOPPED"}, \
	[5] = {CLD_CONTINUED, "CLD_CONTINUED"}, \
	[6] = {0, NULL} \
}

# define POLL_SI_CODE { \
	[0] = {POLL_IN, "POLL_IN"}, \
	[1] = {POLL_OUT, "POLL_OUT"}, \
	[2] = {POLL_MSG, "POLL_MSG"}, \
	[3] = {POLL_ERR, "POLL_ERR"}, \
	[4] = {POLL_PRI, "POLL_PRI"}, \
	[5] = {POLL_HUP, "POLL_HUP"}, \
	[6] = {0, NULL} \
}

#endif
