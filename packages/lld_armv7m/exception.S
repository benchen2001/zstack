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

	/* store r4-r7 */
	PUSH {R7}
	PUSH {R6}
	PUSH {R5}
	PUSH {R4}

	/* store r5-r11 in ARMv7A */

	MOV r0, sp
	BL schedule
	MOV sp, r0

	/* restore r4-r7 */
	POP {R4}
	POP {R5}
	POP {R6}
	POP {R7}

	/* restore r5-r11 in ARMv7A */

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

