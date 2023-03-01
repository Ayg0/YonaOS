#include "../INCLUDE/descriptor_tables.h"

// initializing the descriptor tables
void	init_descriptor_tables(){
	// initializing the global descriptor table
	init_gdt();
	// initializing the interrupts descriptor table
	init_idt();
}