#ifndef OS_LIGHT_CONFIG_H
#define OS_LIGHT_CONFIG_H

#define OS_FREQ		(100)	// or 80Hz for realtime

#define TASK_SLOT_NUM	(5)
#define EVENT_SLOT_NUM	(5)

#define TASK_IDLE	(0)

#define OS_STACK_SIZE	(TASK_SLOT_NUM * 1024)

#endif
