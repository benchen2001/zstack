#include <string.h>
#include <core.h>
#include <kernel.h>

#include "os.h"

int os_freq = CONFIG_OS_FREQ;
int os_tick = 0;

int current_task = -1;

unsigned char		os_stack[CONFIG_OS_STACK_SIZE];
unsigned int		os_stack_top;
unsigned int		os_stack_bottom;

struct tcb		tcb_array[CONFIG_TASK_NUM];

scheduler_hook		scheduler_hook_array[CONFIG_SCHED_HOOK_NUMBER];

static void task_finish(void)
{
	tcb_array[current_task].ready_link = 0;
	software_interrupt(0);
}

void kernel_init (void)
{
	int i;
	uint32_t sp;
	
	// init stack
	memset(os_stack, 0xCC, CONFIG_OS_STACK_SIZE);
	os_stack_bottom = (unsigned int)os_stack;
	os_stack_top = os_stack_bottom + CONFIG_OS_STACK_SIZE;
	
	sp = os_stack_top;
	
	// init TCB
	for (i=0; i<CONFIG_TASK_NUM; i++) {
		if (0 == task_config_array[i].stacksize) {
			tcb_array[i].ready_link = 0;
			continue;
		}
		tcb_array[i].sp = sp - core_exception_context_size;
		tcb_array[i].priority = task_config_array[i].priority;
		tcb_array[i].ready_link = 1;
		tcb_array[i].delay_link = 0;
		tcb_array[i].resume_timestamp = 0;
		tcb_array[i].event_link = 0;
		tcb_array[i].event_id = 0;
		
		sp = sp - task_config_array[i].stacksize;
	}
	
	// init exception return context
	for (i=0; i<CONFIG_TASK_NUM; i++) {
		core_exception_context_init(
			tcb_array[i].sp,
			(uint32_t)task_config_array[i].entry,
			(uint32_t)task_finish
			);
	}
}

unsigned long long schedule (unsigned int sp)
{
	int i;
	int previous_task;
	int high_priority = -1;
	int high_priority_task;
	
	interrupt_disable();
	
	/* If current task is invalid, there is no space to store its sp */
	if (-1 != current_task) {
		tcb_array[current_task].sp = sp;
	}

	/* check hook first */
	for (i=0; i<CONFIG_SCHED_HOOK_NUMBER; i++) {
		if (scheduler_hook_array[i]) {
			scheduler_hook_array[i]();
		}
	}
	
	// Check Delay List: sleep
	for (i=0; i<CONFIG_TASK_NUM; i++) {
		if (tcb_array[i].delay_link && (os_tick >= tcb_array[i].resume_timestamp)) {
			tcb_array[i].delay_link = 0;
			tcb_array[i].resume_timestamp = 0;
			tcb_array[i].ready_link = 1;
		}
	}
	
	previous_task = current_task;
	
	/* Algorithm: Sequence */
	for (i=current_task + 1; i<current_task + CONFIG_TASK_NUM; i++) {
		if (CONFIG_TASK_IDLE == i % CONFIG_TASK_NUM) {
			continue;
		}
		if (tcb_array[i % CONFIG_TASK_NUM].ready_link) {
				if (tcb_array[i % CONFIG_TASK_NUM].priority > high_priority) {
					high_priority = tcb_array[i % CONFIG_TASK_NUM].priority;
					high_priority_task = i % CONFIG_TASK_NUM;
				}
		}
	}

	if (0 != high_priority) {
		current_task = high_priority_task;
	}

	/* If there is no ready task, select IDLE task */
	if (current_task == previous_task) {
		current_task = CONFIG_TASK_IDLE;
	}
	
	interrupt_enable();
	
	return tcb_array[current_task].sp;
}

