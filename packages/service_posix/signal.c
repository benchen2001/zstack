#include <posix/signal.h>
#include <core.h>

extern int pthread_current_task;
extern struct pthread pthread_array[CONFIG_PTHREAD_NUMBER];

/* the sigaction based on pthread */
void sigaction(int signo, const struct sigaction *restrict new, struct sigaction *restrict old)
{
	irq_lock();

	if (old) {
		memcpy(old, &pthread_array[pthread_current_task].sigaction[signo], sizeof(struct sigaction));
	}

	memcpy(&pthread_array[pthread_current_task].sigaction[signo], new, sizeof(struct sigaction));

	irq_unlock();
}

int kill(pid_t pid, int sig)
{
	irq_lock();

	pthread_array[pid].signal |= (1<<sig);

	irq_unlock();
}

