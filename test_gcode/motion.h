
#ifndef _MOTION_H_
#define _MOTION_H_

typedef enum Position
{
	X,
	Y,
	Z
}Pos;

typedef struct _motionStructure
{
	int x,y,z;
	int stepUnit; 

}Motion;

int getPosition(Pos p);
void setPosition(Pos p, int val);
void setPositionAdd(Pos p, int val);

inline int getStepUnit(void);
void setStepUnit(int val);


void moveXstep(int dir);
void moveYstep(int dir);
void moveXYstep(int dirx,int diry);
void moveToXY(float x,float y);
void moveZdown(float z);
void moveZup(float z);



#endif
