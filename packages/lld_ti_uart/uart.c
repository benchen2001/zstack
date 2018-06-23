
int putc(int ch)
{
	if ('\n' == ch) {
		*((volatile unsigned int *)0x4000C000) = '\r';
	}
	*((volatile unsigned int *)0x4000C000) = ch;
	return 0;
}

