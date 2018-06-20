#ifndef DELAY_H
#define DELAY_H

#include <stdint.h>

static inline void udelay(uint32_t us)
{
	for (volatile int i=0; i<us*CONFIG_CORE_CYCLE_PER_US; i++);
}

static inline void mdelay(uint32_t ms)
{
	for (volatile int i=0; i<ms; i++) {
		udelay(1000);
	}
}

#endif
