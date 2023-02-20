NAME = BUILD/Yona.bin	# final output
CC = i386-elf-gcc # compiler
CFLAGS = -ffreestanding -fno-builtin -nostdlib -nodefaultlibs # flags to compile the C code
LD = i386-elf-ld	# linker
LFLAGS = -Ttext 0x1000 --oformat binary	# link flags 
OBJDIR = OBJ
SRCDIR = C_SRC

# C Code
C_SRC := $(shell find $(SRCDIR) -type f -name '*.c')
# C Objects
C_OBJ := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(C_SRC))

all: $(C_OBJ)
	nasm -f bin ASM_SRC/empty.asm -o $(OBJDIR)/ASM/empty.o
	nasm ASM_SRC/kernel_start.asm -f elf -o $(OBJDIR)/ASM/kernel_start.o
	$(LD) $(LFLAGS) -o $(OBJDIR)/ASM/kernel.bin  $(OBJDIR)/ASM/kernel_start.o $(C_OBJ)
	nasm ASM_SRC/boot.asm -f bin -o $(OBJDIR)/ASM/boot.bin
	cat $(OBJDIR)/ASM/boot.bin $(OBJDIR)/ASM/kernel.bin $(OBJDIR)/ASM/empty.o > $(NAME)
	qemu-system-i386 $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(dir $(C_OBJ))

fclean:
	rm -rf $(NAME) $(OBJDIR)/ASM/boot.bin $(OBJDIR)/ASM/kernel_start.o \
	$(OBJDIR)/ASM/kernel.bin $(C_OBJ) $(OBJDIR)/ASM/empty.o
re:
	make fclean && make
.PHONY: OBJ fclean all 