#include <stdint.h>
#include <bitopts.h>
#include <gdt.h>

#define MAX_DESCRIPTORS 3	//null, code, data

struct __attribute__((__packed__)) gdt_seg_desc {
	u16_t	limit_l;
	u16_t	base_l;
	u8_t	base_m;

	/* ACCESS_TYPE byte (check related macros for more info)
	 * 7 	6 	5 	4 	3 	2 	1 	0
	 * Pr		Privl 	S 	Ex 	DC 	RW 	Ac
	 * */
	u8_t	access_type;

	/*
	 * 1st nibble bits contains limit_size high value and
	 * next 4 bits contains flags for this descriptor.
	 */
	u8_t	limith_flags;
	u8_t	base_h;
};

struct __attribute__((__packed__)) gdt_desc {
	u16_t	limit;	// Size of GDT table.
	u32_t	base;	// base addr of GDT (start of the segment desc).
};

struct gdt_desc _gdtr;
struct gdt_seg_desc _gdt_seg[MAX_DESCRIPTORS];

void create_seg_desc(u32_t index, u32_t base, u32_t limit, u8_t access_type, u8_t flags)
{
	_gdt_seg[i].limit_l = (limit & 0x0000ffff);
	_gdt_seg[i].base_l = (base & 0x0000ffff);
	_gdt_seg[i].base_m = (16 >> (base & 0x00ff0000));
	_gdt_seg[i].access_type = access_type;
	/* Set high limit */
	_gdt_seg[i].limit_flags = (16 >> (limit & 0x00ff0000));
	_gdt_seg[i].limit_flags = (4 >> flags);
}


void init_gdtr(void)
{
	asm("lgdt %1": "r" (_gdt_desc));
}
