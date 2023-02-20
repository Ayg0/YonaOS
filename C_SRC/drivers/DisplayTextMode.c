#include "../INCLUDE/system.h"

screen	_screen;

/*
	Initialization routine
	Cursor control routines
	Drawing routines
	Font rendering routines
	Input/output routines
	Mode switching routines
	Memory management routines
*/

void	screen_init(u16 mode){
	_screen._cursor.mode = 1;
	_screen._cursor.x = 0;
	_screen._cursor.y = 0;
}

// setting the location of the cursor
int	set_cursor(u16 x, u16 y){
	u8 location;

	if (x >= MAX_COL || y >= MAX_ROW)
		return (-1);
	_screen._cursor.x = x;
	_screen._cursor.y = y;
	location = x + (y * MAX_COL);
	// read more about the Cursor Location High Register (Index 0x0E)
    Pbyte_out(SCREEN_CRTL, 0x0E);
    Pbyte_out(SCREEN_DATA, (location >> 8));
	// read more about the Cursor Location Low Register (Index 0x0F)
    Pbyte_out(SCREEN_CRTL, 0x0F);
    Pbyte_out(SCREEN_DATA, (location & 0xff));
	return 0;
}

void	cursor_mode(u8 enabled){
	if (_screen._cursor.mode == enabled)
		return	;
	if (enabled)
	{
		Pbyte_out(0x3D4, 0x0A);
		Pbyte_out(0x3D5, Pbyte_in(0x3D5) & 0xDF);
	}
	else{
		Pbyte_out(0x3D4, 0x0A);
		Pbyte_out(0x3D5, Pbyte_in(0x3D5) | 0x20);
	}
	_screen._cursor.mode = enabled;
}

void	put_char(u8 c, u16 attr){
	u32	location;

	if (!attr)
		attr = WB;
	location = _screen._cursor.x * 2 + _screen._cursor.y * (MAX_COL * 2);
	*((u8 *)VIDEOMEMORY + location) = c; 
	*((u8 *)VIDEOMEMORY + location + 1) = attr;
	_screen._cursor.x++;
	if (_screen._cursor.x == MAX_COL){
		_screen._cursor.x = 0;
		_screen._cursor.y++;
	}
	set_cursor(_screen._cursor.x, _screen._cursor.y);
	return;
}

void	put_str(u8 *s, u16 attr){
	u32	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\r')
			_screen._cursor.y = 0;
		else if (s[i] == '\n')
			_screen._cursor.y++;
		else
			put_char(s[i], 0);
		i++;
	}
	return; 
}