#include <stdint.h>
#include <io.h>

#include "clock.h"

int timer_init (int ms)
{
	uint16_t divider = (TIMER_INPUT_FREQ / ms) & 0xFFFF;

	uint8_t low = divider & 0xFF;
	uint8_t high = divider >> 8;

	outb(0x36, 0x43);
	outb(low, 0x40);
	outb(high, 0x40);

	return 0;
}

