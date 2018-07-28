#ifndef PACKAGE_PTHREAD_H
#define PACKAGE_PTHREAD_H

#include <stdint.h>
#include <posix/pthread.h>
#include <posix/signal.h>

struct pthread {
	void (*entry)(void *arg);
	void *param;
	pthread_attr_t attr;
	uint32_t signal;
	struct sigaction sigaction[CONFIG_SIGNAL_NUMBER];
};

#endif
