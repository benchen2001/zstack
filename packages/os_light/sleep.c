#include <string.h>
#include <core.h>
#include <kernel.h>

#include "os.h"

void msleep (unsigned int ms)
{
	interrupt_disable();
	tcb_array[current_task].ready_link = 0;
	tcb_array[current_task].delay_link = 1;
	tcb_array[current_task].resume_timestamp = os_tick + os_freq * ms / 1000;
	interrupt_enable();
	
	software_interrupt(0);
}

void sleep (unsigned int seconds)
{
	msleep(seconds * 1000);
}


