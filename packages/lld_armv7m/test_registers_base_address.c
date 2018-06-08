#include <stdint.h>

#include <armv7-m/register-map.h>

#define IS_ADDRESS_VALID(member, addr) { \
    if ((VU32)&member != addr) { \
        invalid_line = __LINE__; \
        reg_addr = (VU32)&member; \
        goto invalid; \
    }}

int test_registers_base_address(void)
{
    int invalid_line = 0;
    VU32 reg_addr = 0;

    (void)reg_addr;

    IS_ADDRESS_VALID(SCS.SYSTICK,  0xE000E010);
    IS_ADDRESS_VALID(SCS.NVIC,     0xE000E100);
    IS_ADDRESS_VALID(SCS.SCB,      0xE000ED00);
    IS_ADDRESS_VALID(SCS.MPU,      0xE000ED90);
    IS_ADDRESS_VALID(SCS.SWTI,     0xE000EF00);
    IS_ADDRESS_VALID(SCS.PERIPH_ID,0xE000EFD0);

invalid:
    return invalid_line;
}

