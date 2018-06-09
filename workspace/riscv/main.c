#include <stdint.h>
#include <printk.h>

int main(void)
{
	printk("Hello World: %d\n", 0xaa);

	while (1);

	return 0;
}

