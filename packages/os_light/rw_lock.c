/*
 * Writer has higher priority then reader.
 */

#include <string.h>
#include <core.h>
#include <kernel.h>

#include "os.h"

struct task_event	event_array[CONFIG_EVENT_NUM];

int rwlock_unlock (int id)
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

/*
 * put the readers into queue, only one can take the read sem, the other readers wait out of the door
 * which gives the writer the chance to close the door before all the readers complete work.
 */
int rwlock_read_lock (int id)
{
	sem_take(SEM_READER_OUTDOOR);
	sem_take(SEM_READER_REQUEST_ENTER);

	sem_take(SEM_UPDATE_READER);
	rwlock_array[id].read_count++;

	/* wait for writer out, and close the door */
	if (1 == rwlock_array[id].read_count) {
		sem_take(SEM_WRITER);
	}

	sem_post(SEM_UPDATE_READER);

	sem_post(SEM_READER_REQUEST_ENTER);
	sem_post(SEM_READER_OUTDOOR);

	return 0;
}

int rwlock_read_unlock (int id)
{
	sem_take(SEM_UPDATE_READER);

	rwlock_array[id].reader_count--;

	/* open the reader door */
	if (rwlock_array[id].reader_count <= 0) {
		sem_post(SEM_WRITER);
	}

	sem_post(SEM_UPDATE_READER);

	return 0;
}

int rwlock_write_lock (int id)
{
	sem_take(SEM_UPDATE);

	rwlock_array[id].count++;

	/* wait for reader out, and close the door */
	if (1 == rwlock_array[id].count) {
		sem_take(SEM_READER);
	}

	sem_post(SEM_UPDATE);

	sem_take(SEM_WRITER);

	return 0;
}

int rwlock_write_unlock (int id)
{
	/* open the writer door */
	sem_post(SEM_WRITER);

	sem_take(SEM_UPDATE);

	rwlock_array[id].count--;

	/* open the reader door */
	if (rwlock_array[id].count <= 0) {
		sem_post(SEM_READER);
	}

	sem_post(SEM_UPDATE);

	return 0;
}

