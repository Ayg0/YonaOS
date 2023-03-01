#ifndef GENERAL_H
# define GENERAL_H
# include "macros.h"
# include "typedefs.h"
# include "display.h"
# include "libt.h"
# include "descriptor_tables.h"

// used by drivers:
void	Pword_out(u16 port_number, u16 value);
void	Pbyte_out(u16 port_number, u8 value);
u16		Pword_in(u16 port_number);
u8		Pbyte_in(u16 port_number);
#endif