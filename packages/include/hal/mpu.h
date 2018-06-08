#ifndef CORE_MPU_H
#define CORE_MPU_H

#include <stdint.h>

enum mpu_item_type {
    MPU_ITEM_CODE,
    MPU_ITEM_DATA,
    MPU_ITEM_DEVICE,
    MPU_ITEM_TYPE_MAX,
};

struct mpu_config_item {
    uint32_t addr;
    uint32_t length;
    enum mpu_item_type type;
};

#endif

