

#include "gcode.h"

#include "file.h"
#include "stdio.h"

int gcode_parse(char* filename)
{
	char buffer[256];

	FILE file = fopen(filename,"r");

	if(file != NULL)
	{
		
		fgets(buffer,256,file);


	}



	return 0;
}

