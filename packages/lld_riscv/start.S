	.global _start
	.global tohost
	.global fromhost
	.extern main

_start:
	LA t0, trap_entry
	CSRW mtvec, t0
	ECALL
	J main

trap_entry:
	CSRR t0, mepc
	ADDI t0, t0, 4
	CSRW mepc, t0
	MRET

putc:
	LI t0, 0x10030
	LA t1, tohost
	SW t0, (t1)

	.align 4

tohost:
	.word 0

fromhost:
	.word 0

