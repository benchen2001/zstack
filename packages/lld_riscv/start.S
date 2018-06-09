	.global _start
	.global tohost
	.global fromhost
	.extern main

_start:
	LA t0, trap_entry
	CSRW mtvec, t0
	LI sp, 0x80001000
	//ECALL
	J main

trap_entry:
	CSRR t0, mepc
	ADDI t0, t0, 4
	CSRW mepc, t0
	MRET

