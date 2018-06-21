
int putc(int ch)
{
	*((volatile unsigned int *)0x4000C000) = ch;
	return 0;
}

