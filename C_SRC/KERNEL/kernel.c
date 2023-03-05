#include "../INCLUDE/libt.h"
#include "../INCLUDE/timer.h"
#include "../INCLUDE/system.h"
#include "../INCLUDE/display.h"
#include "../INCLUDE/keyboard.h"
#include "../INCLUDE/user_programs.h"
#include "../INCLUDE/descriptor_tables.h"

extern int	main();


void	main_init(){
	screen_init(1);
	init_descriptor_tables();
	init_timer(50);
	init_keyboard();
	__asm__ __volatile__ ("sti");
}

int	main() {
	main_init();

	while (1)
	{
		put_str("KASH $> ");
		while (!keyboad_new_line());
		if (!t_strcmp(get_buffer()->buffer, "draw"))
			draw_face();
		if (!t_strcmp(get_buffer()->buffer, "clear"))
			clrs();
		else if (!t_strcmp(get_buffer()->buffer, "exit")){
			clrs();
			put_str("Nice Work now turn the power-off\r\n:( Idk how to do it yet.");
			cursor_mode(0);
			break ;
		}
		clear_keyboard_buffer();
	}
	return (5);
}