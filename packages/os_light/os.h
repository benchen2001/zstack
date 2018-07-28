#ifndef OS_LIGHT_OS_H
#define OS_LIGHT_OS_H

struct tcb {
	unsigned int sp;
	unsigned int priority;
	unsigned int ready_link;
	unsigned int delay_link;
	unsigned int resume_timestamp;
	unsigned int event_link;	/* TODO merge */
	unsigned int event_id;
	unsigned int mutex_link;	/* TODO merge the link with type */
	unsigned int mutex_id;
	unsigned int mailbox_link;	/* TODO merge the link with type */
	unsigned int mailbox_id;
	unsigned int rwlock_link;	/* TODO merge */
	unsigned int rwlock_id;
};

extern unsigned int		system_freq;
extern unsigned int		system_tick;

extern struct task_config	task_config_array[];
extern struct task_event	task_event_array[];

extern struct tcb		tcb_array[CONFIG_TASK_NUM];
extern int			current_task;

extern int			os_freq;
extern int			os_tick;

#endif
