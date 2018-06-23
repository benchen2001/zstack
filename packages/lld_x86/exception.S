#include "selector.h"

.global irq_entry
.global exception_0

.macro EXCEPTION number
	.global exception_\number

exception_\number:
	push $\number
	jmp exception_entry
.endm

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

exception_entry:
	mov $SS_KERNEL_CODE, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	jmp exception_isr

irq_entry:
	mov $SS_KERNEL_CODE, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	jmp .

exception_0:
	mov $SS_KERNEL_CODE, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs

	/* move core_exception_context from core to task */
	addl $(-4*5), %ebp

	mov 0x0(%esp), %eax
	mov %eax, 0x0(%ebp)
	mov 0x4(%esp), %eax
	mov %eax, 0x4(%ebp)
	mov 0x8(%esp), %eax
	mov %eax, 0x8(%ebp)
	mov 0xc(%esp), %eax
	mov %eax, 0xc(%ebp)
	mov 0x10(%esp), %eax
	mov %eax, 0x10(%ebp)

	pushl %ebp
	call schedule
	mov %eax, %ebp

	/* move core_exception_context from task to core */
	mov 0x0(%ebp), %eax
	mov %eax, 0x0(%esp)
	mov 0x4(%ebp), %eax
	mov %eax, 0x4(%esp)
	mov 0x8(%ebp), %eax
	mov %eax, 0x8(%esp)
	mov 0xc(%ebp), %eax
	mov %eax, 0xc(%esp)
	mov 0x10(%ebp), %eax
	mov %eax, 0x10(%esp)

	addl $(4*5), %ebp

	/* enable irq */
	mov 0x8(%esp), %eax
	orl $0x200, %eax
	mov %eax, 0x8(%esp)
	iret

