#ifndef ARMV7M_SYSTICK_H
#define ARMV7M_SYSTICK_H

#include <types.h>

struct SYSTICK_t {
    VU32 CSR;
    VU32 RVR;
    VU32 CVR;
    VU32 CALIB;
};

#define SYSTICK_INTERNAL_CLK    (1<<2)
#define SYSTICK_INT_ENABLE      (1<<1)
#define SYSTICK_ENABLE          (1<<0)

#endif

