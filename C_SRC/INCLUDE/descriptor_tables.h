#ifndef	DESCRIPTOR_TABLES
# define DESCRIPTOR_TABLES

# include "typedefs.h"
# define USED_HANDLERS 32
// IDT
	/*
		The interrupt descriptor table contains entry(gate) with the addresses to the routines of which you'll jump to
		if you encounter that interrupt.
	*/

typedef struct _idt_gate{
	u16	low_base;		// low 16 bits of the address to jump to
	u16	segment_sel;	//	segment selector
	u8	always0;		// this will always equ 0
	u8	type_attr;		// type_attr (4bits), DPL (2bits), P (1 bit)
	/*  7 6  5 4       0
		[P|PDL|type_attr]
		https://wiki.osdev.org/Interrupt_Descriptor_Table#IDTR
		https://stackoverflow.com/questions/3425085/the-difference-between-call-gate-interrupt-gate-trap-gate
	*/
	u16	high_base;		// high 16 bits of the address.
}	__attribute__((packed)) idt_gate;

typedef struct _idt_ptr
{
	u16	limit;
	u32	base;		// address of the first element in the idt_gate array
}__attribute__((packed)) idt_ptr;

typedef struct registers
{
	//https://www.eecg.utoronto.ca/~amza/www.mindsec.com/files/x86regs.html
	u32 ds;	// data segment selector
	u32	edi, esi, ebp, esp, ebx, edx, ecx, eax; // pushed by pusha /*https://pdos.csail.mit.edu/6.828/2005/readings/i386/PUSHA.htm*/
	u32 int_no, error_code;	// interrupt index and error code
	u32	eip, cs, eflags, useresp, ss; // pushed by the cpu automatically
} _registers;


// CPU exceptions ISRs
extern	void	isr0();
extern	void	isr1();
extern	void	isr2();
extern	void	isr3();
extern	void	isr4();
extern	void	isr5();
extern	void	isr6();
extern	void	isr7();
extern	void	isr8();
extern	void	isr9();
extern	void	isr10();
extern	void	isr11();
extern	void	isr12();
extern	void	isr13();
extern	void	isr14();
extern	void	isr15();
extern	void	isr16();
extern	void	isr17();
extern	void	isr18();
extern	void	isr19();
extern	void	isr20();
extern	void	isr21();
extern	void	isr22();
extern	void	isr23();
extern	void	isr24();
extern	void	isr25();
extern	void	isr26();
extern	void	isr27();
extern	void	isr28();
extern	void	isr29();
extern	void	isr30();
extern	void	isr31();

void	init_descriptor_tables();
void	isr_handler(_registers r);

#endif
