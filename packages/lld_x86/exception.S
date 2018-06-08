#include "selector.h"

	.extern idt_common_isr

	.global irq_entry

.macro EXCEPTION number
	.global exception_\number

exception_\number:
	push $\number
	jmp idt_common_entry
.endm

EXCEPTION 0
EXCEPTION 1
EXCEPTION 2
EXCEPTION 3
EXCEPTION 4
EXCEPTION 5
EXCEPTION 6
EXCEPTION 7
EXCEPTION 8
EXCEPTION 9
EXCEPTION 10
EXCEPTION 11
EXCEPTION 12
EXCEPTION 13
EXCEPTION 14
EXCEPTION 15
EXCEPTION 16
EXCEPTION 17
EXCEPTION 18
EXCEPTION 19
EXCEPTION 20
EXCEPTION 21
EXCEPTION 22
EXCEPTION 23
EXCEPTION 24
EXCEPTION 25
EXCEPTION 26
EXCEPTION 27
EXCEPTION 28
EXCEPTION 29
EXCEPTION 30
EXCEPTION 31

irq_entry:
	pushl $32
	jmp idt_common_entry

idt_common_entry:
	mov $SS_KERNEL_CODE, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	call idt_common_isr
	popl %eax
	iret

