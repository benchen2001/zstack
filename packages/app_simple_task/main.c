#include <printk.h>
#include <kernel.h>
#include <delay.h>
#include <core.h>
#include <lld/interrupt_controller.h>

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

static void Task2(void)
{
	while (1) {
		printk("TASK2\n");
		//mdelay(100);
		software_interrupt(0);
	}
}

static void Task3(void)
{
	while (1) {
		printk("TASK3\n");
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
	{ TaskIdle,	1024 },
	{ Task0,	1024 },
	{ Task1,	1024 },
	{ Task2,	1024 },
	{ Task3,	1024 },
};

int main(void)
{
	interrupt_controller_init();

	kernel_init();

	software_interrupt(0);
	while (1);
}

void __stack_chk_fail_local(void)
{
}

