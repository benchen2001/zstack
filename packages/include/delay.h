#ifndef DELAY_H
#define DELAY_H

#include <stdint.h>

#define UDELAY_LIMIT	(0xFFFFFFFF / 1000)

static inline void udelay(uint32_t us)
{
	// TODO
	if (CONFIG_CORE_CYCLE_PER_US > UDELAY_LIMIT) {
		while(1);
	}

	for (volatile unsigned int i=0; i<us*CONFIG_CORE_CYCLE_PER_US; i++);
}

static inline void mdelay(uint32_t ms)
{
	for (volatile unsigned int i=0; i<ms; i++) {
		udelay(1000);
	}
}

#endif
