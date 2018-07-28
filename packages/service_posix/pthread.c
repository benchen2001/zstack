#include <posix/pthread.h>
#include <core.h>

#include "pthread.h"

struct pthread pthread_array[CONFIG_PTHREAD_NUMBER];

/*
 * as the task must be static defined in os light, here is the default logic
 * it be replaced by pthread_create
 */
void pthread_task_dummy(void *arg)
{
	while (1) {
		sleep(1000);
	}
}

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

int pthread_create(
	pthread_t *restrict pid,
	const pthread_attr_t *restrict attr,
	void *(entry)(void*),
	void *restrict param
	)
{
	int i;

	irq_lock();

	for (i=0; i<CONFIG_PTHREAD_NUMBER; i++) {
		if (NULL == pthread_array[i].entry) {
			pthread_array[i].entry = entry;
			pthread_array[i].param = param;
			memcpy(&pthread_array[i].attr, attr, sizeof(pthread_attr_t));
			*pid = i;
			break;
		}
	}

	irq_unlock();

	if (CONFIG_PTHREAD_NUMBER == i) {
		return -1;
	}

	return 0;
}
