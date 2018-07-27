#include <string.h>
#include <core.h>
#include <kernel.h>

#include "os.h"

struct mutex mutex_array[CONFIG_MUTEX_NUM];

int mutex_unlock (int id)
{
	int i;
	
	interrupt_disable();
	
	// if any task pending on it
	if (0 == mutex_array[id].count) {
		for (i=0; i<CONFIG_TASK_NUM; i++) {
			if (tcb_array[i].event_link) {
				tcb_array[i].ready_link = 1;
				tcb_array[i].event_link = 0;
				tcb_array[i].event_id = 0;
				break;
			}
		}
		
		// Don't increase it until there are no tasks block on the link
		// TODO: count may grow very large, the max number is?
		if (CONFIG_TASK_NUM == i) {
			mutex_array[id].count++;
		}
	}
	
	interrupt_enable();

	software_interrupt(0);

	// NEVER GOES HERE	
	return 0;
}

int mutex_lock (int id)
{
	interrupt_disable();
	
	if (0 == mutex_array[id].count) {
		tcb_array[current_task].ready_link = 0;
		tcb_array[current_task].event_link = 1;
		tcb_array[current_task].event_id = id;
	}
	else {
		mutex_array[id].count--;
		if (mutex_array[id].count < 0) {
			mutex_array[id].count = 0;
		}
	}
	
	interrupt_enable();

	software_interrupt(0);

	// NEVER GOES HERE
	return 0;
}

