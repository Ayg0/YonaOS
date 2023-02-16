NAME = Yona.bin

all:
	i386-elf-gcc -ffreestanding -c kernel.c -o kernel.o
	nasm -f bin empty.asm
	nasm kernel_start.asm -f elf -o kernel_start.o
	i386-elf-ld -o kernel.bin -Ttext 0x1000 kernel_start.o kernel.o --oformat binary
	nasm boot.asm -f bin -o boot.bin
	cat boot.bin kernel.bin empty > $(NAME)
	qemu-system-i386 -fda $(NAME)

fclean:
	rm -rf $(NAME) boot.bin kernel_start.o kernel.o empty kernel.bin