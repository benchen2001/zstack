/*
 * The vector table should have 256 words.
 *
 * The first word is stack top, auto loaded into SP register.
 *
 * The others are 255 vectors NVIC supported.
 */

#include "config.h"

    .section .vectors, "a", %progbits

vector_table:
    .word section_stack_end     /* => MSP */
    .word exception_reset       /* => PC  */
    .word exception_nmi
    .word exception_hard_fault
    .word exception_mem_manage
    .word exception_bus_fault
    .word exception_usage_fault
    .word exception_reserved
    .word exception_reserved
    .word exception_reserved
    .word exception_reserved
    .word exception_svc
    .word exception_debug_monitor
    .word exception_reserved
    .word exception_pendsv
    .word exception_systick

    .rept CONFIG_CPU_V7M_NUM_IRQ
    .word exception_periph
    .endr

