#include "../INCLUDE/general.h"

extern int	main();

//unsigned char port_byte_in ( unsigned short port ) {
//// A handy C wrapper function that reads a byte from the specified port
//// "=a" ( result ) means : put AL register in variable RESULT when finished
//// "d" ( port ) means : load EDX with port
//unsigned char result ;
//__asm__ (" in %% dx , %% al " : "=a " ( result ) : "d " ( port ));
//return result ;
//}

int	main() {
	Pbyte_out(SCREEN_CRTL, 14);
	Pbyte_out(SCREEN_DATA, 5);
	Pbyte_out(SCREEN_CRTL, 15);
	//char *s = "Imane l3iyan";
	//print_str(s, WB, 0, 0);
	return (5);
}