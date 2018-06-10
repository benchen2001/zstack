	.global _start
	.extern main

_start:
	LA t0, trap_entry
	CSRW mtvec, t0
	LI sp, 0x80001000
	J main

trap_entry:
	// store all
	ADDI x0, sp, 0
	JAL schedule
	ADDI sp, x0, 0	// sp
	// reload all
	LUI t1, [sp]	// pc
	CSRW mepc, t1
	MRET

