#include <printk.h>

int main(void)
{
	printk("BareMetal App\n");
	while (1);
}

void __stack_chk_fail_local(void)
{
}

