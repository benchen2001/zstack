#include <lld/armv7-m.h>

.macro EXCEPTION_ENTRY, name, number
    .global \name
    .thumb_func
\name:
    push {lr}
    ldr r0, =\number
    bl exception_common_entry
    pop {pc}
.endm

EXCEPTION_ENTRY     exception_reset,            #CORE_EXCEPTION_RESET
EXCEPTION_ENTRY     exception_nmi,              #CORE_EXCEPTION_NMI
EXCEPTION_ENTRY     exception_hard_fault,       #CORE_EXCEPTION_HARD_FAULT
EXCEPTION_ENTRY     exception_mem_manage,       #CORE_EXCEPTION_MEM_MANAGE
EXCEPTION_ENTRY     exception_bus_fault,        #CORE_EXCEPTION_BUS_FAULT
EXCEPTION_ENTRY     exception_usage_fault,      #CORE_EXCEPTION_USAGE_FAULT
EXCEPTION_ENTRY     exception_reserved,         #CORE_EXCEPTION_RESERVED
EXCEPTION_ENTRY     exception_svc,              #CORE_EXCEPTION_SVC
EXCEPTION_ENTRY     exception_debug_monitor,    #CORE_EXCEPTION_DEBUG_MONITOR
EXCEPTION_ENTRY     exception_pendsv,           #CORE_EXCEPTION_PENDSV
EXCEPTION_ENTRY     exception_systick,          #CORE_EXCEPTION_SYSTICK
EXCEPTION_ENTRY     exception_periph,           #CORE_EXCEPTION_PERIPH

exception_common_entry:
	bl c_start

