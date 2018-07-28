#include <string.h>
#include <core.h>
#include <kernel.h>

#include "os.h"

struct mutex mutex_array[CONFIG_MUTEX_NUM];

int mutex_unlock (int id)
{
	int i;
	int mutex_owner;
	
	interrupt_disable();
	
	// if any task pending on it
	if (0 == mutex_array[id].count) {
		for (i=0; i<CONFIG_TASK_NUM; i++) {
			if (tcb_array[i].event_link) {
				tcb_array[i].ready_link = 1;
				tcb_array[i].event_link = 0;
				tcb_array[i].event_id = 0;

				mutex_owner = i;
				break;
			}
		}
		
		// Don't increase it until there are no tasks block on the link
		// TODO: count may grow very large, the max number is?
		if (CONFIG_TASK_NUM == i) {
			interrupt_disable(); // TODO
			return -1;
		}
	}

	/* resume the priority */
	tcb_array[mutex_owner].priority = mutex_array[id].priority;
	
	interrupt_enable();

	software_interrupt(0);

	// NEVER GOES HERE	
	return 0;
}

int mutex_lock (int id)
{
	int mutex_owner;

	interrupt_disable();

	/* if any task hold the lock */
	if (0 == mutex_array[id].owner) { // TODO 0 is IDLE task
		mutex_array[id].owner == current_task;
	}
	
	mutex_owner = mutex_array[id].owner;

	/* check if the same task, eg. task lock twice */
	if (mutex_owner == current_task) {
		interrupt_enable(); // attention
		return -1;
	}

	if (0 == mutex_array[id].count) {

		/* priority reverse check */
		if (tcb_array[mutex_owner].priority < tcb_array[current_task].priority) {
			tcb_array[mutex_owner].priority = tcb_array[current_task].priority + 1;
		}

		tcb_array[current_task].ready_link = 0;
		tcb_array[current_task].event_link = 1;
		tcb_array[current_task].event_id = id;
	}
	else {
		mutex_array[id].count--;
		mutex_array[id].owner = current_task;
		if (mutex_array[id].count < 0) {
			mutex_array[id].count = 0;
		}
	}
	
	interrupt_enable();

	software_interrupt(0);

	// NEVER GOES HERE
	return 0;
}

