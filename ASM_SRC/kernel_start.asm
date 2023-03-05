[bits 32]
[extern main]
call main

huh:
	cli
	hlt
	jmp huh