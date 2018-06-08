#include <stdint.h>

#include "x86.h"

extern uint32_t tss;

#define GDT_ITEM_NUM		(6)

struct gdt_item global_descriptor_table[GDT_ITEM_NUM];

struct gdt_info global_descriptor_table_info = {
	.size = sizeof(global_descriptor_table) - 1,
	.addr = (uint32_t)global_descriptor_table
};

void gdt_register(int index, uint32_t base, uint32_t limit)
{
	global_descriptor_table[index].limit_low = limit & 0xFFFF;
	global_descriptor_table[index].limit_high = 0xF;
	global_descriptor_table[index].base_low = 0;
	global_descriptor_table[index].base_high = 0;
	global_descriptor_table[index].access = GDT_ACCESS_X;
	global_descriptor_table[index].type = GDT_STORAGE;
	global_descriptor_table[index].DPL = 3;
	global_descriptor_table[index].present = 1;
	global_descriptor_table[index].rsvd = 0;
	global_descriptor_table[index].bit32 = 1;
	global_descriptor_table[index].granularity = GDT_GRAN_4KB;
}

void gdt_init (void)
{
	uint64_t *array = (uint64_t *)global_descriptor_table;

	array[0] = 0x0000000000000000;
	array[1] = 0x00CF9A000000FFFF;
	array[2] = 0x00CF92000000FFFF;
	array[3] = 0x00CFFA000000FFFF;
	array[4] = 0x00CFF2000000FFFF;
	array[5] = 0x0000E9007C1DFFFF;

	/* MUST use tss address! */
	global_descriptor_table[5].base_low = (uint32_t)(&tss);
	global_descriptor_table[5].base_high = (uint32_t)(&tss)>>24;
	global_descriptor_table[5].base_high = 0;
	global_descriptor_table[5].limit_low = 0xFFFF;
	global_descriptor_table[5].limit_high = 0xF;

	__asm__ ("lgdt global_descriptor_table_info");
}

