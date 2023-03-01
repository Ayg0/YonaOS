#include "../INCLUDE/system.h"

extern int	main();

int	main() {
	screen_init(1);
	init_descriptor_tables();

	put_str("ok");
	__asm__ __volatile__ ("int $0");
	__asm__ __volatile__ ("int $1");
	__asm__ __volatile__ ("int $2");
	__asm__ __volatile__ ("int $6");
	return (5);
}