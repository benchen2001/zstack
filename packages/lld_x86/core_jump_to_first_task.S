#include "selector.h"

	.global core_jump_to_first_task
	.extern first_task_entry

core_jump_to_first_task:

	mov %esp, %eax

	pushl $SS_TASK_INIT_DATA
	pushl %eax
	pushfl
	popl %eax
	orl $0x200, %eax
	pushl %eax
	pushl $SS_TASK_INIT_CODE
	pushl $1f
	iret

1:
	mov $SS_TASK_INIT_DATA, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	jmp first_task_entry

