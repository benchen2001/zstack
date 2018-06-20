#include <printk.h>
#include <kernel.h>
#include <delay.h>

static void Task0(void)
{
	while (1) {
		printk("TASK0\n");
		mdelay(100);
		software_interrupt(0);
	}
}

static void Task1(void)
{
	while (1) {
		printk("TASK1\n");
		mdelay(100);
		software_interrupt(0);
	}
}

static void Task2(void)
{
	while (1) {
		printk("TASK2\n");
		mdelay(100);
		software_interrupt(0);
	}
}

static void TaskIdle(void)
{
	while (1) {
		printk("TASK IDLE\n");
		mdelay(100);
		software_interrupt(0);
	}
}

struct task_config task_config_array[] = {
	{ TaskIdle,	1024 },
	{ Task0,	1024 },
	{ Task1,	1024 },
	{ Task2,	1024 },
	{ 0,		0}
};

int main(void)
{
	kernel_init();
	
	software_interrupt(0);
	while (1);
}

