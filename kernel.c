extern int	main();

int	main() {
    char* video_memory = (char*) 0xb8002;
    *video_memory = 'A';
    *(video_memory + 1) = 0xf0;
	return (5);
}