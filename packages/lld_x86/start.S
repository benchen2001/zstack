#include "selector.h"

    .global start
    .extern section_stack_top
    .extern interrupt_descriptor_table_info
    .extern c_start

/*---------------------------------------------------------------------------*/

    .code16

    .section .start, "ax"

start:

prepare_enter_protection_mode:

    /* MUST disable interrupt before enter protection mode */
    cli

    /* enable A20 signal */
    inb $0x92, %al
    orb $0x2, %al
    outb %al, $0x92

    lgdt gdt_desc

    /* enable protection mode */
    movl %cr0, %eax
    orl $0x1, %eax
    movl %eax, %cr0

    /* jump to first instruction in protection mode, this will change cs */
    ljmp $SS_KERNEL_CODE, $protection_mode_start

/*---------------------------------------------------------------------------*/

gdt: 
    .quad 0x0000000000000000 
    .quad 0x00CF9A000000FFFF
    .quad 0x00CF92000000FFFF

gdt_desc: 
    .short 8*3-1
    .long gdt

/*---------------------------------------------------------------------------*/

    .code32

protection_mode_start:

prepare_enter_c_mode:
    /* reset data segment */
    mov $SS_KERNEL_DATA, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss

    /* prepare stack */
    mov $section_stack_top, %esp
    mov %esp, %ebp

    jmp c_start

