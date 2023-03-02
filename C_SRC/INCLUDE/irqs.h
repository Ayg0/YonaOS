#ifndef IRQS_H
# define IRQS_H

# define PIC_MASTER_COMMAND	0x0020
# define PIC_MASTER_DATA	0x0021
# define PIC_SLAVE_COMMAND	0x00A0
# define PIC_SLAVE_DATA		0x00A1

void	remap_pic();

#endif