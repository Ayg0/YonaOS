#include "../INCLUDE/timer.h"
#include "../INCLUDE/system.h"
#include "../INCLUDE/display.h"

u32 time;

// R https://wiki.osdev.org/Programmable_Interval_Timer

void	tick(_registers r){
	time++;
	put_str("tick: ");
	put_nbr(time, DECIMAL_FORMAT);
	put_str("\r\n");
}
// initializing the timer with the frequency needed
void	init_timer(u32 frequency){

	set_handler(32, (u32)tick);
	u32 divisor = 1193180 / frequency;

	// Configuration of the PIT to send the divisor to CHANNEL 0
	Pbyte_out(COMMAND_REG, CONFIGURE_PIT(PIT_CHANNEL0, PIT_LHB, MODE3, PIT_BINARY));
	// send the frequency divisor
	Pbyte_out(C0DP, L8(divisor));
	Pbyte_out(C0DP, H8(divisor));
}