#ifndef GENERAL_H
# define GENERAL_H

# include "typedefs.h"
// LOW 8 Bits
# define L8(VAL) VAL & 0xFF
// LOW 16 Bits
# define L16(VAL) VAL & 0xFFFF
// HIGH 8 Bits
# define H8(VAL) ((VAL >> 8) & 0xFF)
// HIGH 16 Bits
# define H16(VAL) ((VAL >> 16) & 0xFFFF)

// used by drivers:
void	Pword_out(u16 port_number, u16 value);
void	Pbyte_out(u16 port_number, u8 value);
u16		Pword_in(u16 port_number);
u8		Pbyte_in(u16 port_number);
#endif