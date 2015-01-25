
#ifdef _DRAW_H_
#define DRAW_H_


void gcode_draw_circle2(float x1,float y1,float z1,float r,float unit,float tolerance);
void gcode_draw_circle3(float x1,float y1,float z1,float r,float unit,float tolerance);

void gcode_draw_line2(float x1, float y1, float x2, float y2, float unit, float tol);

void gcode_draw_arc3(int x1,int y1,int xb,int yb,int xe,int ye,int r,int unit,int ccw);

#endif
