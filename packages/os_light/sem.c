#include <string.h>
#include <core.h>
#include <kernel.h>

#include "os.h"

struct task_event	event_array[CONFIG_EVENT_NUM];

int sem_post (int id)
{
	int i;
	
	interrupt_disable();
	
	if (0 == event_array[id].count) {
		for (i=0; i<CONFIG_TASK_NUM; i++) {
			if (tcb_array[i].event_link) {
				tcb_array[i].ready_link = 1;
				tcb_array[i].event_link = 0;
				tcb_array[i].event_id = 0;

				/* wake up only one task */
				break;
			}
		}
	}
	
	/* if no task pending on it */
	if (CONFIG_TASK_NUM == i) {
		event_array[id].count++;
	}

	interrupt_enable();

	software_interrupt(0);

	// NEVER GOES HERE	
	return 0;
}

int sem_take (int id)
{
	interrupt_disable();
	
	if (0 == event_array[id].count) {
		tcb_array[current_task].ready_link = 0;
		tcb_array[current_task].event_link = 1;
		tcb_array[current_task].event_id = id;
	}
	else {
		event_array[id].count--;
	}
	
	interrupt_enable();

	software_interrupt(0);

	// NEVER GOES HERE
	return 0;
}

