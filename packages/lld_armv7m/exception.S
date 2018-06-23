/*
 * thumb_func MUST be added! which generate thumb style function address
 * the compiler option -mthumb take no effect
 */

	.global exception_reset
	.global exception_nmi
	.global exception_hard_fault
	.global exception_mem_manage
	.global exception_bus_fault
	.global exception_usage_fault
	.global exception_reserved
	.global exception_svc
	.global exception_debug_monitor
	.global exception_pendsv
	.global exception_systick
	.global exception_periph

	.thumb_func
exception_reset:
	bl c_start

	.thumb_func
exception_nmi:
	b .

	.thumb_func
exception_hard_fault:
	b .

	.thumb_func
exception_mem_manage:
	b .

	.thumb_func
exception_bus_fault:
	b .

	.thumb_func
exception_usage_fault:
	b .

	.thumb_func
exception_reserved:
	b .

	.thumb_func
exception_svc:
	MOV r0, sp
	BL schedule
	MOV sp, r0

	/* TODO machine treat r7 as bp, auto write to sp?
	 * It seems to be a qemu's bug.
	 */
	MOV r7, r0

	LDR r0, =0xFFFFFFF9
	BX r0

	.thumb_func
exception_debug_monitor:
	b .

	.thumb_func
exception_pendsv:
	b .

	.thumb_func
exception_systick:
	b .

	.thumb_func
exception_periph:
	b .

