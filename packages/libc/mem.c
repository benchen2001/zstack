
void memset (unsigned char *buffer, unsigned char flag, unsigned int len)
{
	unsigned int i;
	for (i=0; i<len; i++) {
		buffer[i] = flag;
	}
}

