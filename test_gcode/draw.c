
#include "draw.h"
#include "motion.h"

#include "stdio.h"

extern Motion motion;

enum Direction
{
	UP,
	DOWN,
	RIGHT,
	LEFT
};

int getQuadrant(int x1,int y1,int x2,int y2)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	
	if(dx > 0 && dy >= 0)
		return 0;
	else if(dx <= 0 && dy > 0)	
		return 1;
	else if(dx < 0 && dy <= 0)	
		return 2;
	
	return 3;
}

int nextQuadrant(int* q,int ccw)
{
	if(ccw == 0)
	{
		*q -= 1;
		*q &= 0x3;
	}
	else
	{
		*q += 1;
		*q &= 0x3;					
	}
	
	return *q;
}

void getDirection(int quadrant, int ccw, int* dirx, int* diry)
{
	if (dirx != NULL)
	{
		if(quadrant == 0 || quadrant == 1)
		{
			if(ccw == 0) // CW
				*dirx = RIGHT;
			else
				*dirx = LEFT;
		}
		else
		{
			if(ccw == 0) // CW
				*dirx = LEFT;
			else
				*dirx = RIGHT;
		}
	}

	if(diry != NULL)	
	{
		if(quadrant == 0 || quadrant == 3)
		{
			if(ccw == 0) // CW
				*diry = DOWN;
			else
				*diry = UP;
		}
		else	
		{
			if(ccw == 0) // CW
				*diry = UP;
			else
				*diry = DOWN;
		}
	}
}

int reachEndPoint(int q, int x,int y, int x2, int y2, int ccw)
{
	int done = 0;
	
	if(q == 0)
	{
		if(ccw == 0) // CW
		{
			if( x2 <= x && y2 >= y)
				done = 1;			
		}
		else
		{
			if( x2 <= x && y2 <= y)
				done = 1;
		}
	}
	else if(q == 1)
	{
		if(ccw == 0)
		{
			if( x2 <= x && y2 <= y)
				done = 1;			
		}
		else
		{
			if( x2 >= x && y2 <= y)
				done = 1;
		}
	}
	else if(q == 3)
	{
		if(ccw == 0)
		{
			if( x2 >= x && y2 <= y)
				done = 1;			
		}
		else
		{
			if( x2 <= x && y2 >= y)
				done = 1;
		}
	}	
	else
	{
		if(ccw == 0)
		{
			if( x2 >= x && y2 >= y)
				done = 1;			
		}
		else
		{
			if( x2 <= x && y2 <= y)
				done = 1;
		}
	}
	
	return done;
	
}


void gcode_draw_circle2(int x1,int y1,int z1,int r,int unit)
{
    int quadrant;
    int x,y;
    int ex,ey;
    int r2;
    int tmp_x,tmp_y;

    r2 = r*r;
    quadrant = 1;

    moveToXY(x1+r,y1); // move to the start point

    x = r;
    y = 0;

	// motion.x = x1+r;
	// motion.y = y1;
	setPosition(X,x1+r);
	setPosition(Y,y1);

    moveZdown(z1);

    do
    {
        if(quadrant == 1)
        {
            tmp_x = x-unit;
            tmp_y = y+unit;

            ex = abs( tmp_x*tmp_x+y*y-r2);
            ey = abs( x*x+tmp_y*tmp_y-r2);
        }
        else if(quadrant == 2)
        {
            tmp_x = x-unit;
            tmp_y = y-unit;
            ex = abs( tmp_x*tmp_x+y*y-r2);
            ey = abs( x*x+tmp_y*tmp_y-r2);
        }
        else if(quadrant == 3)
        {
            tmp_x = x+unit;
            tmp_y = y-unit;
            ex = abs( tmp_x*tmp_x+y*y-r2);
            ey = abs( x*x+tmp_y*tmp_y-r2);
        }
        else if(quadrant == 4)
        {
            tmp_x = x+unit;
            tmp_y = y+unit;
            ex = abs( tmp_x*tmp_x+y*y-r2);
            ey = abs( x*x+tmp_y*tmp_y-r2);
        }

        if(ex < ey)
        {
            x = tmp_x;
            if(quadrant == 1 || quadrant == 2)
                moveXstep(LEFT);
            else
                moveXstep(RIGHT);
        }
        else
        {
            y = tmp_y;
            if(quadrant == 1 || quadrant == 4)
                moveYstep(UP);
            else
                moveYstep(DOWN);
        }

        if(quadrant == 1)
        {
            if( x <= 0 )
            {
                x = 0;
                y = r;
                quadrant++;
                
            }
        }
        else if(quadrant == 2)
        {
            if( y <= 0)
            {
                x = -r;
                y = 0;
                quadrant++;
            }
        }       
        else if (quadrant == 3)
        {
            if( x >= 0 )
            {
                x = 0;
                y = -r;
                quadrant++;
            }
        }
        else
        {
            if( y >= 0 )
            {
                x = r;
                y = 0;
                quadrant++;
            }
        }

    }
    while(quadrant < 5);

    moveZup(z1);
}

