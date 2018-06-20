#ifndef KERNEL_H
#define KERNEL_H

// There is no task_init or task_create
struct task_config {
	void (*entry)(void);
	int stacksize;
};

struct task_event {
	int type;
	int count;
};

/* Load user config to initialise kernel objects */
extern void kernel_init (void);
extern unsigned long long schedule (unsigned int sp);

extern void sleep (unsigned int seconds);
extern void msleep (unsigned int ms);

extern int sem_post (int id);
extern int sem_take (int id);

#endif
