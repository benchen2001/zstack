#ifndef ARMV7M_CORE_H
#define ARMV7M_CORE_H

typedef union {
    struct {
        VU32 reserved:27;
        VU32 Q:1;
        VU32 V:1;
        VU32 C:1;
        VU32 Z:1;
        VU32 N:1;
    } b;
    VU32 w;
} APSR_t;

typedef union {
    struct {
        VU32 ISR:9;
        VU32 reserved:23;
    } b;
    VU32 w;
} IPSR_t;

typedef union {
    struct {
        VU32 ISR:9;
        VU32 reserved:15;
        VU32 T:1;
        VU32 IT:2;
        VU32 Q:1;
        VU32 V:1;
        VU32 C:1;
        VU32 Z:1;
        VU32 N:1;
    } b;
    VU32 w;
} XPSR_t;

typedef union {
    struct {
        VU32 priv:1;
        VU32 spsel:1;
        VU32 fpca:1;
        VU32 reserved:29;
    } b;
    VU32 w;
} CONTROL_t;

#endif
