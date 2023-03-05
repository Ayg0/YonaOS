#include "../INCLUDE/system.h"
#include "../INCLUDE/display.h"
#include "../INCLUDE/keyboard.h"
#include "../INCLUDE/typedefs.h"


u32 t_atoi(u8 *str){
	u16	i;
	u32	res;

	res = i = 0;
	while (str[i] >= '0' && str[i] <= '9'){
			res *= 10;
			res += str[i] - 48;
			i++;
		}
	return (res);
}