; define the GDT
_GDT:
	; the GDT except a null/The invalid desciptor declared at the begining of the GDT.
	; The Null Descriptor is an 8 byte value of Zeros.
	null_descriptor:
		dd 0 ; define double word (4 byte)
		dd 0
	; defining the code descriptor:
	CODE_Descriptor:
		; define the first 16 bit of the limit
		dw 0xffff
		; define the first 24 bits of the base
		dw 0 ; 16 bits
		db 0 ; 8 bits
		; we need to define the access bytes:
		db 10011010b
		; explanation:
		 ; - Present (1 bit): set it to 1 to indecate that the segment is used.
		 ; - Privilege(2 bit value from 0 to 3): defines the segment privilege, we will put it to 0 as it's the highest privilege ("ring").
		 ; - Type (1 bit): set it to 1 if the segment is the DATA or the Code segment.
		 ; - Code flag: This flag change the meaning of the 2 flags after it depending if weither we set it to 1 for the code segment or 0 for the Data segment.
		 ; - Conforming: define if we can execute the code from lower privilege segments, we set to 0 for no.
		 ; - Readable: define if we can read it or just execute this segment.
		 ; - Accessed: we set it to 0, this is ophten used for debuggin and virtual memory techniques, since the CPU sets the bit when it accesses the segment.
		; then we define the other flags (4 bits) + last 4 bits of the limit:
		db 11001111b
		; explanation:
		 ; - Granularity: when set it to 1 it multiplys the limit by 0x1000, which is a good thing so we will set it to one to get the full 4 GB of RAM.
		 ; - Mode bit: set it to 1 to inform that it's 32 bit and not 64 bit.
		 ; - ONLY_FOR_64_BIT (2 bits): only used in 64 bit so we will set it to 00.
		 ; last 4 bits for the limit so we can have the maximum amount posibble for a 16 bit value.
		; now we define the last 8 bits of the base:
		db 0
	DATA_Descriptor:
		; the data descriptor will be similar except the 3 bit from the Code flag:
		dw 0xffff
		dw 0
		db 0
		db 10010010b
		; the change will accure because we changed the flag to indecate that this is the data segment.
		; - Code Flag: set to 0 because it's the data segment.
		; - Direction Flag: define the direction of memory growing downward (1), and upword (0), our base address starts from 0, so we need to set this flag to 0.
		; - Writable: we set it to 1 so we can write to the segment.
		db 11001111b
		db 0
	_GDT_END: ; end of our GDT
	GDT_Descriptor:
	dw _GDT_END - _GDT - 1	; size of the GDT
	dd _GDT					; start of the GDT
	CODE_SEG equ CODE_Descriptor - _GDT	; setting the constants of the data and code segment
	DATA_SEG equ DATA_Descriptor - _GDT
