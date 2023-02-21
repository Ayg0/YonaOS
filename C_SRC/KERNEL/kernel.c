#include "../INCLUDE/system.h"

extern int	main();



int	main() {
	char *s = "0123456789";
	screen_init(1);
	set_cursor(75, 24);
	put_str(s, 0);
	clrs();
	//put_str("\r", 0);
	//put_str("\n", 0);
	//put_str("ok", 0);
	return (5);
}