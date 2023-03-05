#include "../INCLUDE/system.h"
#include "../INCLUDE/display.h"
#include "../INCLUDE/keyboard.h"
#include "../INCLUDE/typedefs.h"

void	prompt(s8 *prompt){
	put_str(prompt);
	while (!keyboard_new_line());
}
