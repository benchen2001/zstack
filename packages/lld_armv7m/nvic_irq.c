#include "registers.h"

void nvic_enable_irq(int irq)
{
    NVIC->iser[irq>>5] = 1 << (irq & 0x1F);
}

void nvic_disable_irq(int irq)
{
    NVIC->icer[irq>>5] = 1 << (irq & 0x1F);
}

