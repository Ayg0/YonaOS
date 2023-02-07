print_str:
	pusha			; store the value of the registers into the stack
	mov ah, 0x0e
lp:
	cmp byte [bx], 0
	jz	return		; jmp if equal a zero
	mov al, [bx]
	int	0x10
	inc bx			; increment the address in bx
	jmp lp			; continue the loop

printHex:
	mov bx, hex		; storing the address of hex in bx to print
	call print_str	; print "0x"
	start_hex:
		pusha
		xor dx, dx	; initialize dx to 0
		cmp ax, 16	; compare the valude in ax with 16
		jb verify_value	; jump to verify_value if the value of ax is below 16
		mov bx, 16
		div bx			; devide ax by bx and store the result in ax and the reminder in dx
		call start_hex	; call start hex with the new value of ax
		mov ax, dx		; mov the reminder into ax
		verify_value:
			add ax, 48	; add 48 to ax to convert to ascii number
			cmp ax, 57	; check if ax was below 9 it's a number 
			jle print_value	; if it was we print it
			add ax, 7	; else we add 7 to convert to the right letter
		print_value:
			mov ah, 0x0e
			int 0x10
			jmp return

return:
	popa	; restoring the values of the registers from the stack
	ret

hex:
	db "0x", 0