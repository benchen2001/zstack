void interrupt_enable (void)
{
}

void interrupt_disable (void)
{
}

void software_interrupt (int num)
{
	__asm__ ("ECALL");
}

