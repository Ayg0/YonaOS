#include "../INCLUDE/system.h"

void	t_memcpy(void *dst, void *src, u32 nbytes){
	for (u32 i = 0; i < nbytes; i++)
		((u8 *)dst)[i] = ((u8 *)src)[i];
}

void	t_byteSet(void *addr, u8 val, u32 nbytes){
	for (u32 i = 0; i < nbytes; i++)
		((u8 *)addr)[i] = val;
}
// s
void	t_WordSet(void *addr, u16 val, u32 nWords){
	for (u32 i = 0; i < nWords; i++)
		((u16 *)addr)[i] = val;
}