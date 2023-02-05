NAME = boot.bin

all:
	nasm -f bin boot.asm -o $(NAME) && bash run.sh

fclean:
	rm -rf $(NAME)