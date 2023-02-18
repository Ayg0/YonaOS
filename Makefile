NAME = Yona.bin	# final output
CC = i386-elf-gcc # compiler
CFLAGS = -ffreestanding -fno-builtin -nostdlib -nodefaultlibs # flags to compile the C code
LD = i386-elf-ld	# linker
LFLAGS = -Ttext 0x1000 --oformat binary	# link flags 

# C Code
KERNEL_SRC = C_SRC/KERNEL/kernel.c C_SRC/KERNEL/print_utils.c
DRIVERS_SRC = C_SRC/drivers/ports.c C_SRC/drivers/screen.c
C_SRC = $(KERNEL_SRC) $(DRIVERS_SRC)
# C Objects
C_OBJ = $(C_SRC:.c=.o)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@


all: $(C_OBJ)
	nasm -f bin ASM_SRC/empty.asm
	nasm ASM_SRC/kernel_start.asm -f elf -o kernel_start.o
	$(LD) $(LFLAGS) -o kernel.bin  kernel_start.o $(C_OBJ)
	nasm ASM_SRC/boot.asm -f bin -o boot.bin
	cat boot.bin kernel.bin ASM_SRC/empty > $(NAME)
	qemu-system-i386 $(NAME)

fclean:
	rm -rf $(NAME) boot.bin kernel_start.o kernel.o ASM_SRC/empty kernel.bin $(C_OBJ)