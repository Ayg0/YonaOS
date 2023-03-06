#ifndef DISPLAY_H
# define DISPLAY_H
# include "typedefs.h"

// R http://www.osdever.net/FreeVGA/vga/vga.htm#register

// DEVICE I/O ports
	# define SCREEN_CRTL 0x3D4
	/*
		this is one of the most used indexed registers.
		The index byte is written to the port given, then the data byte
		can be read/written from/to port+1 (0x3D5)
	*/
	# define SCREEN_DATA 0x3D5

//SCREEN RELATED
	# define VIDEOMEMORY 0xb8000
	# define MAX_COL 80
	# define MAX_COL_2 160
	# define MAX_ROW 25

// FUNCTIONS RELATED
	# define BINARY_FORMAT	'b'
	# define DECIMAL_FORMAT	'd'
	# define HEX_FORMAT		'h'

//colors:
# define WHITE_ON_BLACK	0x0F
# define BLACK			0x00
# define BLUE			0x01
# define GREEN			0x02
# define CYAN			0x03
# define RED			0x04
# define PURPLE			0x05
# define BROWN			0x06
# define GRAY			0x07
# define DARK_GRAY		0x08
# define DARK_BLUE		0x09
# define DARK_GREEN		0x0A
# define DARK_CYAN		0x0B
# define DARK_RED		0x0C
# define DARK_PURPLE	0x0D
# define YELLOW			0x0E
# define WHITE			0x0F

// USED THE CODE FROM R https://files.osdev.org/mirrors/geezer/osd/graphics/modes.c
// I tried to read more from the www.osdever.net, while still not having a very clear understanding, I'll use it for now to switch

# define MISC_OUTPUT_REG_WR 0x3C2 // http://www.osdever.net/FreeVGA/vga/extreg.htm
# define FEATURE_CTRL_REG	0x3DA	

# define SEQ_REG_ADDR		0x3C4 // http://www.osdever.net/FreeVGA/vga/seqreg.htm
# define SEQ_REG_DATA		0x3C5

# define CRTC_REG_ADDR		0x3D4 // http://www.osdever.net/FreeVGA/vga/crtcreg.htm
# define CRTC_REG_DATA		0x3D5

# define GRAP_REG_ADDR		0x3CE // http://www.osdever.net/FreeVGA/vga/graphreg.htm
# define GRAP_REG_DATA		0x3CF

# define ATTR_REG_ADDR		0x3C0 // http://www.osdever.net/FreeVGA/vga/attrreg.htm
# define ATTR_REG_DATA		0x3C1

# define TEXT_MODE_80x25		0
# define VIDEO_MODE_320x200x256	1

typedef struct s_cursor
{
	u8	mode;
	u8	x;
	u8	y;
}	cursor;

typedef struct s_screen
{
	cursor	_cursor;
	u8		default_attr;
	u8		screen_mode;
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
void	protection_flag(u8 state);
void	clrs();
void	new_line();
void	display_back_space();
void	change_vga_mode(u8 mode);

#endif