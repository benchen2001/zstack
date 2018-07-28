#include <stdint.h>

void memset (unsigned char *buffer, unsigned char flag, unsigned int len)
{
	unsigned int i;
	for (i=0; i<len; i++) {
		buffer[i] = flag;
	}
}

void memcpy(uint8_t *dst, uint8_t *src, uint32_t len)
{
	uint32_t i;

	for (i=0; i<len; i++) {
		dst[i] = src[i];
	}
}
