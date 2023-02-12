NAME = boot.bin

all:
	
	nasm boot.asm -o $(NAME) && bash run.sh

fclean:
	rm -rf $(NAME)