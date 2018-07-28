#include <posix/pthread.h>

struct pthread pthread_array[CONFIG_PTHREAD_NUMBER];

void pthread_scheduler_hook(void)
{
	int thread;
	int signal;

	// TODO need more
	for (thread=0; thread<CONFIG_PTHREAD_NUMBER; thread++) {
		if (pthread_array[thread].signal) {
			for (signal=0; signal<CONFIG_SIGNAL_NUMBER; signal++) {
				if (pthread_array[thread].signal & (1<<signal)) {
					pthread_array[thread].sigaction[signal].sa_handler(signal);
				}
			}
		}
	}
}

