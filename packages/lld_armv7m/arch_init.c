#include <armv7-m/register-map.h>

extern int test_mpu_02(void);

void arch_init(void)
{
    struct SCB_CCR_t *ccr;

    /* See "ARMv7M TRD B1.5.7" */
    ccr = (struct SCB_CCR_t *)&SCS.SCB.CCR;
    ccr->stack_frame_align = 1;

    //mpu_init();
    test_mpu_02();
}

