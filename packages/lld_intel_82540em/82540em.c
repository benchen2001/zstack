#include <stdint.h>
#include <delay.h>

struct i8254x_registers {
	uint64_t ctrl;
	uint64_t status;
	uint32_t eecd;
	uint32_t eerd;
	uint32_t ctrl_ext;
	uint32_t fla;
	uint32_t mdic;
};

static uint16_t i8254x_eeprom_read(uint32_t base, uint8_t addr)
{
	struct i8254x_registers *regs = (void *)base;
	uint32_t tmp = 0;
	uint16_t data = 0;

	regs->eerd = addr<<8 | 1;

	do {
		tmp = regs->eerd;
		mdelay(1);
	} while (0 == (tmp & (1<<4)));

	data = (uint16_t)((tmp>>16) & 0xFFFF);
	return data;
}

uint16_t i8254x_phy_read(uint32_t base, uint8_t addr)
{
	struct i8254x_registers *regs = (void *)base;
	uint16_t data = 0;

	regs->mdic = (addr & 0x1F)<<16 | (1<<21) | (2<<26) | (1<<29);

	while (0 == (regs->mdic & (1<<28 | 1<<30))) {
		mdelay(1);
	}

	if (regs->mdic & (1<<30)) {
		printk("i8254x: MDI READ ERROR\n");
	}

	data = regs->mdic & 0xFFFF;
	return data;
}

void intel_82540em_init(uint32_t base)
{
	struct i8254x_registers *regs = (void *)base;
	uint16_t data;
	uint8_t mac_addr[8];

	data = i8254x_eeprom_read(base, 0);
	mac_addr[0] = data & 0xFF;
	mac_addr[1] = (data >> 8) & 0xFF;
	data = i8254x_eeprom_read(base, 1);
	mac_addr[2] = data & 0xFF;
	mac_addr[3] = (data >> 8) & 0xFF;
	data = i8254x_eeprom_read(base, 2);
	mac_addr[4] = data & 0xFF;
	mac_addr[5] = (data >> 8) & 0xFF;

	printk("i8254x: MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
			mac_addr[0], mac_addr[1], mac_addr[2],
			mac_addr[3], mac_addr[4], mac_addr[5]);

	regs->ctrl |= (1<<6);

	printk("i8254x: PHY ID: %x\n", i8254x_phy_read(base, 0x2d));
}

