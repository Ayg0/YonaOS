#include "../INCLUDE/system.h"



extern int	main();

int	main() {
	char *s = "Imane l3iyana";
	screen_init(1);
	set_cursor(2, 2);
	cursor_mode(0);
	cursor_mode(1);
	put_str(s, 0);
	return (5);
}