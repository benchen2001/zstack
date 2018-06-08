#include "registers.h"
#include "registers-base.h"
#include "nvic.h"

void nvic_set_pending_irq(int irq)
{
    NVIC->ispr[irq>>5] = 1 << (irq & 0x1F);
}

uint32_t nvic_get_pending_irq(int irq)
{
    uint32_t value;

    value = NVIC->ispr[irq>>5] & (1 << (irq & 0x1F));

    return (value ? 1 : 0);
}

void nvic_clear_pending_irq(int irq)
{
    NVIC->icpr[irq>>5] = 1 << (irq & 0x1F);
}
