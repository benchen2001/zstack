#include <printk.h>

void first_task (void)
{
	printk ("This is the first task running in ring3 mode\n");

	while (1);
}
