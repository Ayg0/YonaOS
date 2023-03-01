#ifndef DISPLAY_H
# define DISPLAY_H
# include "typedefs.h"

typedef struct s_cursor
{
	u8	mode;
	u8	x;
	u8 y;
}	cursor;

typedef struct s_screen
{
	cursor	_cursor;
	u16		default_attr;
}	screen;


// TextMode:

void	put_char(u8 c, u8 use_default, u16 attr);
u8		put_str(u8 *s);
void	set_default_attr(u16 attr);
void	put_nbr(u32 nbr, u8 format);
void	cursor_mode(u8 enabled);
u8		get_attr(u8 foreground_color, u8 back_ground_color);
u8		position_check();
u8		set_cursor(u8 x, u8 y);
void	screen_init(u16 mode);
void	clrs();

#endif