[bits 16]


mov bp, 0x8000	; setting the stack to 0x8000
mov sp, bp

mov ax, 0x7c0
mov ds, ax	; setting the data segment

mov [DiskId] , dl; storing the disk id we've got the boot sector from

; Reading data
mov ax, 0
mov es, ax
mov bx, 0x9000 ; where to put the date we read from the disk
mov dl, [DiskId]; read from the same drive we've got the boot sector from
call SectorsLoading	; call the loading sectors routine
mov ax, [es:0x9000]	; get what's inside address 0x9000 (should be 0xFAFA)
call printHex       ; print ax
mov ax, [es:0x9000 + 512] ; get what's inside the first word on the 3rd sector (should be 0xAAAA)
call printHex
inf:
	jmp inf
DiskId:
	db 0
num_sector:
	db 2	; how many sectors to read

 %include "print.asm"
 %include "SectorsLoad.asm"

;; our magic number and padding
times 510 - ($ - $$) db 0	
dw 0xaa55
times 256 dw 0xFAFA	; fill the 2nd sector with 0xFAFA
times 256 dw 0xAAAA ; fill the 3rd sector with 0xAAAA