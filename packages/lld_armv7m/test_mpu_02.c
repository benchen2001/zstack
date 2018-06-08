#include <armv7-m/register-map.h>

#include <types.h>

void test_mpu_02(void)
{
    VU32 *DR = (VU32 *)0x4000C000;

    SCS.MPU.RBAR = 0x00000000 | REGION_VALID | 0;
    SCS.MPU.RASR = FULL_ACCESS | REGION_1M | REGION_ENABLED;

    SCS.MPU.RBAR = 0x20000000 | REGION_VALID | 1;
    SCS.MPU.RASR = FULL_ACCESS | REGION_1M | REGION_ENABLED;

    SCS.MPU.CTRL = SCS.MPU.CTRL | 1;

    *DR = 'z';

    (void)DR;
}

