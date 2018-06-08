#include "registers.h"
#include "registers-base.h"
#include "nvic.h"

#include <stdint.h>

/*
 * If irq < 0, it is a system interrupt, otherwise it is a device interrupt.
 */
void nvic_set_priority(int irq, int priority)
{
    if (irq < 0) {
        scb->shp[(uint32_t)irq & 0xF - 4] = (priority << (8-NVIC_PRIO_BITS)) & 0xFF;
    }
    else {
        nvic->ip[irq] = priority << (8-NVIC_PRIO_BITS) & 0xFF;
    }
}

uint32_t nvic_get_priority(int irq)
{
    uint32_t value;

    if (irq < 0) {
        value = scb->shp[(uint32_t)irq & 0xF - 4] >> (8-NVIC_PRIO_BITS);
    }
    else {
        value = nvic->ip[irq] >> (8-NVIC_PRIO_BITS);
    }

    return value;
}

