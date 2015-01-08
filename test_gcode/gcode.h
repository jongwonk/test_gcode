
#ifndef _GCODE_H_
#define _GCODE_H_


typedef union _DataType
{
	double dVal;
	int iVal;
}ParamValue;

int gcode_parse(char* str);



// in step
int draw_circle(int dx, int dy, int radius, int feedrate); 
int draw_line(int dx, int dy, int feedrate);
int draw_arc(int dx, int dy, int radius,int cw ,int feedrate);

int move_to_point(int dx,int dy, int dz, int feedrate);



#endif
