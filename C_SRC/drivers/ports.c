#include "../INCLUDE/system.h"


// asm ( assembler template : output operands : input operands);

// Read a Byte from Port_number
u8 Pbyte_in(u16 port_number){
	u8 result;
	/*
		reading to the port in assembly will be:
			mov dx, 0x03C4    ; set DX to the port number
			in al, dx        ; reading from port 0x03C4 and store in al
		so we do the same here except GNU uses AT&T syntax, which make the order of the operands reversed.
		also we are saying to store the value of al into result. and the the port number into dx
	*/
	__asm__("in %%dx, %%al" : "=a"(result) : "d"(port_number));
	return result ;
}

// Read a Word from Port_number
u16 Pword_in(u16 port_number){
	u16 result;
	__asm__("in %%dx, %%ax" : "=a"(result) : "d"(port_number));
	return result ;
}
// Write a Byte to Port_number
void	Pbyte_out(u16 port_number, u8 value){
	/*
		writing to a port in assembly will be:
			mov dx, 0x03C4    ; set DX to the port number
			mov al, 0x45    ; set al with the value to print
			out dx, al        ; write to port 0x03C4 the value 0x45
	*/
	__asm__("out %%al, %%dx" : : "a"(value), "d"(port_number));
}

// Write a Word to Port_number
void	Pword_out(u16 port_number, u16 value){
	__asm__("out %%ax, %%dx" : : "a"(value), "d"(port_number));
}