#include "../INCLUDE/timer.h"
#include "../INCLUDE/system.h"
#include "../INCLUDE/display.h"

u32 	ticks;
_time	date;

// R https://wiki.osdev.org/Programmable_Interval_Timer

void	tick(_registers r){

	ticks++;
	//set_cursor(71, 24);
	//date.s += (ticks == FREQUENCY) && !(ticks = 0);
	//date.m += (date.s == 60) && !(date.s = 0);
	//date.h += (date.m == 60) && !(date.m = 0);
	//date.d += (date.h == 24) && !(date.h = 0);
	//date.mo += (date.d == 31) && !(date.d = 0);
	//if (date.h < 10)
	//	put_str("0");
	//put_nbr(date.h, DECIMAL_FORMAT);
	//put_str(":");
	//if (date.m < 10)
	//	put_str("0");
	//put_nbr(date.m, DECIMAL_FORMAT);
	//put_str(":");
	//if (date.s < 10)
	//	put_str("0");
	//put_nbr(date.s, DECIMAL_FORMAT);
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