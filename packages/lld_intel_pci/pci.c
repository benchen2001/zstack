// Refer to wiki.osdev.org/PCI
//
// qemu monitor
// : info pci 

#include <stdint.h>
#include <io.h>
#include <printk.h>

#define CONFIG_ADDR	(0xCF8)
#define CONFIG_DATA	(0xCFC)

struct pci_addr {
	uint32_t fixed	: 2;
	uint32_t reg	: 6;
	uint32_t func	: 3;
	uint32_t slot	: 4;
	uint32_t bus	: 8;
	uint32_t rsvd	: 8;
	uint32_t enable	: 1;
};

struct pci_config {
	uint32_t vendor_id	: 16;
	uint32_t device_id	: 16;
	uint32_t command	: 16;
	uint32_t status		: 16;
	uint32_t revision	: 8;
	uint32_t prog_if	: 8;
	uint32_t subclass	: 8;
	uint32_t class_code	: 8;
	uint32_t cacheline_size	: 8;
	uint32_t latency_timer	: 8;
	uint32_t header_type	: 8;
	uint32_t BIST		: 8;
	uint32_t BAR0		: 32;
	uint32_t BAR1		: 32;
	uint32_t BAR2		: 32;
	uint32_t BAR3		: 32;
	uint32_t BAR4		: 32;
	uint32_t BAR5		: 32;
	uint32_t cardbus	: 32;
	uint32_t subsys_vendor	: 16;
	uint32_t subsys_id	: 16;
	uint32_t rom_base	: 32;
	uint32_t capability	: 8;
	uint32_t rsvd0		: 24;
	uint32_t rsvd1		: 32;
	uint32_t interrupt_line	: 8;
	uint32_t interrupt_pin	: 8;
	uint32_t min_grant	: 8;
	uint32_t max_latency	: 8;
};

uint32_t pci_config_read (int bus, int slot, int func, int reg)
{
	struct pci_addr addr = {
		.enable = 1,
		.bus = bus,
		.slot = slot,
		.func = func,
		.reg = reg,
		.fixed = 0
	};

	uint32_t data;
	uint32_t *addrp = (uint32_t *)&addr;

	out(*addrp, CONFIG_ADDR);
	data = in(CONFIG_DATA);

	return data;
}

int pci_config_read_vendor_id (int bus, int slot, int func)
{
	uint32_t data = pci_config_read(bus, slot, func, 0);
	return data & 0xFFFF;
}


int pci_config_read_device_id (int bus, int slot, int func)
{
	uint32_t data = pci_config_read(bus, slot, func, 0);
	return data >> 16;
}

void pci_config_dump (int bus, int slot, int func)
{
	struct pci_config config;
	uint32_t *data;
	
	data = (uint32_t *)&config;

	for (int i=0; i<sizeof(struct pci_config)/4; i++) {
		data[i] = pci_config_read(bus, slot, func, i);
	}

	printk(	"---------------------------------------------------------\n"
		"PCI BUS %d SLOT %d FUNC %d DUMP:\n"
		"---------------------------------------------------------\n"
		"Vendor ID: %x\t"
		"Device ID: %x\n"
		"Command: %x\t"
		"Status: %x\n"
		"Revision: %x\t"
		"Prog IF: %x\t"
		"Subclass: %x\t"
		"Class Code: %x\n"
		"Cacheline: %x\t"
		"Latency: %x\t"
		"Header Type: %x\t"
		"BIST: %x\n"
		"BAR0: %x\n"
		"BAR1: %x\n"
		"BAR2: %x\n"
		"BAR3: %x\n"
		"BAR4: %x\n"
		"BAR5: %x\n"
		"Card BUS: %x\n"
		"Subsystem Vendor: %x\t"
		"Subsystem ID: %x\n"
		"ROM Base: %x\n"
		"Capability: %x\n"
		"Interrupt Line: %x\t"
		"Interrupt Pin: %x\t"
		"Min Grant: %x\t"
		"Max Latency: %x\n"
		"---------------------------------------------------------\n",
		bus, slot, func,
		config.vendor_id, config.device_id,
		config.command, config.status,
		config.revision, config.prog_if, config.subclass, config.class_code,
		config.cacheline_size, config.latency_timer, config.header_type, config.BIST,
		config.BAR0,
		config.BAR1,
		config.BAR2,
		config.BAR3,
		config.BAR4,
		config.BAR5,
		config.cardbus,
		config.subsys_vendor, config.subsys_id,
		config.rom_base,
		config.capability,
		config.interrupt_line, config.interrupt_pin, config.min_grant, config.max_latency
		);
}

struct pci_vendor_map {
	char *name;
	uint16_t id;
};

void pci_scan (void)
{
	uint32_t id = 0;
	uint32_t class = 0;
	uint32_t bar0 = 0;

	for (int bus=0; bus<256; bus++) {
		for (int slot=0; slot<16; slot++) {
			for (int func=0; func<8; func++) {
				id = pci_config_read(bus, slot, func, 0);
				class = pci_config_read(bus, slot, func, 2);
				bar0 = pci_config_read(bus, slot, func, 3);
				if (0xFFFFFFFF != id) {
					printk(	"bus %d slot %d func %d\n"
						"\tvendor: %x device: %x\n"
						"\tclass: %x subclass: %x\n",
						bus, slot, func,
						id & 0xFFFF,
						id >> 16,
						class >> 24,
						(class >> 16) & 0xFF
						);
					printk("\tBAR0: %x\n", bar0);
				}
			}
		}
	}
}

int pci_init (void)
{
	pci_scan();

	//pci_config_dump(0,0,0);

	return 0;
}

