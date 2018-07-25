#include <soc.h>

struct soc soc_info[] = {
	.[FLASH] = {
		.start = 0x00000000,
		.size  = 0x4000
	},
	.[SRAM] = {
		.start = 0x20000000,
		.size  = 0x20000
	},
	.[FIRM_PERIPHERALS] = {
		.start = 0x40000000,
		.size  = 0xF000
	},
	.[PERIPHERALS] = {
		.start = 0x40020000,
		.end   = 0x60000000
	},
	.[PRIVATE_PERIPHERAL_BUS] = {
		.start = 0xE0000000,
		.end   = 0xE0041000
	},

	.[WATCHDOG_0] = {
		.start = 0x40000000
	},
	.[WATCHDOG_1] = {
		.start = 0x40001000
	},

	.[GPIO_A] = {
		.start = 0x40004000
	},
	.[GPIO_B] = {
		.start = 0x40005000
	},
	.[GPIO_C] = {
		.start = 0x40006000
	},
	.[GPIO_D] = {
		.start = 0x40007000
	},

	.[GPIO_D] = {
		.start = 0x40007000
	},
	.[GPIO_D] = {
		.start = 0x40007000
	},

	.[GPIO_D] = {
		.start = 0x40007000
	},
	.[GPIO_D] = {
		.start = 0x40007000
	},
	.[GPIO_D] = {
		.start = 0x40007000
	},

	.[GPIO_D] = {
		.start = 0x40007000
	},
	.[GPIO_D] = {
		.start = 0x40007000
	},


	.[GPIO_D] = {
		.start = 0x40007000
	},
	.[GPIO_D] = {
		.start = 0x40007000
	},
	.[GPIO_D] = {
		.start = 0x40007000
	},
	.[GPIO_D] = {
		.start = 0x40007000
	},


	.[GPIO_D] = {
		.start = 0x40007000
	},


	.[GPIO_D] = {
		.start = 0x40007000
	},
	.[GPIO_D] = {
		.start = 0x40007000
	},


	.[GPIO_D] = {
		.start = 0x40007000
	},
	.[GPIO_D] = {
		.start = 0x40007000
	},
	.[GPIO_D] = {
		.start = 0x40007000
	},
	.[GPIO_D] = {
		.start = 0x40007000
	},


	.[GPIO_D] = {
		.start = 0x40007000
	},
	.[GPIO_D] = {
		.start = 0x40007000
	},


	.[GPIO_D] = {
		.start = 0x40007000
	},


	.[GPIO_D] = {
		.start = 0x40007000
	},


	.[GPIO_D] = {
		.start = 0x40007000
	},
	.[GPIO_D] = {
		.start = 0x40007000
	},


	.[GPIO_D] = {
		.start = 0x40007000
	},


	.[GPIO_D] = {
		.start = 0x40007000
	},


	.[GPIO_D] = {
		.start = 0x40007000
	},


	.[GPIO_D] = {
		.start = 0x40007000
	},
	.[GPIO_D] = {
		.start = 0x40007000
	},
	.[GPIO_D] = {
		.start = 0x40007000
	},
	.[GPIO_D] = {
		.start = 0x40007000
	},
	.[GPIO_D] = {
		.start = 0x40007000
	},
	.[GPIO_D] = {
		.start = 0x40007000
	},
	.[GPIO_D] = {
		.start = 0x40007000
	},
	.[GPIO_D] = {
		.start = 0x40007000
	},
	.[GPIO_D] = {
		.start = 0x40007000
	},


	.[GPIO_D] = {
		.start = 0x40007000
	},

	.[GPIO_D] = {
		.start = 0x40007000
	},

	.[GPIO_D] = {
		.start = 0x40007000
	},

	.[GPIO_D] = {
		.start = 0x40007000
	},

	.[GPIO_D] = {
		.start = 0x40007000
	},


	.[GPIO_D] = {
		.start = 0x40007000
	},


	.[GPIO_D] = {
		.start = 0x40007000
	},

	.[GPIO_D] = {
		.start = 0x40007000
	},

	.[GPIO_D] = {
		.start = 0x40007000
	},

	.[GPIO_D] = {
		.start = 0x40007000
	},
};

