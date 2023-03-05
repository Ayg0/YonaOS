#include "../INCLUDE/libt.h"
#include "../INCLUDE/system.h"
#include "../INCLUDE/display.h"

screen	_screen;

// basic screen init
void	screen_init(u16 mode){
	_screen._cursor.mode = 1;
	_screen._cursor.x = 0;
	_screen._cursor.y = 0;
	_screen.default_attr = WHITE_ON_BLACK;
}
// set the default attribute for the characters on screen
void	set_default_attr(u16 attr){
	_screen.default_attr = attr;
}

// setting the location of the cursor
u8	set_cursor(u8 x, u8 y){
	u16 location;

	_screen._cursor.x = x;
	_screen._cursor.y = y;
	position_check();
	location = _screen._cursor.x + (_screen._cursor.y * MAX_COL);
	// read more about the Cursor Location High Register (Index 0x0E)
    Pbyte_out(SCREEN_CRTL, 0x0E);
    Pbyte_out(SCREEN_DATA, (u8)H8(location));
	// read more about the Cursor Location Low Register (Index 0x0F)
    Pbyte_out(SCREEN_CRTL, 0x0F);
    Pbyte_out(SCREEN_DATA, (u8)L8(location));
	return 0;
}
// hide or show the cursor
void	cursor_mode(u8 enabled){
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
// puts a number into the screen
int	put_nbr_base(u32 nbr, char *s, u8 base_len){
	if (nbr >= base_len)
		put_nbr_base(nbr / base_len, s, base_len);
	put_char(s[nbr % base_len], 1, 0);
	return (7);
}

void	LineBeginning(){
	set_cursor(0, _screen._cursor.y);
}

void	new_line_only(){
	set_cursor(_screen._cursor.x, ++_screen._cursor.y);
}

void	new_line(){
	set_cursor(0, ++_screen._cursor.y);
}

// check the position if it's valid
u8	position_check(){
	u8	err_flag = 0;
	
	if (_screen._cursor.x > MAX_COL || _screen._cursor.y > MAX_ROW)
	{
		set_default_attr(get_attr(RED, BLACK));
		_screen._cursor.x = 0;
		_screen._cursor.y = 0;
	}
	if (_screen._cursor.x == MAX_COL){
		
		_screen._cursor.x = 0;
		if (_screen._cursor.y != MAX_ROW)
			_screen._cursor.y++;
		err_flag = 1;
	}
	if (_screen._cursor.y == MAX_ROW){
		for (u16 i = 0; i < MAX_ROW - 1; i++)
			t_memcpy((void *)VIDEOMEMORY + (i * MAX_COL_2), (void *)VIDEOMEMORY + ((i + 1) * MAX_COL_2), MAX_COL_2);
		t_WordSet((void *)VIDEOMEMORY + ((MAX_ROW - 1) * MAX_COL_2), 0x0f00, 80);
		_screen._cursor.y = MAX_ROW - 1;
		err_flag = 1;
	}
	return(err_flag);
}

void	display_back_space(){
	u8 x, y;

	x = -(_screen._cursor.x != 0) + ((_screen._cursor.x == 0) * (MAX_COL - 1));
	y = -(_screen._cursor.x == 0);
	_screen._cursor.x += x;
	_screen._cursor.y += y;
	x = _screen._cursor.x;
	y = _screen._cursor.y;
	put_char(' ', 1, 1);
	set_cursor(x, y);
}

// puts a character into the screen
void	put_char(u8 c, u8 use_default, u16 attr){
	u32	location;

	if (use_default)
		attr = _screen.default_attr;
	position_check(); // protection flag for the check
	location = (_screen._cursor.x + _screen._cursor.y * MAX_COL) * 2;
	*((u8 *)VIDEOMEMORY + location) = c;
	*((u8 *)VIDEOMEMORY + location + 1) = attr;
	_screen._cursor.x++;
	_screen._cursor.mode && set_cursor(_screen._cursor.x, _screen._cursor.y);
	return;
}
// put a string into the screen
u8	put_str(u8 *s){
	u32	i;

	i = 0;
	while (s[i])
	{
		//put_nbr(_screen._cursor.x, DECIMAL_FORMAT);
		if (s[i] == '\r')
			LineBeginning();
		else if (s[i] == '\n')
			new_line_only();
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
// print a number in BINARY_FORMAT, DECIMAL_FORMAT or HEX_FORMAT.
void put_nbr(u32 nbr, u8 format){
	char *hex = "0123456789ABCDEF";
	char *decimal = "0123456789";
	char *binary = "01";

	format == 'h' && put_str("0x") && put_nbr_base(nbr, hex, 16);
	format == 'd' && put_nbr_base(nbr, decimal, 10);
	format == 'b' && put_nbr_base(nbr, binary, 2);
	return ;
}

// make an attribute for Text Mode
u8 get_attr(u8 foreground_color, u8 back_ground_color){
	return ((back_ground_color << 4) | (foreground_color & 0x0f));
}
