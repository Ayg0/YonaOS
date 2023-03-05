#ifndef TIMER_H
# define TIMER_H
# include "descriptor_tables.h"
# include "irqs.h"

# define FREQUENCY 50

// Channel 0 data port (read/write)
# define C0DP 		0x40
// Channel 1 data port (read/write)
# define C1DP 		0x41
// Channel 2 data port (read/write)
# define C2DP 		0x42
// Mode/Command register (write only, a read is ignored)
# define COMMAND_REG	0x43
/*								CHANNEL (bits 6 and 7)								*/
	# define PIT_CHANNEL0		0B00000000 // select channel 0
	# define PIT_CHANNEL1		0B01000000 // select channel 1
	# define PIT_CHANNEL2		0B10000000 // select channel 2
	# define PIT_READ_BACK		0B11000000 // read-back command (8254 only)
/*								ACCESS (bits 6 and 7)								*/
	# define PIT_LATCH_COUNT	0B00000000 // latch count value command
	# define PIT_LB				0B00010000 // low byte only
	# define PIT_HB				0B00100000 // high byte only
	# define PIT_LHB			0B00110000 // low and high bytes
/*								OPERATING (bits 1 to 3)								*/
	# define MODE0				0B00000000 // interrupt on terminal count
	# define MODE1				0B00000010 // hardware re-triggerable one-shot
	# define MODE2				0B00000100 // rate generator
	# define MODE3				0B00000110 // square wave generator
	# define MODE4				0B00001000 // software triggered strobe
	# define MODE5				0B00001010 // hardware triggered strobe
	# define MODE6				0B00001100 // rate generator (same as mode 2)
	# define MODE7				0B00001110 // square wave generator (same as mode 3)
/*								COUNT (bits 1 to 3)								*/
	# define PIT_BINARY			0B00000000 // 16 bit binary
	# define PIT_BCD			0B00000001 // 4 digit BCD

// Command register configuration Macro
# define CONFIGURE_PIT(CHANNEL, ACCESS_MODE, OPERATING_MODE, BCD_BINARY) CHANNEL | ACCESS_MODE | OPERATING_MODE | BCD_BINARY


typedef struct time
{
	u8 s;
	u8 m;
	u8 h;
	u8 d;
	u8 mo;
} _time;



void	init_timer(u32 frequency);
void	tick(_registers r);

#endif