mov cx, 5
mov bx, 10

looop:
	cmp cx, 20
	je  end
	cmp cx, bx
	jg  yes
	jmp no

yes:
	mov al, 'Y'
	jmp	print
no:
	mov al, 'N'	
print:
	mov ah, 0x0e
	int 0x10
	mov al, 10
	int 0x10
	inc cx
	jmp looop
end:
	jmp end

times 510 -( $ - $$ ) db 0
dw 0xaa55