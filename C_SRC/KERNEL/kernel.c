#include "../INCLUDE/timer.h"
#include "../INCLUDE/system.h"
#include "../INCLUDE/display.h"
#include "../INCLUDE/descriptor_tables.h"

extern int	main();


void	main_init(){
	screen_init(1);
	init_descriptor_tables();
	init_timer(50);
	__asm__ __volatile__ ("sti");
}

int	main() {
	main_init();	// don't remove it.

	put_str("ok");
	//__asm__ __volatile__ ("int $2");
	//__asm__ __volatile__ ("int $6");
	return (5);
}