#include "general.h"

extern int	main();

int	main() {
    char* video_memory = (char*) 0xb8002;
    *video_memory = 'A';
    *(video_memory + 1) = 0xf0;
	print_char('W', 0xf0, 0, 0);
	print_char('O', 0xf0, 1, 0);
	print_char('W', 0xf0, 2, 0);
	print_char(' ', 0xf0, 3, 0);
	print_char('W', 0xf0, 4, 0);
	print_char('O', 0xf0, 5, 0);
	print_char('R', 0xf0, 6, 0);
	print_char('K', 0xf0, 7, 0);
	print_char('I', 0xf0, 8, 0);
	print_char('N', 0xf0, 9, 0);
	print_char('G', 0xf0, 10, 0);
	return (5);
}