#include "../../INCLUDE/irqs.h"
#include "../../INCLUDE/system.h"
#include "../../INCLUDE/display.h"
#include "../../INCLUDE/timer.h"
#include "../../INCLUDE/descriptor_tables.h"

u32	ints_handlers[256];

// sending end of interrupt
static void	PIC_EOI(u8 irq){
	if (irq >= 40)
		Pbyte_out(PIC_SLAVE_COMMAND, 0x20);
	Pbyte_out(PIC_MASTER_COMMAND, 0x20);
}
// MR = MAY READ
// MR https://pdos.csail.mit.edu/6.828/2010/readings/hardware/8259A.pdf
// R http://www.osdever.net/tutorials/view/programming-the-pic
// R https://forum.osdev.org/viewtopic.php?f=1&t=32677

void	remap_pic(){
// ICW (Initialization Commands words)
	// ICW1 : starts the initialization sequence (in cascade mode)
	Pbyte_out(PIC_MASTER_COMMAND, 0x11);
	io_wait();	// used in older hardware so it gives some time for it to react
	Pbyte_out(PIC_SLAVE_COMMAND, 0x11);
	io_wait();
	// ICW2
	Pbyte_out(PIC_MASTER_DATA, 0x20);	// offset at 32
	io_wait();
	Pbyte_out(PIC_SLAVE_DATA, 0x28);	// offset at 40
	io_wait();
	// IWC3
	Pbyte_out(PIC_MASTER_DATA, 1 << 2);	// Indecating that the Slave PIC is connected to IRQ2 to the Master PIC 
	io_wait();
	Pbyte_out(PIC_SLAVE_DATA, 2);		// Indecating that the Slave PIC's Cascade Identity is 2
	io_wait();
	// IWC4 is used for telling that we are working in a 80x86 architecture
	Pbyte_out(PIC_MASTER_DATA, 0x01);
	io_wait();
	Pbyte_out(PIC_SLAVE_DATA,0x01);
	io_wait();
	// enable all interrupt requests in both PICS
	Pbyte_out(PIC_MASTER_DATA, 0x00);
	io_wait();
	Pbyte_out(PIC_SLAVE_DATA,0x00);
	io_wait();
}

void	set_handler(u8 index, u32 handler){
	ints_handlers[index] = handler;
}

extern void	irq_handler(_registers r){
	void (*f)(_registers);
	PIC_EOI(r.int_no); // after each interrupt we need to send the EOI signal, or the PICs will not send any more interrupts.
	if (ints_handlers[r.int_no] != 0){
		f = (void *)ints_handlers[r.int_no];
		f(r);
	}
	else
		put_str("k\r\n");
}