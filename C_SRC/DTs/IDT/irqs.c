#include "../../INCLUDE/irqs.h"
#include "../../INCLUDE/system.h"
#include "../../INCLUDE/descriptor_tables.h"

// sending end of interrupt
static void	PIC_EOI(u8 irq){
	if (irq >= 8)
		Pbyte_out(PIC_SLAVE_COMMAND, 0x20);
	Pbyte_out(PIC_MASTER_COMMAND, 0x20);
}
// R https://pdos.csail.mit.edu/6.828/2010/readings/hardware/8259A.pdf

void	remap_pic(){
	u8	offset_Master;
	u8	offset_Slave;
}
