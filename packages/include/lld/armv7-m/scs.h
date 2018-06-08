#ifndef ARMV7M_SCS_H
#define ARMV7M_SCS_H

#include <types.h>

#include "scb.h"

#include <arm/nvic.h>
#include <arm/systick.h>
#include <arm/mpu.h>

struct SCB_t {
    VU32 CPUID;
    VU32 ICSR;
    VU32 VTOR;
    VU32 AIRCR;
    VU32 SCR;
    VU32 CCR;
    VU32 SHP[3];
    VU32 SHCSR;
    VU32 CFSR;
    VU32 HFSR;
    VU32 DFSR;
    VU32 MMFAR;
    VU32 BFAR;
    VU32 AFSR;
    VU32 ID_PFR[2];
    VU32 ID_DFR;
    VU32 ID_AFR;
    VU32 ID_MMFR[4];
    VU32 ID_ISAR[6];
    VU32 CLIDR;
    VU32 CTR;
    VU32 CCSIDR;
    VU32 CSSELR;
    VU32 CPACR;
};

struct DCB_t {
    VU32 DHCSR;
    VU32 DCRSR;
    VU32 DCRDR;
    VU32 DEMCR;
};

struct FPEX_t {
    VU32 FPCCR;
    VU32 FPCAR;
    VU32 FPDSCR;
    VU32 MVFP0;
    VU32 MVFP1;
    VU32 MVFP2;
};

struct CBPM_t {
    VU32 ICIIALLU;
    VU32 RESERVED;
    VU32 ICIMVAU;
    VU32 DCIMVAC;
    VU32 DCISW;
    VU32 DCCMVAU;
    VU32 DCCMVAC;
    VU32 DCCSW;
    VU32 DCCIMVAC;
    VU32 DCCISW;
    VU32 BPIALL;
};

struct PERIPH_ID_t {
    VU32 PID4;
    VU32 PID5;
    VU32 PID6;
    VU32 PID7;
    VU32 PID0;
    VU32 PID1;
    VU32 PID2;
    VU32 PID3;
};

struct COMP_ID_t {
    VU32 CID0;
    VU32 CID1;
    VU32 CID2;
    VU32 CID3;
};

struct SCS_t {
    VU32                MCR;
    VU32                ICTR;
    VU32                ACTLR;
    VU32                RESERVED_E00C_E010[(0xE010-0xE00C)>>2];
    struct SYSTICK_t    SYSTICK;
    VU32                RESERVED_E020_E100[(0xE100-0xE020)>>2];
    struct NVIC_t       NVIC;
    struct SCB_t        SCB;
    VU32                RESERVED_ED8C_ED90[(0xED90-0xED8C)>>2];
    struct MPU_t        MPU;
    VU32                RESERVED_EDBC_EDF0[(0xEDF0-0xEDBC)>>2];
    struct DCB_t        DCB;
    VU32                RESERVED_EE00_EF00[(0xEF00-0xEE00)>>2];
    VU32                SWTI;
    VU32                RESERVED_EF04_EF34[(0xEF34-0xEF04)>>2];
    struct FPEX_t       FPEX;
    VU32                RESERVED_EF4C_EF50[(0xEF50-0xEF4C)>>2];
    struct CBPM_t       CBPM;
    VU32                RESERVED_EF7C_EF90[(0xEF90-0xEF7C)>>2];
    VU32                RESERVED_EF90_EFD0[(0xEFD0-0xEF90)>>2];
    struct PERIPH_ID_t  PERIPH_ID;
    struct COMP_ID_t    COMP_ID;
};

#endif

