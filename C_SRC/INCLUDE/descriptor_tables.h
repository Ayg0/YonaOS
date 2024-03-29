#ifndef	DESCRIPTOR_TABLES
# define DESCRIPTOR_TABLES

# include "typedefs.h"
// MACROS
# define CODE_SEGMENT 0x08
# define GDT_ENTRIES 3
# define USED_HANDLERS 48

// GDT
	/* R https://wiki.osdev.org/GDT_Tutorial
		The Global Descriptor table contains entries telling the CPU about memory segments, their properties:
		starting location, permission ... ect.
		read more in the old GDT in assembly.
	*/
	// each gdt_entry
	typedef	struct gdt_entry{
		u16	low_limit;	// 0-15 bits of the limit
		u16	low_base;	// 0-15 bits of the base
		u8	middle_base;	// 16-23 bits of the base
		u8	access_bytes;	// access bytes
		u8	flags_highLimit;	// flags and the last 4 bits of the limit
		u8	high_base;		// 24-31 bits of the base
	}__attribute__ ((packed)) _gdt_entry;
	// the GDT_descriptor
	typedef	struct	gdt_p{
		u16	limit;	// size of the GDT
		u32	base;	//	start of the GDT
	}__attribute__ ((packed)) _gdt_ptr;

	void	init_gdt();
	extern	void gdt_load(u32 gdt_p);
// IDT
	/*
		The interrupt descriptor table contains entry(gate) with the addresses to the routines of which you'll jump to
		if you encounter that interrupt.
	*/
	typedef struct idt_gate{
		u16	low_base;		// low 16 bits of the address to jump to
		u16	segment_sel;	//	segment selector
		u8	always0;		// this will always equ 0
		u8	type_attr;		// type_attr (4bits), DPL (2bits), P (1 bit)
		/*  7 6  5 4       0
			[P|PDL|type_attr]
			R https://wiki.osdev.org/Interrupt_Descriptor_Table#IDTR
			R https://stackoverflow.com/questions/3425085/the-difference-between-call-gate-interrupt-gate-trap-gate
		*/
		u16	high_base;		// high 16 bits of the address.
	}	__attribute__((packed)) _idt_gate;
	
	typedef struct idt_ptr
	{
		u16	limit;
		u32	base;		// address of the first element in the idt_gate array
	}__attribute__((packed)) _idt_ptr;
	
	typedef struct registers
	{
		// R https://www.eecg.utoronto.ca/~amza/www.mindsec.com/files/x86regs.html
		u32 ds;	// data segment selector
		u32	edi, esi, ebp, esp, ebx, edx, ecx, eax; // pushed by pusha R https://pdos.csail.mit.edu/6.828/2005/readings/i386/PUSHA.htm
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

	extern	void	irq0();
	extern	void	irq1();
	extern	void	irq2();
	extern	void	irq3();
	extern	void	irq4();
	extern	void	irq5();
	extern	void	irq6();
	extern	void	irq7();
	extern	void	irq8();
	extern	void	irq9();
	extern	void	irq10();
	extern	void	irq11();
	extern	void	irq12();
	extern	void	irq13();
	extern	void	irq14();
	extern	void	irq15();
	
	void	init_idt();
	void	init_descriptor_tables();
	void	isr_handler(_registers r);
	extern void	irq_handler(_registers r);
	
#endif
