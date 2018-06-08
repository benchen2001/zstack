#ifndef X86_H
#define X86_H

#include <stdint.h>
#include <printk.h>

struct gdt_item {
	uint32_t limit_low	:16;
	uint32_t base_low	:24;

	uint32_t access 	:4;

	uint32_t type		:1;
	uint32_t DPL		:2; 
	uint32_t present	:1;

	uint32_t limit_high	:4;

	uint32_t rsvd		:2;
	uint32_t bit32		:1;
	uint32_t granularity	:1;

	uint32_t base_high	:8;
} __attribute__((packed));

struct gdt_info {
	uint16_t size;
	uint32_t addr;
} __attribute__((packed));

struct tss_item
{
	uint32_t prev_tss;	// The previous TSS
	uint32_t esp0;		// Ring 0
	uint32_t ss0;
	uint32_t esp1;		// Ring 1
	uint32_t ss1;
	uint32_t esp2;		// Ring 2
	uint32_t ss2;
	uint32_t cr3;		// Below for Ring 3
	uint32_t eip;
	uint32_t eflags;
	uint32_t eax;
	uint32_t ecx;
	uint32_t edx;
	uint32_t ebx;
	uint32_t esp;
	uint32_t ebp;
	uint32_t esi;
	uint32_t edi;
	uint32_t es;   
	uint32_t cs;        
	uint32_t ss;        
	uint32_t ds;        
	uint32_t fs;       
	uint32_t gs;         
	uint32_t ldt;      
	uint16_t trap;
	uint16_t iomap_base;
} __attribute__((packed));

struct idt_item {
	uint16_t offset_low;
	uint16_t selector;
	uint8_t rsvd;
	uint8_t attr_gate_type:4;
	uint8_t attr_storage_segment:1;
	uint8_t attr_dpl:2;
	uint8_t attr_present:1;
	uint16_t offset_high;
} __attribute__((packed));

struct idt_info {
	uint16_t size;
	uint32_t addr;
} __attribute__((packed));

#define IDT_TASK32	(0x5)
#define IDT_INT32	(0xE)
#define IDT_TRAP32	(0xF)

/* DS: data segment */
#define GDT_ACCESS_RO	(0)
#define GDT_ACCESS_RW	(2)
#define GDT_ACCESS_X	(8)
#define GDT_ACCESS_RX	(0xA)

#define GDT_STORAGE	(1)
#define GDT_GATE	(0)

#define GDT_GRAN_BYTE	(0)
#define GDT_GRAN_4KB	(1)

extern void gdt_init (void);
extern void idt_init (void);
extern void tss_init (void);

#endif
