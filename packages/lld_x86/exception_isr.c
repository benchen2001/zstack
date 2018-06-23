#include <printk.h>

void exception_isr(int num)
{
	printk("exception: %d\n", num);
	while (1);
}

