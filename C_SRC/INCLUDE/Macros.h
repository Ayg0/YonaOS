#ifndef	MARCOS_H
# define MARCOS_H

//SCREEN RELATED
	# define VIDEOMEMORY 0xb8000
	# define MAX_ROW 80
	# define MAX_COL 25
	//colors:
		// black on white
		# define WB	0x0f
	// DEVICE I/O ports
	# define SCREEN_CRTL 0x3D4
	/*
		this is one of the most used indexed registers.
		The index byte is written to the port given, then the data byte
		can be read/written from/to port+1 (0x3D5)
	*/
	# define SCREEN_DATA 0x3D5



	
#endif