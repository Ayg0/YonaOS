#ifndef KEYBOARD_H
# define KEYBOARD_H

# include "irqs.h"
# include "descriptor_tables.h"

typedef struct buffer
{
	u8 buffer[256];
	u8 index;
} _buffer;

typedef struct keyboard_flags
{
	u8	NL;
	u8	ALT;
	u8	CTRL;
	u8	SHIFT;
	u8	NUMLOCK;
	u8	CAPLOCK;
} _key_flags;

# define CAP_OPT(CAPLOCK, SHIFT) (CAPLOCK & !SHIFT | !CAPLOCK & SHIFT)

u8 		back_space();
_buffer	*get_buffer();
void	init_keyboard();
u8		get_buffer_index();
u8		keyboard_new_line();
void	clear_keyboard_buffer();
#endif