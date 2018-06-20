	.global _start
	.extern main
	.extern schedule

#define REG	8

_start:
	LA t0, trap_entry
	CSRW mtvec, t0
	LA sp, stack_top
	J main

trap_entry:
	// store all
	ADDI sp, sp, -REG*32

	SD x1, 0 * REG(sp)
	SD x2, 1 * REG(sp)
	SD x3, 2 * REG(sp)
	SD x4, 3 * REG(sp)
	SD x5, 4 * REG(sp)
	SD x6, 5 * REG(sp)
	SD x7, 6 * REG(sp)
	SD x8, 7 * REG(sp)
	SD x9, 8 * REG(sp)
	SD x10, 9 * REG(sp)
	SD x11, 10 * REG(sp)
	SD x12, 11 * REG(sp)
	SD x13, 12 * REG(sp)
	SD x14, 13 * REG(sp)
	SD x15, 14 * REG(sp)
	SD x16, 15 * REG(sp)
	SD x17, 16 * REG(sp)
	SD x18, 17 * REG(sp)
	SD x19, 18 * REG(sp)
	SD x20, 19 * REG(sp)
	SD x21, 20 * REG(sp)
	SD x22, 21 * REG(sp)
	SD x23, 22 * REG(sp)
	SD x24, 23 * REG(sp)
	SD x25, 24 * REG(sp)
	SD x26, 25 * REG(sp)
	SD x27, 26 * REG(sp)
	SD x28, 27 * REG(sp)
	SD x29, 28 * REG(sp)
	SD x30, 29 * REG(sp)
	SD x31, 30 * REG(sp)
	// store pc to stack
	CSRR t0, mepc
	SD t0, 31 * REG(sp)

	// store sp to TCB and return next task's sp
	MV a0, sp
	JAL schedule
	MV sp, a0

	// reload all
	LD t0, 31 * REG(sp)
	CSRW mepc, t0

	LD x1, 0 * REG(sp)
	LD x3, 2 * REG(sp)
	LD x4, 3 * REG(sp)
	LD x5, 4 * REG(sp)
	LD x6, 5 * REG(sp)
	LD x7, 6 * REG(sp)
	LD x8, 7 * REG(sp)
	LD x9, 8 * REG(sp)
	LD x10, 9 * REG(sp)
	LD x11, 10 * REG(sp)
	LD x12, 11 * REG(sp)
	LD x13, 12 * REG(sp)
	LD x14, 13 * REG(sp)
	LD x15, 14 * REG(sp)
	LD x16, 15 * REG(sp)
	LD x17, 16 * REG(sp)
	LD x18, 17 * REG(sp)
	LD x19, 18 * REG(sp)
	LD x20, 19 * REG(sp)
	LD x21, 20 * REG(sp)
	LD x22, 21 * REG(sp)
	LD x23, 22 * REG(sp)
	LD x24, 23 * REG(sp)
	LD x25, 24 * REG(sp)
	LD x26, 25 * REG(sp)
	LD x27, 26 * REG(sp)
	LD x28, 27 * REG(sp)
	LD x29, 28 * REG(sp)
	LD x30, 29 * REG(sp)
	LD x31, 30 * REG(sp)
	
	ADDI sp, sp, 32 * REG

	MRET

