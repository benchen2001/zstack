#include <armv7-m/register-map.h>

#include <arm/barrier.h>

#include <mpu.h>

static const uint32_t attribute[MPU_ITEM_TYPE_MAX] = {
    [MPU_ITEM_CODE] = MPU_REGION_ATTR_CODE,
    [MPU_ITEM_DATA] = MPU_REGION_ATTR_DATA,
    [MPU_ITEM_DEVICE] = MPU_REGION_ATTR_DEVICE
};

void mpu_init(struct mpu_config_item *items, int count)
{
    int i;

    uint32_t base = 0, attr = 0;

    struct MPU_REGION_BASE_t  *basep = (struct MPU_REGION_BASE_t *)&base;
    struct MPU_REGION_ATTR_t  *attrp = (struct MPU_REGION_ATTR_t *)&attr;
    struct MPU_CONTROL_t      *ctrlp = (struct MPU_CONTROL_t *)&SCS.MPU.CTRL;

    for (i=0; i<count; i++) {
        base = 0;
        basep->addr = items[i].addr; /* align check */
        basep->region = i;
        basep->valid = 1;

        attr = attribute[items[i].type];
        attrp->size = items[i].length;
        attrp->enable = 1;

        SCS.MPU.RBAR = base;
        SCS.MPU.RASR = attr;
    }

    ctrlp->enable = 1;

    dsb();
    isb();
}

