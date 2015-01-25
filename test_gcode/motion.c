
#include "motion.h"
#include "stdio.h"
#include "debug.h"

static Motion motion = {0,0,0,100};

int getPosition(Pos p)
{
	int ret = 0;

	if(p == X)
		ret = motion.x;
	else if(p == Y)
		ret = motion.y;
	else if(p == Z)
		ret = motion.z;

	return ret;
}
void setPosition(Pos p, int val)
{
	if(p == X)
		motion.x = val;
	else if(p == Y)
		motion.y = val;
	else if(p == Z)
		motion.z = val;
}

void setPositionAdd(Pos p, int val)
{
	if(p == X)
		motion.x += val;
	else if(p == Y)
		motion.y += val;
	else if(p == Z)
		motion.z += val;
}

void setPositionSub(Pos p, int val)
{
	if(p == X)
		motion.x -= val;
	else if(p == Y)
		motion.y -= val;
	else if(p == Z)
		motion.z -= val;
}


inline int getStepUnit(void)
{
	return motion.stepUnit;

}
void setStepUnit(int val)
{
	motion.stepUnit = val;
}

void moveXstep(int dir)
{
	
    if(dir)
    {
    	setPositionAdd(X,getStepUnit());
		DebugPrintf(NULL,"%d %d\n",getPosition(X),getPosition(Y));
    }
    else
    {
		setPositionSub(X,getStepUnit());
        DebugPrintf(NULL,"%d %d\n",getPosition(X),getPosition(Y));
    }
}

void moveYstep(int dir)
{
    if(dir)
    {
		setPositionAdd(Y,getStepUnit());
        DebugPrintf(NULL,"%d %d\n",getPosition(X),getPosition(Y));
    }
    else
    {
		setPositionAdd(Y,getStepUnit());
        DebugPrintf(NULL,"%d %d\n",getPosition(X),getPosition(Y));
    }
}

void moveXYstep(int dirx,int diry)
{
    if(dirx)
    {
		setPositionAdd(X,getStepUnit());
		printf("1:%d\n",getPosition(X));
    }
    else
    {
		setPositionSub(X,getStepUnit());
		printf("2:%d\n",getPosition(X));
    }
    	
    if(diry)
    {
		setPositionAdd(Y,getStepUnit());
    }
    else
    {
		setPositionSub(Y,getStepUnit());
    }
     
	DebugPrintf(NULL,"%d %d\n",getPosition(X),getPosition(Y));
  
}



void moveToXY(float x,float y)
{
    printf("move to (%d,%d)\n",x,y);
    DebugPrintf(NULL,"%d %d\n",x,y);
}

void moveZdown(float z)
{
    printf("Z: down(%d)\n",z);
}

void moveZup(float z)
{
    printf("Z: up(%d)\n",z);

}