void gcode_draw_circle3(int x1,int y1,int z1,int r,int unit)
{
    int quadrant;
    int x,y;
    int ex,ey,ec;
    int r2;
    int tmp_x,tmp_y;
    int dirx,diry;
	
	
    r2 = r*r;
    quadrant = 1;

    moveToXY(x1+r,y1); // move to the start point

    x = r;
    y = 0;

	//motion.x = x1+r;
	//motion.y = y1;
	setPosition(X,x1+r);
	setPosition(Y,y1);
	
    moveZdown(z1);

    do
    {
        if(quadrant == 1)
        {
            tmp_x = x-unit;
            tmp_y = y+unit;
            ex = abs( tmp_x*tmp_x+y*y-r2);
            ey = abs( x*x+tmp_y*tmp_y-r2);
        }
        else if(quadrant == 2)
        {
            tmp_x = x-unit;
            tmp_y = y-unit;
            ex = abs( tmp_x*tmp_x+y*y-r2);
            ey = abs( x*x+tmp_y*tmp_y-r2);
        }
        else if(quadrant == 3)
        {
            tmp_x = x+unit;
            tmp_y = y-unit;
            ex = abs( tmp_x*tmp_x+y*y-r2);
            ey = abs( x*x+tmp_y*tmp_y-r2);
        }
        else if(quadrant == 4)
        {
            tmp_x = x+unit;
            tmp_y = y+unit;
            ex = abs( tmp_x*tmp_x+y*y-r2);
            ey = abs( x*x+tmp_y*tmp_y-r2);
        }
        
        ec = abs( tmp_x*tmp_x+tmp_y*tmp_y-r2);
            

        if(ex < ey)
        {
			if(ec <= ex)
			{
				x = tmp_x;
				y = tmp_y;
				
				if(quadrant == 1 || quadrant == 2)
					dirx = LEFT;
				else
					dirx = RIGHT;
				
				if(quadrant == 1 || quadrant == 4)
					diry = UP;
				else	
					diry = DOWN;
					
				moveXYstep(dirx,diry);
								
			}
			else
			{
				x = tmp_x;
				if(quadrant == 1 || quadrant == 2)
					moveXstep(LEFT);
				else
					moveXstep(RIGHT);
			}
        }
        else
        {
			if(ec <= ey)
			{
				x = tmp_x;
				y = tmp_y;
				
				if(quadrant == 1 || quadrant == 2)
					dirx = LEFT;
				else
					dirx = RIGHT;
				
				if(quadrant == 1 || quadrant == 4)
					diry = UP;
				else	
					diry = DOWN;
					
				moveXYstep(dirx,diry);

			}
			else
			{
				y = tmp_y;
				if(quadrant == 1 || quadrant == 4)
					moveYstep(UP);
				else
					moveYstep(DOWN);
			}
        }

        if(quadrant == 1)
        {
            if( x <= 0 )
            {
                x = 0;
                y = r;
                quadrant++;
                
            }
        }
        else if(quadrant == 2)
        {
            if( y <= 0)
            {
                x = -r;
                y = 0;
                quadrant++;
            }
        }       
        else if (quadrant == 3)
        {
            if( x >= 0 )
            {
                x = 0;
                y = -r;
                quadrant++;
            }
        }
        else
        {
            if( y >= 0 )
            {
                x = r;
                y = 0;
                quadrant++;
            }
        }

    }
    while(quadrant < 5);

    moveZup(z1);
}


void gcode_draw_line2(int ix1, int iy1, int ix2, int iy2, int iunit)
{
	
	int dx,dy;
	int e;
	int x,y;
	int quadrant;
	int done = 0;
	int mt = 0;
	int iunitx,iunity;
		
	
	dx = 2*(ix2-ix1);
	dy = 2*(iy2-iy1);
	
	if(dx >= 0 && dy >= 0)
	{
		e = dy;
		quadrant = 1;		
		iunitx = (int)iunit;
		iunity = (int)iunit;
	}
	else if(dx < 0 && dy >= 0)
	{
		e = dx;
		quadrant = 2; 		
		iunitx = -iunit;
		iunity =  iunit;
	}
	else if(dx < 0 && dy < 0)
	{
		e = -dx;
		quadrant = 3; 		
		iunitx = -iunit;
		iunity = -iunit;		
	}
	else 
	{
		e = -dy;
		quadrant = 4; 			
		iunitx = iunit;
		iunity = -iunit;		
	}
	
	printf("1:%d %d %d %d\n",quadrant,e,iunitx,iunity);

	setPosition(X,ix1);
	setPosition(Y,iy1);

	x = ix1;
	y = iy1;
	
	moveToXY(ix1,iy1);
	
	do
	{
		mt = 0;		
		
		if(abs(dx) >= abs(dy))
		{
			x += iunitx;
			e += abs(dy);
			
			if(e >= abs(dx))
			{
				mt = 1;
				y += iunity;
				e -= abs(dx);
			}
			
			if(mt)
				moveXYstep((iunitx > 0)?RIGHT:LEFT,(iunity>0)?UP:DOWN);
			else
				moveXstep((iunitx > 0)?RIGHT:LEFT);
		}
		else
		{
			y += iunity;
			e += abs(dx);
		
			if(e >= abs(dy))
			{
				mt = 1;
				x += iunitx;
				e -= abs(dy);
			}
			
			if(mt)
				moveXYstep((iunitx > 0)?RIGHT:LEFT,(iunity>0)?UP:DOWN);
			else
				moveYstep((iunity > 0)?UP:DOWN);			
		}
		
		if( quadrant == 1 && ix2 <= x && iy2 <= y )
				done = 1;
		else if(quadrant == 2 && ix2 >= x && iy2 <= y )
				done = 1;
		else if(quadrant == 3 && ix2 >= x && iy2 >= y )
				done = 1;		
		else if( ix2 <= x && iy2 >= y )
				done = 1;			
		
	}while(!done);
	
}

