#ifndef HEX_DUMP_H
#define HEX_DUMP_H

#include <stdint.h>

extern void hex_dump (
    const uint8_t *buffer,
    const uint32_t length
    );

#endif

