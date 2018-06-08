#include <armv7-m/nvic.h>

void nvic_init(void)
{
    NVIC_VTOR = 0x0;
}

