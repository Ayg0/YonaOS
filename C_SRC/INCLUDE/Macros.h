#ifndef	MARCOS_H
# define MARCOS_H

//SCREEN RELATED
	# define VIDEOMEMORY 0xb8000
	# define MAX_COL 80
	# define MAX_COL_2 160
	# define MAX_ROW 25
	//colors:

		# define WHITE_ON_BLACK	0x0F
		# define BLACK			0x00
		# define BLUE			0x01
		# define GREEN			0x02
		# define CYAN			0x03
		# define RED			0x04
		# define PURPLE			0x05
		# define BROWN			0x06
		# define GRAY			0x07
		# define DARK_GRAY		0x08
		# define DARK_BLUE		0x09
		# define DARK_GREEN		0x0A
		# define DARK_CYAN		0x0B
		# define DARK_RED		0x0C
		# define DARK_PURPLE	0x0D
		# define YELLOW			0x0E
		# define WHITE			0x0F
	// DEVICE I/O ports
	# define SCREEN_CRTL 0x3D4
	/*
		this is one of the most used indexed registers.
		The index byte is written to the port given, then the data byte
		can be read/written from/to port+1 (0x3D5)
	*/
	# define SCREEN_DATA 0x3D5	
	// FUNCTIONS RELATED

	# define BINARY_FORMAT	'b'
	# define DECIMAL_FORMAT	'd'
	# define HEX_FORMAT		'h'
#endif