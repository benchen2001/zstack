#ifndef PERIPHERAL_ST_DMA_H
#define PERIPHERAL_ST_DMA_H

#include <io/types.h>

struct DMA_CONTROLLER {
    VU32 LISR;
    VU32 HISR;
    VU32 LIFCR;
    VU32 HIFCR;

    VU32 S0CR;
    VU32 S0NDTR;
    VU32 S0PAR;
    VU32 S0M0AR;
    VU32 S0M1AR;
    VU32 S0FCR;

    VU32 S1CR;
    VU32 S1NDTR;
    VU32 S1PAR;
    VU32 S1M0AR;
    VU32 S1M1AR;
    VU32 S1FCR;

    VU32 S2CR;
    VU32 S2NDTR;
    VU32 S2PAR;
    VU32 S2M0AR;
    VU32 S2M1AR;
    VU32 S2FCR;

    VU32 S3CR;
    VU32 S3NDTR;
    VU32 S3PAR;
    VU32 S3M0AR;
    VU32 S3M1AR;
    VU32 S3FCR;

    VU32 S4CR;
    VU32 S4NDTR;
    VU32 S4PAR;
    VU32 S4M0AR;
    VU32 S4M1AR;
    VU32 S4FCR;

    VU32 S5CR;
    VU32 S5NDTR;
    VU32 S5PAR;
    VU32 S5M0AR;
    VU32 S5M1AR;
    VU32 S5FCR;

    VU32 S6CR;
    VU32 S6NDTR;
    VU32 S6PAR;
    VU32 S6M0AR;
    VU32 S6M1AR;
    VU32 S6FCR;

    VU32 S7CR;
    VU32 S7NDTR;
    VU32 S7PAR;
    VU32 S7M0AR;
    VU32 S7M1AR;
    VU32 S7FCR;
};

#endif
