#ifndef POSIX_PTHREAD_H
#define POSIX_PTHREAD_H

int pthread_create(pthread_t *restrict, const pthread_attr_t *restrict, void *(*)(void*), void *restrict);

#endif
