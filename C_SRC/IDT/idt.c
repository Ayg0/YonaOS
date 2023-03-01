#include "../INCLUDE/descriptor_tables.h"
#include "../INCLUDE/typedefs.h"
#include "../INCLUDE/libt.h"

#define CODE_SEGMENT 0x08

idt_gate	idt_gates[256];
idt_ptr		idt_p;

static void	idt_set_gate(u8 index, u32 handler, u16 selector, u8 type_attr){
	idt_gates[index].low_base = handler & 0xffff; 
	idt_gates[index].high_base = (handler >> 16) && 0xffff; 
	idt_gates[index].segment_sel = selector; 
	idt_gates[index].always0 = 0;
	idt_gates[index].type_attr = type_attr;
}

static void	idt_install(){
	idt_set_gate(0, (u32)isr0, CODE_SEGMENT, 0x8E);
	idt_set_gate(1, (u32)isr1, CODE_SEGMENT, 0x8E);
	idt_set_gate(2, (u32)isr2, CODE_SEGMENT, 0x8E);
	idt_set_gate(3, (u32)isr3, CODE_SEGMENT, 0x8E);
	idt_set_gate(4, (u32)isr4, CODE_SEGMENT, 0x8E);
	idt_set_gate(5, (u32)isr5, CODE_SEGMENT, 0x8E);
	idt_set_gate(6, (u32)isr6, CODE_SEGMENT, 0x8E);
	idt_set_gate(7, (u32)isr7, CODE_SEGMENT, 0x8E);
	idt_set_gate(8, (u32)isr8, CODE_SEGMENT, 0x8E);
	idt_set_gate(9, (u32)isr9, CODE_SEGMENT, 0x8E);
	idt_set_gate(10, (u32)isr10, CODE_SEGMENT, 0x8E);
	idt_set_gate(11, (u32)isr11, CODE_SEGMENT, 0x8E);
	idt_set_gate(12, (u32)isr12, CODE_SEGMENT, 0x8E);
	idt_set_gate(13, (u32)isr13, CODE_SEGMENT, 0x8E);
	idt_set_gate(14, (u32)isr14, CODE_SEGMENT, 0x8E);
	idt_set_gate(15, (u32)isr15, CODE_SEGMENT, 0x8E);
	idt_set_gate(16, (u32)isr16, CODE_SEGMENT, 0x8E);
	idt_set_gate(17, (u32)isr17, CODE_SEGMENT, 0x8E);
	idt_set_gate(18, (u32)isr18, CODE_SEGMENT, 0x8E);
	idt_set_gate(19, (u32)isr19, CODE_SEGMENT, 0x8E);
	idt_set_gate(20, (u32)isr20, CODE_SEGMENT, 0x8E);
	idt_set_gate(21, (u32)isr21, CODE_SEGMENT, 0x8E);
	idt_set_gate(22, (u32)isr22, CODE_SEGMENT, 0x8E);
	idt_set_gate(23, (u32)isr23, CODE_SEGMENT, 0x8E);
	idt_set_gate(24, (u32)isr24, CODE_SEGMENT, 0x8E);
	idt_set_gate(25, (u32)isr25, CODE_SEGMENT, 0x8E);
	idt_set_gate(26, (u32)isr26, CODE_SEGMENT, 0x8E);
	idt_set_gate(27, (u32)isr27, CODE_SEGMENT, 0x8E);
	idt_set_gate(28, (u32)isr28, CODE_SEGMENT, 0x8E);
	idt_set_gate(29, (u32)isr29, CODE_SEGMENT, 0x8E);
	idt_set_gate(30, (u32)isr30, CODE_SEGMENT, 0x8E);
	idt_set_gate(31, (u32)isr31, CODE_SEGMENT, 0x8E);
}


static void	init_idt(){
	idt_p.limit = sizeof(idt_gate) * (256 - 1);
	idt_p.base = (u32)&idt_gates;
	idt_install();
	__asm__ __volatile__ ("lidt (%%eax)": : "a"(&idt_p));
}

char *interrupt_msgs(u8 index){
	switch (index)
	{
	case 0:	return("Division By Zero");
	case 1:	return("One step exception");
	case 2:	return ("Non Maskable Interrupt");
    case 3:	return ("Breakpoint");
    case 4:	return ("Overflow");
    case 5:	return ("bound Range Exceeded");
    case 6:	return ("Invalid Opcode");
    case 7:	return ("Device Not Available");
    case 8:	return ("Double Fault");
    case 9:	return ("Coprocessor Segment Overrun");
    case 10:	return ("Invalid TSS");
    case 11:	return ("Segment Not Present");
    case 12:	return ("Stack-Segment Fault");
    case 13:	return ("General Protection Fault");
    case 14:	return ("Page Fault");
    case 15:	return ("Reserved");
    case 16:	return ("x87 Floating-Point Exception");
    case 17:	return ("Alignment Check");
    case 18:	return ("Machine Check");
    case 19:	return ("SIMD Floating-Point Exception");
    case 20:	return ("Virtualization Exception");
    case 21:	return ("Control Protection Exception");
    case 22:	return ("Reserved");
    case 23:	return ("Reserved");
    case 24:	return ("Reserved");
    case 25:	return ("Reserved");
    case 26:	return ("Reserved");
    case 27:	return ("Reserved");
    case 28:	return ("Hypervisor Injection Exception");
    case 29:	return ("VMM Communication Exception");
    case 30:	return ("Security Exception");
    case 31:	return ("Reserved");
	default:	return ("Unknown");
	}
}

extern void	isr_handler(_registers r){
	put_str("\r\n");
	put_str("Inerrupt received: ");
	put_nbr(r.int_no, HEX_FORMAT);
	put_str(" >> ");
	put_str(interrupt_msgs(r.int_no));
	put_str("\r\n");
}

void	init_descriptor_tables(){
	init_idt();
}