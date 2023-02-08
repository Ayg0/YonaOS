[bits 16]

 mov bp, 0x8000	; setting the stack to 0x8000
 mov sp, bp

;call printHex

mov ax, 0x7c0
mov ds, ax

mov ax, [num]
call printHex
 
inf:
	jmp inf

num:
	dw 0x7c

 %include "print.asm"

;; our magic number and padding
times 510 - ($ - $$) db 0	
dw 0xaa55