/*
 function : gcode_draw_arc3
        x1,y1: x,y of center
        xb,yb: x,y of beginning point
        xe,ye: x,y of end point
		...
*/

void gcode_draw_arc3(int x1,int y1,int xb,int yb,int xe,int ye,int r,int unit,int ccw)
{
    int quadrant;
    int x,y;
    int ex,ey,ec;
    int r2;
    int tmp_x,tmp_y;
    int dirx,diry;
	int done;
	int qb,qe; // begin/end quadrant 
	
	done = 0;
	
    r2 = -r*r;

    moveToXY(xb,yb); // move to the start point
	
	qb = getQuadrant(x1,y1,xb,yb);
	qe = getQuadrant(x1,y1,xe,ye);
	
	quadrant = qb;
	
    x = xb;
    y = yb;

	// motion.x = xb;
	// motion.y = yb;
	setPosition(X,xb);
	setPosition(Y,yb);

    do
    {
		if(ccw == 0) // CW
		{
			if(quadrant == 0)
			{
				tmp_x = x+unit;
				tmp_y = y-unit;
			}
			else if(quadrant == 1)
			{
				tmp_x = x+unit;
				tmp_y = y+unit;				
			}
			else if(quadrant == 2)
			{
				tmp_x = x-unit;
				tmp_y = y+unit;
			}
			else if(quadrant == 3)
			{
				tmp_x = x-unit;
				tmp_y = y-unit;
			}
		}
		else
		{
			if(quadrant == 0)
			{
				tmp_x = x-unit;
				tmp_y = y+unit;				
			}
			else if(quadrant == 1)
			{
				tmp_x = x-unit;
				tmp_y = y-unit;
			}
			else if(quadrant == 2)
			{
				tmp_x = x+unit;
				tmp_y = y-unit;
			}
			else if(quadrant == 3)
			{
				tmp_x = x+unit;
				tmp_y = y+unit;
			}
		}
		
		ex = abs( tmp_x*tmp_x+y*y+r2);
		ey = abs( x*x+tmp_y*tmp_y+r2);
        ec = abs( tmp_x*tmp_x+tmp_y*tmp_y+r2);

        if(ex < ey)
        {
			if(ec <= ex)
			{
				x = tmp_x;
				y = tmp_y;
				getDirection(quadrant,ccw,&dirx,&diry);
				moveXYstep(dirx,diry);
			}
			else
			{
				x = tmp_x;
				getDirection(quadrant,ccw,&dirx,NULL);
				moveXstep(dirx);	
			}
        }
        else
        {
			if(ec <= ey)
			{
				x = tmp_x;
				y = tmp_y;
				getDirection(quadrant,ccw,&dirx,&diry);
				moveXYstep(dirx,diry);
			}
			else
			{
				y = tmp_y;
				getDirection(quadrant,ccw,NULL,&diry);
				moveYstep(diry);
			}
        }

        if(quadrant == 0)
        {
			if(qe == 0)
				done = reachEndPoint(qe, x,y, xe,ye, ccw);
			
			if(ccw == 0 && y <= 0)
				nextQuadrant(&quadrant,ccw);
			else if(ccw != 0 && x <= 0)
				nextQuadrant(&quadrant,ccw);
        }
        else if(quadrant == 1)
        {
			if(qe == 1)
				done = reachEndPoint(qe, x,y, xe,ye, ccw);
				
			if(ccw == 0 && x >= 0)
				nextQuadrant(&quadrant,ccw);
			else if(ccw != 0 && y <= 0)
				nextQuadrant(&quadrant,ccw);
        }       
        else if (quadrant == 2)
        {
			if(qe == 2)
				done = reachEndPoint(qe, x,y, xe,ye, ccw);
			
			if(ccw == 0 && y >= 0)
				nextQuadrant(&quadrant,ccw);
			else if( ccw != 0 && x >= 0)
				nextQuadrant(&quadrant,ccw);
        }
        else
        {
			if(qe == 3)
				done = reachEndPoint(qe, x,y, xe,ye, ccw);
			
			if(ccw == 0 && x <= 0 )
				nextQuadrant(&quadrant,ccw);
			else if(ccw != 0 && y >= 0)
				nextQuadrant(&quadrant,ccw);
        }
    }
    while(!done);
}
