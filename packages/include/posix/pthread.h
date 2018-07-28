#ifndef POSIX_PTHREAD_H
#define POSIX_PTHREAD_H

typedef int pthread_t;

typedef struct {
	int stacksize;
	int priority;
} pthread_attr_t;

extern int pthread_create(pthread_t *restrict, const pthread_attr_t *restrict, void *(*)(void*), void *restrict);

#endif
