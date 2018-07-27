#ifndef POSIX_SIGNAL_H
#define POSIX_SIGNAL_H

enum posix_signal {
	SIGABRT,
	SIGALRM,
	SIGBUS,
	SIGCHLD,
	SIGCONT,
	SIGFPE,
	SIGHUP,
	SIGILL
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

typedef uint32_t sigset_t;
typedef uint32_t siginfo_t;

struct sigaction {
	void		(*sa_handler)(int);				/* pointer to signal-catching function */
	sigset_t 	sa_mask;					/* set of signals */
	int 		sa_flags;					/* special flags*/
	void 		(*sa_sigaction)(int, siginfo_t *, void *);	/* pointer to a signal-catching function */

extern void sigaction(int, const struct sigaction *restrict, struct sigaction *restrict);
extern int raise(int);

#endif
