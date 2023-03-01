[GLOBAL gdt_load]

DATA_S equ 0x10 ; where our data segment is located
CODE_S equ 0x08 ; where our code segment is located

gdt_load:
	mov	eax, [esp + 4]
	lgdt [eax]
	
	mov ax, DATA_S
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp CODE_S:__ret

__ret:
	ret