#ifndef KERNEL_H
#define KERNEL_H

// There is no task_init or task_create
struct task_config {
	void (*entry)(void);
	unsigned int priority;
	int stacksize;
};

struct task_event {
	int count;
};

struct mutex {
	int count;
	int owner;
	int priority; /* for priority resume */
};

struct mail {
	uint8_t payload[CONFIG_MAIL_SIZE];
}

struct mailbox {
	struct msg queue[CONFIG_MAILBOX_SIZE];	/* if full, block send task, if empty, block recv task */
	int num;				/* the number of mail in box */
	int slot;				/* current slot mail to be put in box */
	int ready;				/* current ready mail to be token, which maybe the highest priority */
};

/* Load user config to initialise kernel objects */
extern void kernel_init (void);
extern unsigned long long schedule (unsigned int sp);

extern void sleep (unsigned int seconds);
extern void msleep (unsigned int ms);

extern int sem_post (int id);
extern int sem_take (int id);

extern int mutex_unlock (int id);
extern int mutex_lock (int id);

#endif
