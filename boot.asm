[org 0x7c00]
kernel_start equ 0x9000

xor ax, ax
mov es, ax
mov ds, ax

mov bp, 0x8000	; setting the stack to 0x8000
mov sp, bp

mov [DiskId] , dl; storing the disk id we've got the boot sector from

; Reading data
call SectorsLoading	; call the loading sectors routine
mov ah, 0x0 ; text mode (it will clear the screen).
mov al, 0x3
int 0x10

; switching to 32 bit protected mode:
	; disable inturrupts bye bye BIOS
	cli 
	; loading the GDT
	lgdt [GDT_Descriptor]
	; swich to 32 bit mode
	mov eax, cr0
	or  eax, 1
	mov cr0, eax
	; doing a far jump to start in 32 bit mode:
	jmp CODE_SEG:StartingProtectedMode

; starting on 32 bit mode:
[bits 32]
StartingProtectedMode:
	mov ax , DATA_SEG ; Now in PM , our old segments are meaningless ,
	mov ds , ax ; so we point our segment registers to the
	mov ss , ax ; data selector we defined in our GDT
	mov es , ax
	mov fs , ax
	mov gs , ax

	mov ebp , 0x90000 ; Update our stack position so it is right at the top of the free space.
	mov esp , ebp

	mov ah, 0x0f
	mov al, 'A'
	mov [0xb8000], ax

inf:
	jmp inf
DiskId:
	db 0
num_sector:
	db 20	; how many sectors to read

 %include "BIOS_UTILS/print.asm"
 %include "BIOS_UTILS/SectorsLoad.asm"
 %include "GDT.asm"

;; our magic number and padding
times 510 - ($ - $$) db 0
dw 0xaa55