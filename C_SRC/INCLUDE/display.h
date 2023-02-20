#ifndef DISPLAY_H
# define DISPLAY_H
# include "typedefs.h"

typedef struct s_cursor
{
	u8	mode;
	u16	x;
	u16 y;
}	cursor;

typedef struct s_screen
{
	cursor	_cursor;
}	screen;


// TextMode:

void	put_char(u8 c, u16 attr);
void	put_str(u8 *s, u16 attr);
void	cursor_mode(u8 enabled);
int		set_cursor(u16 x, u16 y);
void	screen_init(u16 mode);

#endif