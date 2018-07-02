#include <stdint.h>

int bitshift(const uint8_t *src, uint32_t *position, const uint32_t length)
{
	uint32_t pos = *position;
	uint32_t offset_byte = pos >> 3;
	uint32_t offset_bit_in_byte = pos & 0x7;
	uint8_t value;

	if (*position == length) {
		return -1;
	}

	value = src[offset_byte] & (1 << (7 - offset_bit_in_byte));

	*position = *position + 1;

	return value ? 1 : 0;
}
