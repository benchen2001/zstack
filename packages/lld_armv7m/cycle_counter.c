/*
 * The SysTick function must be configured to use the processor clock as the
 * reference timing source. The count will be accurate up to a 24-bit maximum
 * number of clock cycles from the point where the STCVR is re-loaded.
 *
 * Reference
 *  - http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.faqs/ka8713.html
 *  - http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0439c/BABJFFGJ.html
 */

#include "registers.h"
#include "registers-base.h"
#include "systick.h"

#include <stdint.h>

void cycle_counter_start(void)
{
    SYSTICK->reload = 0xFFFFFF;
    SYSTICK->count = 0;
    SYSTICK->SR = 5; /* disable interrupt */
}

uint32_t cycle_counter_end(void)
{
    return (SYSTICK->count - 2);
}

