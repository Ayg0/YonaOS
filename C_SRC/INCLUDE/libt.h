#ifndef	LIBT_H
# define LIBT_H
# include "system.h"

void	t_memcpy(void *dst, void *src, u32 nbytes);
void	t_WordSet(void *addr, u16 val, u32 nWords);
void	t_byteSet(void *addr, u8 val, u32 nbytes);
#endif