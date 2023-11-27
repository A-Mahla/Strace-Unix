# Strace-Unix - Lightweight Debugger with System Call Tracing

<br>

![mybadge](https://badgen.net/badge/SKILLS/%20UNIX,%20SYSCALL,%20C%20/red?scale=1.2)

#### This project aims to better understand how GDB handles program tracing.


🔧 System Requirements:
   - Operating System: Linux 64_X86 Distribution
   - Software: [make](https://www.gnu.org/software/make/), [gcc](https://gcc.gnu.org/), [docker](https://www.docker.com/) (optional)

<br>

## Usage



To use it open your terminal and run these commands:

  - To create custom strace binary ```./ft_strace```:

      ```shell
      (cd /path/to/project/directory && make)
      ```

   - To use this custom nm:

      ```shell
      ./ft_strace <prog> <args> ...
      ```

   - For run it if you haven't all libraries required:
      ```shell
      (cd /path/to/project/directory && make run)
      ./ft_strace <prog> <args> ...
      ```

> This is program is made to be compiled and run on a linux x86\_64 system. It
> has not been tested on any other architecture and is not expected to work
> under any other one. However, it is still possible to trace 32bit processes.

<br>

## About

<br>

This program observes a running process and lists each
[system call](https://en.wikipedia.org/wiki/System_call) with the
[ptrace()](https://man7.org/linux/man-pages/man2/ptrace.2.html) function (which
actually is a system call too). After having seized a process it will use the
[waitpid()](https://man7.org/linux/man-pages/man2/wait4.2.html) system call to
wait for events.

<br>

## What is a system call

System calls are a userspace to kernel interface. They allow regular user
processes to access system functionalities. The
[Kernel](https://en.wikipedia.org/wiki/Linux_kernel) is a program that is always
running. It acts as bridge between the OS and the hardware. Thus it handles
everything memory-related, networking, etc... It also spawns and kills
processes or sends signals for example.

They include _open()_, _read()_, _write()_, or _fork()_ and _execve()_... The
complete [list](https://x64.syscall.sh/) contains more than 300 different system
calls. Most of them are accessible through glibc wrapper functions that somewhat
abstract the interface for compatibility between architectures. Some of them do
not have corresponding wrappers and have to be called with the
[syscall()](https://man7.org/linux/man-pages/man2/syscall.2.html) function.

In its most basic form a linux system call is an assembly instruction, an
interruption for legacy 32bit systems and the *syscall* instruction for x86\_64
systems. The particular system called being used is designated by a unique
syscall number that is passed in a particular register (*eax* for i386 and *rax*
for x86\_64). It takes at most 6 parameters through six other registers. On
different processor architectures different syscall numbers and register sets
will be used. Some might even have system calls that do not exist on an other
one. Or they could also implement the same system call in different ways. A
particularly egregious example of that is the _clone()_ system call. It has
[four different definitions](https://github.com/torvalds/linux/blob/master/kernel/fork.c#L3022)
including three that have five parameters in varying order and one with six
parameters.

Most of that is abstracted for the final user that should not have to worry
about it. However it is important to keep in mind when dealing with different
architectures in a low level setting. This one of the reason that ft\_strace
only works on the x86\_64 architecture.

<br>

## How to catch a system call ?

With _ptrace()_. But first you have to *seize* the running process you want to
observe. For that one simply has to use the *PTRACE_SEIZE* request on the pid of
the chosen process:

```C
ptrace(PTRACE_SEIZE, pid, NULL, NULL);
```

Then if the process has appropriate rights, or if the pid corresponds to a child
process, the target process will be traced. If the tracee is not already stopped
it will have to be done with an other *ptrace()* request (*PTRACE_INTERRUPT*).
Then the process can be restarted using this request:

```C
ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
```

It will both restart the process and make it stop on the next syscall entry.
From there ft\_strace simply waits for events with the _wait4()_ function. Every
system call entry and exit of the tracee will be reported back to ft\_strace, as
well as the signals it receives and eventually its death (be it by _exit()_ or
by a signal).

To get the details of a syscall, which one has been called, its parameters and
eventually its return value, the registers of the tracee must be inspected. This
is done with yet an other _ptrace()_ request:

```C
ptrace(PTRACE_GETREGSET, pid, NT_PRSTATUS, &registers);
```

This copies the regular register values (as specified by *NT_PRSTATUS*) of the
process identified by *pid* in the *registers* structure. Then the tracer
process has to interpret the register structure depending on the architecture
to extract the syscall information.
