#include "config.h"

#include <armv7-m/register-map.h>

#include <stdint.h>

void systick_init(uint32_t ticks)
{
    SCS.SYSTICK.RVR = ticks;
    SCS.SYSTICK.CVR = 0;
    SCS.SYSTICK.CSR = SYSTICK_ENABLE | SYSTICK_INT_ENABLE | SYSTICK_INTERNAL_CLK;
}

