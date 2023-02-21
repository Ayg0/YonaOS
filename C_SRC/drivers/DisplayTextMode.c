#include "../INCLUDE/system.h"

screen	_screen;

/*
	/Initialization routine
	/Cursor control routines
	//Drawing routines
	//Font rendering routines
	/Input/output routines
	/Mode switching routines
	//Memory management routines
*/
// basic screen init
void	screen_init(u16 mode){
	_screen._cursor.mode = 1;
	_screen._cursor.x = 0;
	_screen._cursor.y = 0;
}

// setting the location of the cursor
int	set_cursor(u16 x, u16 y){
	u16 location;

	_screen._cursor.x = x;
	_screen._cursor.y = y;
	location = x + (y * MAX_COL);
	// read more about the Cursor Location High Register (Index 0x0E)
    Pbyte_out(SCREEN_CRTL, 0x0E);
    Pbyte_out(SCREEN_DATA, (u8)(location >> 8));
	// read more about the Cursor Location Low Register (Index 0x0F)
    Pbyte_out(SCREEN_CRTL, 0x0F);
    Pbyte_out(SCREEN_DATA, (u8)(location & 0xff));
	return 0;
}
// hide or show the cursor
void	cursor_mode(u8 enabled){
	if (enabled)
	{
		Pbyte_out(0x3D4, 0x0A);
		Pbyte_out(0x3D5, Pbyte_in(0x3D5) & 0xC0);
		Pbyte_out(0x3D4, 0x0B);
		Pbyte_out(0x3D5, (Pbyte_in(0x3D5) & 0xE0) | 15);
	}
	else{
		Pbyte_out(0x3D4, 0x0A);
		Pbyte_out(0x3D5, Pbyte_in(0x3D5) | 0x20);
	}
	_screen._cursor.mode = enabled;
}
// puts a number into the screen
int	put_nbr_base(u32 nbr, char *s, u8 base_len){
	if (nbr >= base_len)
		put_nbr_base(nbr / base_len, s, base_len);
	put_char(s[nbr % base_len], 0, 0x09);
	return (7);
}
// puts a character into the screen
void	put_char(u8 c, u8 use_default, u16 attr){
	u32	location;

	if (use_default)
		attr = WB;
	location = (_screen._cursor.x + _screen._cursor.y * MAX_COL) * 2;
	*((u8 *)VIDEOMEMORY + location) = c; 
	*((u8 *)VIDEOMEMORY + location + 1) = attr;
	_screen._cursor.x++;
	if (_screen._cursor.x == MAX_COL){
		_screen._cursor.x = 0;
		_screen._cursor.y++;
	}
	if (_screen._cursor.y == MAX_ROW){
		for (u16 i = 0; i < MAX_ROW - 1; i++)
			t_memcpy((void *)VIDEOMEMORY + (i * MAX_COL_2), (void *)VIDEOMEMORY + ((i + 1) * MAX_COL_2), MAX_COL_2);
		t_WordSet((void *)VIDEOMEMORY + ((MAX_ROW - 1) * MAX_COL_2), 0x0f00, 80);
		_screen._cursor.y = MAX_ROW - 1;
	}
	set_cursor(_screen._cursor.x, _screen._cursor.y);
	return;
}
// put a string into the screen
int	put_str(u8 *s, u16 attr){
	u32	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\r')
			_screen._cursor.x = 0;
		else if (s[i] == '\n')
			_screen._cursor.y++;
		else
			put_char(s[i], 1, 0);
		i++;
	}
	return (1); 
}
// clear the screen
void	clrs(){
	for (u8 i = 0; i < 25; i++)
		t_WordSet((void *)VIDEOMEMORY + (i * MAX_COL_2), 0x0f00, 80);
	set_cursor(0, 0);
}
// print a number in binary('b'), decimal('d') or hex('h') formats
void put_nbr(u32 nbr, u8 format){
	char *hex = "0123456789ABCDEF";
	char *decimal = "0123456789";
	char *binary = "01";

	format == 'h' && put_str("0x", 0) && put_nbr_base(nbr, hex, 16);
	format == 'd' && put_nbr_base(nbr, decimal, 10);
	format == 'b' && put_nbr_base(nbr, binary, 2);
	return ;
}
// scroll the screen
