#ifndef OS_LIGHT_CORE_H
#define OS_LIGHT_CORE_H

#include <stdint.h>

extern void interrupt_enable (void);
extern void interrupt_disable (void);
extern void software_interrupt (int num);

extern int core_exception_context_size;
extern void core_exception_context_init (uint32_t, uint32_t, uint32_t);

#endif
