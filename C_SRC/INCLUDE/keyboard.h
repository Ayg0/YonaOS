#ifndef KEYBOARD_H
# define KEYBOARD_H

# include "irqs.h"
# include "descriptor_tables.h"

typedef struct buffer
{
	u8 buffer[256];
	u8 index;
} _buffer;


u8 		back_space();
_buffer	*get_buffer();
void	init_keyboard();
u8		get_buffer_index();
u8		keyboad_new_line();
void	clear_keyboard_buffer();
#endif