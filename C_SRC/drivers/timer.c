#include "../INCLUDE/libt.h"
#include "../INCLUDE/timer.h"
#include "../INCLUDE/system.h"
#include "../INCLUDE/display.h"
#include "../INCLUDE/keyboard.h"

u32 	ticks;
_time	date;

// R https://wiki.osdev.org/Programmable_Interval_Timer

void	tick(_registers r){
	ticks++;
	date.s += (ticks == FREQUENCY) && !(ticks = 0);
	date.m += (date.s == 60) && !(date.s = 0);
	date.h += (date.m == 60) && !(date.m = 0);
	date.d += (date.h == 24) && !(date.h = 0);
	date.mo += (date.d == 31) && !(date.d = 0);
}

void	put_time(){
	if (date.h < 10)
		put_str("0");
	put_nbr(date.h, DECIMAL_FORMAT);
	put_str(":");
	if (date.m < 10)
		put_str("0");
	put_nbr(date.m, DECIMAL_FORMAT);
	put_str(":");
	if (date.s < 10)
		put_str("0");
	put_nbr(date.s, DECIMAL_FORMAT);
	put_str("\r\n");
}
void	put_date(){
	if (date.d < 10)
		put_str("0");
	put_nbr(date.d, DECIMAL_FORMAT);
	put_str("/");
	if (date.mo < 10)
		put_str("0");
	put_nbr(date.mo, DECIMAL_FORMAT);
	put_str("/");
	put_nbr(date.year, DECIMAL_FORMAT);
	put_str("\r\n");
}

void	set_time(){
	clear_keyboard_buffer();
	prompt("Enter hours: ");
	date.h = t_atoi(get_buffer()->buffer);
	clear_keyboard_buffer();
	prompt("Enter minutes: ");
	date.m = t_atoi(get_buffer()->buffer);
	clear_keyboard_buffer();
	prompt("Enter s: ");
	date.s = t_atoi(get_buffer()->buffer);
	clear_keyboard_buffer();
}
void	set_date(){
	clear_keyboard_buffer();
	prompt("Enter day: ");
	date.d = t_atoi(get_buffer()->buffer);
	clear_keyboard_buffer();
	prompt("Enter month: ");
	date.mo = t_atoi(get_buffer()->buffer);
	clear_keyboard_buffer();
	prompt("Enter year: ");
	date.year = t_atoi(get_buffer()->buffer);
	clear_keyboard_buffer();
}


_time *get_date(){
	return (&date);
}

// initializing the timer with the frequency needed
void	init_timer(u32 frequency){
	u16	divisor;

	divisor = 1193180 / frequency;
	// Configuration of the PIT to send the divisor to CHANNEL 0
	Pbyte_out(COMMAND_REG, CONFIGURE_PIT(PIT_CHANNEL0, PIT_LHB, MODE3, PIT_BINARY));
	// send the frequency divisor
	Pbyte_out(C0DP, L8(divisor));
	Pbyte_out(C0DP, H8(divisor));
	set_handler(32, (u32)tick);
}