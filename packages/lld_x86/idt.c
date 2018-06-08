#include <stdint.h>
#include <bitops.h>
#include <printk.h>

#include <lld/interrupt_controller.h>

#include "selector.h"
#include "exception.h"
#include "x86.h"

struct TCB {
	uint32_t ss;
	uint32_t esp;
	uint32_t eflags;
	uint32_t cs;
	uint32_t eip;
};
void task_b_entry (void)
{
	while (1) {
		printk("+");
	}
}
struct TCB tasks[2] = 
{
	{
	.ss = SS_TASK_INIT_DATA,
	.esp = 0x5000,
	.eflags = 0x206,
	.cs = SS_TASK_INIT_CODE,
	.eip = (uint32_t)task_b_entry
	}
};

int curtask = 0;

void idt_common_isr (int num)
{
	if (num >= 32) {
		interrupt_controller_ack();
	}

	if (32 != num) {
		printk("num = %d\n", num);
		while (1);
	}

	printk(".");

#if 1
	// pop num first
	__asm__ ("popl %eax");

#if 1
	if (curtask == 0) {
		curtask = 1;
		__asm__
		(
		"popl %eax;"
		"popl %eax;"
		"popl %eax;"
		"popl %eax;"
		"popl %eax;"

		"pushl $0x23;"
		"pushl $0x6000;"
		"pushl $0x206;"
		"pushl $0x1B;"
		"pushl $0x1373;"
		);
	}
#endif

	__asm__ ("pushl %eax");
#endif
}

struct idt_item interrupt_descriptor_table[256];

/* size should minus 1, to avoid overflow */
struct idt_info interrupt_descriptor_table_info = {
	.size = sizeof(interrupt_descriptor_table) - 1,
	.addr = (uint32_t)interrupt_descriptor_table
};

int idt_register (int no, uint32_t entry)
{
	interrupt_descriptor_table[no].offset_low = entry;
	interrupt_descriptor_table[no].offset_high = entry>>16;

	interrupt_descriptor_table[no].selector = SS_KERNEL_CODE;
	interrupt_descriptor_table[no].attr_gate_type = IDT_INT32;
	interrupt_descriptor_table[no].attr_storage_segment = 0;
	interrupt_descriptor_table[no].attr_dpl = 3;
	interrupt_descriptor_table[no].attr_present = 1;

	return 0;
}

void idt_init(void)
{
	idt_register (0, (uint32_t)exception_0);
	idt_register (1, (uint32_t)exception_1);
	idt_register (2, (uint32_t)exception_2);
	idt_register (3, (uint32_t)exception_3);
	idt_register (4, (uint32_t)exception_4);
	idt_register (5, (uint32_t)exception_5);
	idt_register (6, (uint32_t)exception_6);
	idt_register (7, (uint32_t)exception_7);
	idt_register (8, (uint32_t)exception_8);
	idt_register (9, (uint32_t)exception_9);
	idt_register (10, (uint32_t)exception_10);
	idt_register (11, (uint32_t)exception_11);
	idt_register (12, (uint32_t)exception_12);
	idt_register (13, (uint32_t)exception_13);
	idt_register (14, (uint32_t)exception_14);
	idt_register (15, (uint32_t)exception_15);
	idt_register (16, (uint32_t)exception_16);
	idt_register (17, (uint32_t)exception_17);
	idt_register (18, (uint32_t)exception_18);
	idt_register (19, (uint32_t)exception_19);
	idt_register (20, (uint32_t)exception_20);
	idt_register (21, (uint32_t)exception_21);
	idt_register (22, (uint32_t)exception_22);
	idt_register (23, (uint32_t)exception_23);
	idt_register (24, (uint32_t)exception_24);
	idt_register (25, (uint32_t)exception_25);
	idt_register (26, (uint32_t)exception_26);
	idt_register (27, (uint32_t)exception_27);
	idt_register (28, (uint32_t)exception_28);
	idt_register (29, (uint32_t)exception_29);
	idt_register (30, (uint32_t)exception_30);
	idt_register (31, (uint32_t)exception_31);

	for (int i=32; i<256; i++) {
		idt_register (i, (uint32_t)irq_entry);
	}

	__asm__ ("lidt interrupt_descriptor_table_info");
}

void idt_dump (void)
{
	uint32_t *item = (uint32_t *)interrupt_descriptor_table;

	printk("%08x %08x\n", item[1], item[0]);
	printk("%08x %08x\n", item[3], item[2]);
}

