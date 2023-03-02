#include "../../INCLUDE/system.h"
#include "../../INCLUDE/descriptor_tables.h"

// gdt vars
_gdt_entry	gdt_entries[GDT_ENTRIES];
_gdt_ptr	gdt_p;

static void	set_gdt_entry(u32 index, u32 limit, u32 base, u8 access_b, u8 flags){
	// define the size of the segment:
	gdt_entries[index].low_limit = L16(limit);
	gdt_entries[index].flags_highLimit = (limit >> 16) & 0x0F;	// limit at the last for bits
	// define the base address of the segment:
	gdt_entries[index].low_base	= L16(base);
	gdt_entries[index].middle_base = (base >> 16) & 0xFF;
	gdt_entries[index].high_base = (base >> 24) & 0xFF;
	// define the access/flag bits:
	gdt_entries[index].flags_highLimit |= flags & 0xF0;	// flags stored at the first 4 bits
	gdt_entries[index].access_bytes = access_b;
}

void	init_gdt(){
	gdt_p.base = (u32)&gdt_entries;
	gdt_p.limit = (GDT_ENTRIES * sizeof(_gdt_entry)) - 1;

	set_gdt_entry(0, 0, 0, 0, 0); // NULL Segment
	set_gdt_entry(1, 0xFFFFFFFF, 0x0, 0x9A, 0xCF);	// Code Segment
	set_gdt_entry(2, 0xFFFFFFFF, 0x0, 0x92, 0xCF);	// Data Segment
	
	gdt_load((u32)&gdt_p);
}

