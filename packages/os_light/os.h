#ifndef OS_LIGHT_OS_H
#define OS_LIGHT_OS_H

struct tcb {
	unsigned int sp;
	unsigned int ready_link;
	unsigned int delay_link;
	unsigned int resume_timestamp;
	unsigned int event_link;
	unsigned int event_id; /* semaphore */
};

extern unsigned int system_freq;
extern unsigned int system_tick;

extern struct task_config task_config_array[];
extern struct task_event  task_event_array[];

#endif
