#include <stdint.h>
#include <stdio.h>
#include <printk.h>

void hex_dump(uint8_t *buffer, uint32_t length)
{
        int i;
        for (i=0; i<length/16; i++) {
                printk("%08x : %02x %02x %02x %02x %02x %02x %02x %02x | "
                              "%02x %02x %02x %02x %02x %02x %02x %02x\n",
                        i*16,
                        buffer[i*16+0],
                        buffer[i*16+1],
                        buffer[i*16+2],
                        buffer[i*16+3],
                        buffer[i*16+4],
                        buffer[i*16+5],
                        buffer[i*16+6],
                        buffer[i*16+7],
                        buffer[i*16+8],
                        buffer[i*16+9],
                        buffer[i*16+10],
                        buffer[i*16+11],
                        buffer[i*16+12],
                        buffer[i*16+13],
                        buffer[i*16+14],
                        buffer[i*16+15]);
        }
}

