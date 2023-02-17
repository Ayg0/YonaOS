#include "general.h"

extern int	main();

int	main() {
	const char *s = "I see that you're working now.";
	int j = 0;
	while (s[j])
	{
		print_char(s[j], 0x0f, j, 0);
		j++;
	}
	
	return (5);
}