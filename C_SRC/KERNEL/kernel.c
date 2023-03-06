#include "../INCLUDE/libt.h"
#include "../INCLUDE/timer.h"
#include "../INCLUDE/system.h"
#include "../INCLUDE/display.h"
#include "../INCLUDE/keyboard.h"
#include "../INCLUDE/user_programs.h"
#include "../INCLUDE/descriptor_tables.h"

extern int	main();
u8 HOLD;

void	main_init(){
	HOLD = 1;
	screen_init(1);
	init_descriptor_tables();
	init_timer(50);
	init_keyboard();
	__asm__ __volatile__ ("sti");
}
void exit(){
	HOLD = 0;
	clrs();
	put_str("Nice Work now turn the power-off\r\n:( Idk how to do it yet.");
	cursor_mode(0);
}

char *valid_cmds[] = {
	"clear",
	"draw",
	"exit",
	"time",
	"date",
	"set time",
	"set date",
};

void (*functions[])() = {
	clrs,
	draw_face,
	exit,
	put_time,
	put_date,
	set_time,
	set_date,
};

void	check_and_exec(char *buff){
	u32 i;
	void (*f)();

	for (i = 0; valid_cmds[i]; i++){
		if (!t_strcmp(buff, valid_cmds[i]))
			functions[i]();
	}
}

int	main() {
	main_init();

	while (HOLD)
	{
		prompt("YOT $> ");
		check_and_exec(get_buffer()->buffer);
		clear_keyboard_buffer();
	}
	
	return (5);
}