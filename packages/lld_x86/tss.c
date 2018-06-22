#include <stdint.h>
#include "selector.h"
#include "x86.h"

extern uint32_t section_stack_top;

struct tss_item tss;

void tss_init (void)
{
	// ring 0
	tss.esp0 = &section_stack_top;
	tss.ss0  = SS_KERNEL_DATA;

	// ring 3
	tss.cs   = SS_KERNEL_CODE+3;

	tss.ss   = SS_KERNEL_DATA+3;

	tss.ds   = SS_KERNEL_DATA+3;
	tss.es   = SS_KERNEL_DATA+3;
	tss.fs   = SS_KERNEL_DATA+3;
	tss.gs   = SS_KERNEL_DATA+3;

	__asm__
	(
	"mov $0x28, %ax\n" // TODO
	"ltr %ax"
	);
}

