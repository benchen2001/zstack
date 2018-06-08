#ifndef ARMV7M_REGISTERS_SCS_SCB_H
#define ARMV7M_REGISTERS_SCS_SCB_H

#include <types.h>

struct SCB_CPUID_t {
    VU32 implementer:8;
    VU32 variant:4;
    VU32 arch:4;
    VU32 partno:12;
    VU32 revision:4;
};

struct SCB_ID_MMFR0_t {
    VU32 reserved0:8;
    VU32 aux:4;
    VU32 tcm:4;
    VU32 share_level:4;
    VU32 outermost_share:4;
    VU32 pmsa:4;
    VU32 reserved1:4;
};

struct SCB_CLIDR_t {
    VU32 unk:2;
    VU32 louu:3;
    VU32 loc:3;
    VU32 louis:3;
    VU32 ctype7:3;
    VU32 ctype6:3;
    VU32 ctype5:3;
    VU32 ctype4:3;
    VU32 ctype3:3;
    VU32 ctype2:3;
    VU32 ctype1:3;
};

struct SCB_CCSIDR_t {
    VU32 wt:1;
    VU32 wb:1;
    VU32 ra:1;
    VU32 wa:1;
    VU32 numset:15;
    VU32 assoc:10;
    VU32 linesize:3;
};

struct SCB_CCR_t {
    VU32 reserved0:12;
    VU32 branch_prediction_enable:1;
    VU32 icache_enable:1;
    VU32 dcache_enable:1;
    VU32 reserved1:6;
    VU32 stack_frame_align:1;
    VU32 bf_hf_nmi_gn:1;
    VU32 reserved2:3;
    VU32 div_0_error_enable:1;
    VU32 unalign_error_enable:1;
    VU32 reserved3:1;
    VU32 unprivilege_access_STIR:1;
    VU32 no_base_thread:1;
};

#endif

