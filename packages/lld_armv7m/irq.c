void interrupt_enable(void)
{
	__asm__("CPSIE i");
}

void interrupt_disable(void)
{
	__asm__("CPSID i");
}

void software_interrupt(int num)
{
	__asm__("SVC #0");
}

