#include "INCLUDE/general.h"

void	print_char(int c, int color, int x, int y){
	*(VIDEOMEMORY + (x * 2) + (y * 80)) = c; 
	*(VIDEOMEMORY + (x * 2) + (y * 80) + 1) = color; 
	return; 
}