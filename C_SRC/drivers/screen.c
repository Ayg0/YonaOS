#include "../INCLUDE/general.h"

void	print_char(u8 c, u32 color, u32 col, u32 row){
	u32	location;

	location = col * 2 + row * (MAX_ROW * 2);
	*((u8 *)VIDEOMEMORY + location) = c; 
	*((u8 *)VIDEOMEMORY + location) = color; 
	return;
}

void	print_str(u8 *s, u32 color, u32 col, u32 row){
	u32 j;

	j = 0;
	color += WB * (!color);	// if no colors assigned asign default WB
	while (s[j])
	{
		row += (col == MAX_COL) + (-row * (row == MAX_ROW));
		col += -col * (col == MAX_COL);
		if (s[j] == '\n')
			row += 1;
		print_char(s[j], 0x0f, col, row);
		col++;
		j++;
	}
	return; 
}