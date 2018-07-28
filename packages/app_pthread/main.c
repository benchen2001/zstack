#include <printk.h>
#include <kernel.h>
#include <delay.h>
#include <core.h>
#include <lld/interrupt_controller.h>

extern void pthread_dummy_task(void);

static void Task0(void)
{
	while (1) {
		printk("TASK0\n");
		//mdelay(100);
		software_interrupt(0);
	}
}

static void Task1(void)
{
	while (1) {
		printk("TASK1\n");
		//mdelay(100);
		software_interrupt(0);
	}
}

/* once enter idle mode, it can only be triggered by irq
 * TODO: use pause instruction to stop cpu cycles
 */
static void TaskIdle(void)
{
	while (1);
}

struct task_config task_config_array[CONFIG_TASK_NUM] = {
	{ TaskIdle,		1024 },
	{ Task0,		1024 },
	{ Task1,		1024 },
	{ pthread_task_dummy,	1024 },
	{ pthread_task_dummy,	1024 },
};

static void pthread_task_0(void *arg)
{
	while(1);
}

static void pthread_task_1(void *arg)
{
	while(1);
}

int main(void)
{
	pid_t pid;
	pthread_attr_t attr;

	printk("----- ZStack(%s) -----\n", __TIME__);

	interrupt_controller_init();

	kernel_init();

	// TODO init attr
	pthread_create(&pid, &attr, pthread_task_0, NULL);
	pthread_create(&pid, &attr, pthread_task_1, NULL);

	software_interrupt(0);
	while (1);
}

void __stack_chk_fail_local(void)
{
}

