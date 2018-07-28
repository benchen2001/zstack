#ifndef POSIX_SIGNAL_H
#define POSIX_SIGNAL_H

#include <posix.h>

enum posix_signal {
	SIGABRT,
	SIGALRM,
	SIGBUS,
	SIGCHLD,
	SIGCONT,
	SIGFPE,
	SIGHUP,
	SIGILL,
	SIGINT,
	SIGKILL,
	SIGPIPE,
	SIGQUIT,
	SIGSEGV,
	SIGSTOP,
	SIGTERM,
	SIGTSTP,
	SIGTTIN,
	SIGTTOU,
	SIGUSR1,
	SIGUSR2,
	SIGPOLL,
	SIGPROF,
	SIGSYS,
	SIGTRAP,
	SIGURG,
	SIGVTALRM,
	SIGXCPU,
	SIGXFSZ
};

enum posix_signal_default_proc {
	SIG_PROC_ABRT,
	SIG_PROC_IGNORE,
	SIG_PROC_STOP,
	SIG_PROC_CONTINUE
};

enum {
	SA_NODEF,	/* don't block if in process */
	SA_RESETHAND,	/* after it has been proced with user defined handler, replace with default handler */
	SA_SIGINFO,	/* additional info */
	SA_INTERRUPT,	/* signal proc once */
	SA_RESTART	/* signal proc repeat */
};

typedef uint32_t sigset_t;
typedef uint32_t siginfo_t;

struct sigaction {
	void		(*sa_handler)(int);				/* pointer to signal-catching function */
	sigset_t 	sa_mask;					/* set of signals */
	int 		sa_flags;					/* special flags*/
	void 		(*sa_sigaction)(int, siginfo_t *, void *);	/* handle with thread context, see SA_SIGINFO */
};

/*
 * parameters:
 *   signo: the signal number
 *   signal action: the new action for the signal
 *   old signal action:  if not null, return the previous signal action
 *
 * if the signal has been proced, same signal's action will block, will not miss it
 */
extern void sigaction(int, const struct sigaction *restrict, struct sigaction *restrict);

/*
 * send signal to specified pthread
 */
extern int kill(pid_t pid, int sig);

#endif
