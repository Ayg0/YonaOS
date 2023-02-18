#ifndef GENERAL_H
# define GENERAL_H
# include "Macros.h"
# include "typedefs.h"

// used by drivers:
void	Pword_out(u16 port_number, u16 value);
void	Pbyte_out(u16 port_number, u8 value);
u16		Pword_in(u16 port_number);
u8		Pbyte_in(u16 port_number);

// screen.h
void	print_char(u8 c, u32 color, u32 col, u32 row);
void	print_str(u8 *s, u32 color, u32 col, u32 row);

#endif