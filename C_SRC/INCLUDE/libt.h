#ifndef	LIBT_H
# define LIBT_H
# include "system.h"

u32		t_atoi(u8 *str);
void	prompt(s8 *prompt);
u8		t_strcmp(u8 *s1, u8 *s2);
void	t_byteSet(void *addr, u8 val, u32 nbytes);
void	t_WordSet(void *addr, u16 val, u32 nWords);
void	t_memcpy(void *dst, void *src, u32 nbytes);
#endif