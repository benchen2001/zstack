#include <io.h>
#include <stdint.h>

void interrupt_controller_init (void)
{
	outb_p(0x11, 0x20); // ICW1: Cacade mode, edge trigger
	outb_p(0x11, 0xa0);

	outb_p(0x20, 0x21); // ICW2: IRQ offset
	outb_p(0x28, 0xa1);

	outb_p(0x04, 0x21); // ICW3: PIN connect with 8259A M/S
	outb_p(0x02, 0xa1);

	outb_p(0x01, 0x21); // ICW4: 80x86 mode
	outb_p(0x01, 0xa1);

	outb_p(0xff, 0x21); // OCW: Disable all
	outb_p(0xff, 0xa1);
}

// TODO 0xa0 ack
void interrupt_controller_ack (void)
{
	outb_p(0x20, 0x20);
}

void interrupt_controller_enable (int irq)
{
	uint8_t value;
	uint8_t mask = ~(1<<irq);

	if (irq < 8) {
		value = inb_p(0x21);
		outb_p(value & mask, 0x21);
	}
	else {
		value = inb_p(0xa1);
		outb_p(value & mask, 0xa1);
	}
}

void intel_8259a_disable (uint8_t irq)
{
	uint8_t value;
	uint8_t mask = (1<<irq);

	if (irq < 8) {
		value = inb_p(0x21);
		outb_p(value | mask, 0x21);
	}
	else {
		value = inb_p(0xa1);
		outb_p(value | mask, 0xa1);
	}
}

