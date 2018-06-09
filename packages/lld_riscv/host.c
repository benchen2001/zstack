#include <stdint.h>

volatile uint64_t tohost;
volatile uint64_t fromhost;

void putc (int ch)
{
	while (0 != tohost);
	tohost = ch | 0x0101000000000000;
}

