#include "registers.h"
#include "registers-base.h"
#include "scb.h"

#include <stdint.h>

void nvic_set_priority_group(uint32_t group)
{
    uint32_t value;
    uint32_t group_valid;

    group_valid = group & 0x7;

    value = SCB->aircr;
    value = value & (~(SCB_AIRCR_VEC_MASK | SCB_AIRCR_PRIOGROUP_MASK));
    value = value | (0x5FA << SCB_AIRCR_VEC_POS) | (group_valid << 8);

    SCB->aircr = value;
}

uint32_t nvic_get_priority_group(void)
{
    uint32_t value;

    value = SCB->aircr;

    value = (value & SCB_AIRCR_PRIOGROUP_MASK) >> SCB_AIRCR_PRIOGROUP_POS;

    return value;
}
