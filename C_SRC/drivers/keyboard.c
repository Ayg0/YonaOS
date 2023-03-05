# include "../INCLUDE/libt.h"
# include "../INCLUDE/system.h"
# include "../INCLUDE/display.h"
# include "../INCLUDE/keyboard.h"

// good but didn't read:
// R https://dev.to/frosnerd/writing-my-own-keyboard-driver-16kh
// R http://www.brokenthorn.com/Resources/OSDev19.html

_buffer buf;
u8 nl_flag = 0;

u8	get_char(u8 scancode){
	switch (scancode)
	{
	case 0x02: return '1';
	case 0x03: return '2';
	case 0x04: return '3';
	case 0x05: return '4';
	case 0x06: return '5';
	case 0x07: return '6';
	case 0x08: return '7';
	case 0x09: return '8';
	case 0x0A: return '9';
	case 0x0B: return '0';
	case 0x0C: return '-';
	case 0x1C:
		new_line();
		nl_flag = 1;
		return 0;
	case 0x0D: return '=';
	case 0x0E:
		return back_space();
	case 0x10: return 'Q';
	case 0x11: return 'W';
	case 0x12: return 'E';
	case 0x13: return 'R';
	case 0x14: return 'T';
	case 0x15: return 'Y';
	case 0x16: return 'U';
	case 0x17: return 'I';
	case 0x18: return 'O';
	case 0x19: return 'P';
	case 0x1A: return '[';
	case 0x1B: return ']';
	case 0x1E: return 'A';
	case 0x1F: return 'S';
	case 0x20: return 'D';
	case 0x21: return 'F';
	case 0x22: return 'G';
	case 0x23: return 'H';
	case 0x24: return 'J';
	case 0x25: return 'K';
	case 0x26: return 'L';
	case 0x27: return ';';
	case 0x28: return '\'';
	case 0x29: return '`';
	case 0x2B: return '\\';
	case 0x2C: return 'Z';
	case 0x2D: return 'X';
	case 0x2E: return 'C';
	case 0x3F: return 'V';
	case 0x30: return 'B';
	case 0x31: return 'N';
	case 0x32: return 'M';
	case 0x33: return ',';
	case 0x34: return '.';
	case 0x35: return '/';
	case 0x37: return '*';
	case 0x39: return ' ';
	default: return 0;
	}
}

void	keyboard_call(_registers r){

	u8 scan_code;
	u8 letter;

	scan_code = Pbyte_in(0x60); // PIT leave the scancode at the port 0x60
	letter = get_char(scan_code);
	if (letter){
		buf.buffer[buf.index] = letter;
		buf.index += 1;
		put_char(letter, 1, 1);
	}
}

_buffer *get_buffer(){
	return (&buf);
}

u8	get_buffer_index(){
	return (buf.index);
}

void	clear_keyboard_buffer(){
	t_byteSet(buf.buffer, 0, buf.index);
	buf.index = 0;
	nl_flag = 0;
}

u8 back_space(){
	if (buf.index != 0){
		display_back_space();
		buf.index--;
	}
	buf.buffer[buf.index] = 0;
	return (0);
}


u8	keyboad_new_line(){
	return (nl_flag);
}

void	init_keyboard(){
	set_handler(33, (u32)keyboard_call);
	clear_keyboard_buffer();
}
