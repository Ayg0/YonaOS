[org 0x7c00]
kernel_start equ 0xa000
VIDEO_MEMORY equ 0xb8000

xor ax, ax
mov es, ax
mov ds, ax

mov bp, 0x8000	; setting the stack to 0x8000
mov sp, bp

mov [DiskId] , dl; storing the disk id we've got the boot sector from

; Reading data
SectorsLoading:
	mov bx, kernel_start	; where to put the data we read from the disk
	mov dl, [DiskId]; read from the same drive we've got the boot sector from
	mov ah, 0x02; read sector BIOS
	mov al, [num_sector]	; number of sectors
	mov ch, 0x00; cylinder 0
	mov dh, 0x00; head 0
	mov cl, 0x02; start from sector 2
	int 0x13
	jc	Reading_error	; jump if carry
	jmp change_vid_mod
Reading_error:
	mov ah, 0x0e
	mov al, 'F'
	int 0x10
	jmp inf

change_vid_mod:
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

	call writ
	call kernel_start

inf:
	jmp inf
DiskId:
	db 0
num_sector:
	db 2	; how many sectors to read

writ:
	pusha
	mov ah, 0xf0
	mov al, 'E'
	mov [0xb8000], ax
	popa
	ret

 %include "GDT.asm"

;; our magic number and padding
times 510 - ($ - $$) db 0
dw 0xaa55