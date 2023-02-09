SectorsLoading:
	pusha
	mov ah, 0x02; read sector BIOS
	mov al, [num_sector]	; number of sectors
	mov ch, 0x00; cylinder 0
	mov dh, 0x00; head 0
	mov cl, 0x02; start from sector 2
	int 0x13
	jc	Reading_error	; jump if carry
	cmp al, [num_sector]
	jne Reading_error	; jump if we didn't read all sectors
	popa
	ret
	
Reading_error:
	mov bx, [error_read]
	call print_str
	popa
	ret

error_read:
	db "Error... Loading sectors", 0