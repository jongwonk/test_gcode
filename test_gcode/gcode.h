
#ifndef _GCODE_H_
#define _GCODE_H_

typedef struct
{
	float x,y,z; // position
	float i,j,k; // position
	float hx,hy,hz; // home position
	int ustep; // micro stepping
	int fr;	// feedrate	
	int dfr; // default feed rate
	unsigned int mode:1; // 0:abs, 1:rel
	unsigned int unit:1; // 0:inch, 1:mm
	int offsetx;
	int offsety;
	int offsetz;



}SysInfo;

int gcode_parse(char* str);
void gcode_delay(int sec);
void gcode_enable(void);
void gcode_disable(void);
void gcode_report(void);
void gcode_home(int x,int y,int z);
void gcode_moveto(float x, float y, float z);
void gcode_arc_cw(void);
void gcode_arc_ccw(void);

// in step
// possibly for device driver
int draw_arc_cw();
int draw_arc_ccw();
int draw_circle(int dx, int dy, int radius, int feedrate); 
int draw_line(int dx, int dy, int feedrate);
int draw_arc(int dx, int dy, int radius,int cw ,int feedrate);
int move_to_point(int dx,int dy, int dz, int feedrate);



#endif
