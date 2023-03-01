#include "../../INCLUDE/descriptor_tables.h"
#include "../../INCLUDE/libt.h"
// idt vars
_idt_gate	idt_gates[256];
_idt_ptr	idt_p;

// set the handler in it's own gate in the IDT
static void	idt_set_gate(u8 index, u32 handler, u16 selector, u8 type_attr){
	idt_gates[index].low_base = handler & 0xffff; 
	idt_gates[index].high_base = (handler >> 16) & 0xffff; 
	idt_gates[index].segment_sel = selector; 
	idt_gates[index].always0 = 0;
	idt_gates[index].type_attr = type_attr;
}
// R https://chamilo.grenoble-inp.fr/courses/ENSIMAG4MMPCSEF/document/traps.pdf
// defining the msgs of each interrupt
static	char *interrupt_msgs(u8 index){
	switch (index)
	{
	case 0:		return (" Division By Zero");
	case 1:		return (" One step exception");
	case 2:		return (" Non Maskable Interrupt");
    case 3:		return (" Breakpoint");
    case 4:		return (" Overflow");
    case 5:		return (" bound Range Exceeded");
    case 6:		return (" Invalid Opcode");
    case 7:		return (" Device Not Available");
    case 8:		return (" Double Fault");
    case 9:		return (" Coprocessor Segment Overrun");
    case 10:	return (" Invalid TSS");
    case 11:	return (" Segment Not Present");
    case 12:	return (" Stack-Segment Fault");
    case 13:	return (" General Protection Fault");
    case 14:	return (" Page Fault");
    case 15:	return (" Reserved");
    case 16:	return (" x87 Floating-Point Exception");
    case 17:	return (" Alignment Check");
    case 18:	return (" Machine Check");
    case 19:	return (" SIMD Floating-Point Exception");
    case 20:	return (" Virtualization Exception");
    case 21:	return (" Control Protection Exception");
    case 22:	return (" Reserved");
    case 23:	return (" Reserved");
    case 24:	return (" Reserved");
    case 25:	return (" Reserved");
    case 26:	return (" Reserved");
    case 27:	return (" Reserved");
    case 28:	return (" Hypervisor Injection Exception");
    case 29:	return (" VMM Communication Exception");
    case 30:	return (" Security Exception");
    case 31:	return (" Reserved");
	default:	return (" Unknown");
	}
}
// assigning each handler with it's corresponding gate
static void	init_handlers(){
	u32	handlers[] = {	
		(u32)isr0, (u32)isr1, (u32)isr2, (u32)isr3,(u32)isr4, (u32)isr5, (u32)isr6, (u32)isr7, (u32)isr8, (u32)isr9, 
		(u32)isr10, (u32)isr11, (u32)isr12, (u32)isr13, (u32)isr14, (u32)isr15, (u32)isr16, (u32)isr17, (u32)isr18, (u32)isr19, 
		(u32)isr20, (u32)isr21, (u32)isr22, (u32)isr23, (u32)isr24, (u32)isr25, (u32)isr26, (u32)isr27, (u32)isr28, (u32)isr29, 
		(u32)isr30, (u32)isr31
	};
	//remember updating the number of handlers if you add one
	for (u8 i = 0; i < USED_HANDLERS; i++)
		idt_set_gate(i, handlers[i], CODE_SEGMENT, 0x8E);
}
// initializing the idt
void	init_idt(){
	idt_p.limit = sizeof(_idt_gate) * (256 - 1);	// defining the size of the idt.
	idt_p.base = (u32)&idt_gates;				// defining the start address of the idt.
	init_handlers();							// filling the idt with the corresponding ISRS.
	__asm__ __volatile__ ("lidt (%%eax)": : "a"(&idt_p));	// loading the idt into the IDTR.
}
// the global handler that all signals call
extern void	isr_handler(_registers r){
	put_str("\r\n");
	put_str("Inerrupt received: ");
	set_default_attr(get_attr(YELLOW, BLACK));
	put_nbr(r.int_no, HEX_FORMAT);
	set_default_attr(WHITE_ON_BLACK);
	put_str(interrupt_msgs(r.int_no));
}