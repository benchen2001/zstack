/*
 * Make it unreadable, which should cause MMFAULT.
 * We need more tests.
 */

#include <mpu.h>
#include <sections.h>

#include <stdint.h>
#include <linux.h>

static struct mpu_config_item items[] = {
    {section_test_area_start, section_test_area_size, MPU_ITEM_DATA},
};

void test_mpu(void)
{
    VU32 value;
    value = *((VU32*)section_test_area_start);
    mpu_init(items, ARRAY_SIZE(items));
    value = *((VU32*)section_test_area_start);
    (void)value;
}

