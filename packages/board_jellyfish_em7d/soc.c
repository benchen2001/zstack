#include <soc.h>

struct soc_ip_config soc_ip_config_array[] = {
	{"SRAM",	0x40000000, -1, 0},
	{"DMA",		0xbfb60000, 5,  0},
	{"GPIO",	0xbfb68000, 7,  0},
	{"I2C",		0xbfb70000, 6,  0},
	{"IRQCTRL",	0xbfb78000, -1, 0},
	{"TIMER",	0xbfb80000, 0,  0},
	{"AON",		0xbfb88000, -1, 0},
	{"ARC",		0xbfb8c000, -1, 0},
	{"ISP",		0xbfe00000, 2,  0},
	{0}
};

