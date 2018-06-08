#include <lld/interrupt_controller.h>
#include <lld/timer.h>
#include <lld/core.h>

#include <serial.h>
#include <bss.h>

#include <stdint.h>

#include "x86.h"
#include "irq_map.h"

extern void main (void);

void c_start(void)
{
	/* memory init */
	bss_clear();

	/* core init */
	gdt_init();
	tss_init();
	idt_init();

	main();

	while (1);
}

