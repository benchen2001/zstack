#ifndef ARMV_MPU_H
#define ARMV_MPU_H

#include <types.h>

struct MPU_t {
    VU32 TYPE;
    VU32 CTRL;
    VU32 RNR;
    VU32 RBAR;
    VU32 RASR;

    VU32 RBAR_A1;
    VU32 RASR_A1;
    VU32 RBAR_A2;
    VU32 RASR_A2;
    VU32 RBAR_A3;
    VU32 RASR_A3;
};

struct MPU_REGION_TYPE_t {
    VU32 reserved0:8;
    VU32 iregion:8;
    VU32 dregion:8;
    VU32 reserved1:7;
    VU32 separate:1;
};

struct MPU_CONTROL_t {
    VU32 reserved:29;
    VU32 priv_def_ena:1;
    VU32 hf_nmi_ena:1;
    VU32 enable:1;
};

struct MPU_REGION_NUMBER_t {
    VU32 reserved:24;
    VU32 region:8;
};

struct MPU_REGION_BASE_t {
    VU32 addr:27;
    VU32 valid:1;
    VU32 region:4;
};

struct MPU_REGION_ATTR_t {
    VU32 reserved0:3;
    VU32 instruction_access:1;
    VU32 reserved1:1;
    VU32 access_permission:3;
    VU32 reserved2:2;
    VU32 type_extension:3;
    VU32 shareable:1;
    VU32 cacheable:1;
    VU32 bufferable:1;
    VU32 sub_region_disable:8;
    VU32 reserved3:2;
    VU32 size:5;
    VU32 enable:1;
};

/* Masks for MPU Memory Region Sizes */
#define REGION_32B      0x08
#define REGION_64B      0x0A
#define REGION_128B     0x0C
#define REGION_256B     0x0E
#define REGION_512B     0x10
#define REGION_1K       0x12
#define REGION_2K       0x14
#define REGION_4K       0x16
#define REGION_8K       0x18
#define REGION_16K      0x1A
#define REGION_32K      0x1C
#define REGION_64K      0x1E
#define REGION_128K     0x20
#define REGION_256K     0x22
#define REGION_512K     0x24
#define REGION_1M       0x26
#define REGION_2M       0x28
#define REGION_4M       0x2A
#define REGION_8M       0x2C
#define REGION_16M      0x2E
#define REGION_32M      0x30
#define REGION_64M      0x32
#define REGION_128M     0x34
#define REGION_256M     0x36
#define REGION_512M     0x38
#define REGION_1G       0x3A
#define REGION_2G       0x3C
#define REGION_4G       0x3E

/* General MPU Masks */
#define REGION_ENABLED  0x1
#define REGION_VALID    0x10

#define SHAREABLE       0x40000
#define CACHEABLE       0x20000
#define BUFFERABLE      0x10000

/* Region Permissions */
#define NOT_EXEC        0x10000000 /* All Instruction fetches abort */

#define NO_ACCESS       0x00000000
#define P_NA_U_NA       0x00000000
#define P_RW_U_NA       0x01000000
#define P_RW_U_RO       0x02000000
#define P_RW_U_RW       0x03000000
#define FULL_ACCESS     0x03000000
#define P_RO_U_NA       0x05000000
#define P_RO_U_RO       0x06000000
#define RO              0x07000000

/* Predefined attributes */
#define MPU_REGION_ATTR_CODE (RO | CACHEABLE | BUFFERABLE | REGION_ENABLED)
#define MPU_REGION_ATTR_DATA (NOT_EXEC | FULL_ACCESS | CACHEABLE | BUFFERABLE | REGION_ENABLED)
#define MPU_REGION_ATTR_DEVICE (NOT_EXEC | FULL_ACCESS | REGION_ENABLED)

#endif

