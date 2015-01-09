

#include "gcode.h"
#include "stdio.h"
#include "string.h"

SysInfo sInfo;

#define NOVAL 2
#define FAIL 0
#define SUCCESS 1

int power10(int m)
{
	int result = 1;

	while(m--)
	{
		result *= 10;
	}
}

int gcode_getParamPtr(char* str,char ch,float* ret)
{
	int pv1,pv2;
	int dcnt;
	int isDecimal;
	int noval = 0;
	char* ptr = str;

	while(ptr != NULL && *ptr != '\0')
	{
		if(*ptr++ == ch)
		{
			break;
		}
	}

	if(*ptr == '\0')
	{
		*ret = 0.0f;
		return FAIL;
	}

	pv1 = 0;
	pv2 = 0;
	isDecimal = 0;
	dcnt = 0;

	if(*ptr == ' ' || *ptr == '\t')
	{
		*ret = 0.0f;
		return SUCCESS || NOVAL;
	}

	while(*ptr != ' ' && *ptr != '\t' && ptr != NULL && *ptr != '\0')
	{
		if(*ptr =='-')
		{
			pv1 = -pv1;
			ptr++;
			continue;
		}
		if(*ptr=='.')
		{
			isDecimal = 1;
			ptr++;
			continue;
		}

		if(!isDecimal)
		{
			pv1 = pv1*10 + (*ptr-'0');
		}
		else
		{	
			dcnt++;
			pv2 = pv2*10 + (*ptr-'0');
		}

		ptr++;

	}

	if(isDecimal)
		*ret = (float)pv1 + (float)pv2/(float)power10(dcnt);
	else
		*ret = (float)pv1;

	return SUCCESS;
}

int gcode_parse(char* str)
{
	float param;
	int len;
	int result;
	float px,py,pz,pi,pj,pk,pr;
	int pf,pp;
	int rx,ry,rz,rf,ri,rj,rk,rr;
	int rp;

	len = strlen(str);
	char* ptr;

	printf("%s,len = %d\n",str,len);

	px = 0.0f;
	py = 0.0f;
	pz = 0.0f;
	pf = 0;
	pp = 0;


	result = gcode_getParamPtr(str,'G',&param);
	if(result)
	{
		switch((int)param)
		{
			case 0:
				rx = gcode_getParamPtr(str,'X',&px); if(!rx)px = 0.0f;
				ry = gcode_getParamPtr(str,'Y',&py); if(!ry)py = 0.0f;
				rz = gcode_getParamPtr(str,'Z',&pz); if(!rz)pz = 0.0f;
				printf("X:%.3f,Y:%.3fd,Z:%.3f\n",px,py,pz);


			break;
			case 1:
				rx = gcode_getParamPtr(str,'X',&px); if(!rx)px = 0.0f;
				ry = gcode_getParamPtr(str,'Y',&py); if(!ry)py = 0.0f;
				rz = gcode_getParamPtr(str,'Z',&pz); if(!rz)pz = 0.0f;
				rf = gcode_getParamPtr(str,'F',&param);  
				if(rf)
					pf = (int)param;
				else
					pf = sInfo.dfr;					

				printf("X:%.3f,Y:%.3f,Z:%.3f,F:%d\n",px,py,pz,(int)pf);
			break;
			case 2:
			case 3:
				rx = gcode_getParamPtr(str,'X',&px); if(!rx)px = 0.0f;
				ry = gcode_getParamPtr(str,'Y',&py); if(!ry)py = 0.0f;
				ri = gcode_getParamPtr(str,'I',&px); if(!ri)pi = 0.0f;
				rj = gcode_getParamPtr(str,'J',&py); if(!ri)pj = 0.0f;
				rk = gcode_getParamPtr(str,'K',&pk); if(!rk)pi = 0.0f;
				rr = gcode_getParamPtr(str,'R',&pr); if(!rr)pj = 0.0f;

				if((int)param == 2)
					gcode_arc_cw();
				else
					gcode_arc_ccw();
			break;
			case 4:
				rp = gcode_getParamPtr(str,'P',&px);
				if(!rp)
					pp = 1;
				else
					pp = (int)px;
				gcode_delay(pp);
			break;
			case 20:
				sInfo.unit = 0;
			break;
			case 21:
				sInfo.unit = 1;
			break;
			case 28:
				rx = gcode_getParamPtr(str,'X',&px);
				ry = gcode_getParamPtr(str,'Y',&py);
				rz = gcode_getParamPtr(str,'Z',&pz);

				gcode_home(rx,ry,rz);

			break;
			case 90:
				sInfo.mode = 0; // absolute mode
			case 91:
				sInfo.mode = 1; // relative mode
			case 92:
				rx = gcode_getParamPtr(str,'X',&px); if(rx)sInfo.offsetx = px;
				ry = gcode_getParamPtr(str,'Y',&py); if(ry)sInfo.offsety = py;
				rz = gcode_getParamPtr(str,'Z',&pz); if(rz)sInfo.offsetz = pz;
			case 93:
			case 94:
			case 95:
			case 96:
			case 97:
			break;
			case 178:
			break;
			case 183:
			break;
			default:
			break;

		}
	}

	result = gcode_getParamPtr(str,'M',&param);
	if(result)
	{
		switch((int)param)
		{
			case 17:
				gcode_enable();
			break;
			case 18:
				gcode_disable();
			break;
			case 114:
				gcode_report();
			break;
			default:
			break;

		}
	}

	return 0;
}

void gcode_enable(void)
{

}
void gcode_disable(void)
{

}

void gcode_delay(int sec)
{



}

void gcode_report(void)
{

}

void gcode_home(int x,int y, int z)
{

	if(x == 0 && y == 0 && z == 0)
	{
		gcode_moveto(0,0,sInfo.hz);
		gcode_moveto(sInfo.hx,sInfo.hy,sInfo.hz);
	}
	else
	{
		if(z) // z
			gcode_moveto(sInfo.x,sInfo.y,sInfo.hz);
		
		if(x == 0 && y != 0) // y
		{
			gcode_moveto(sInfo.x,sInfo.hy,sInfo.z);
		}
		else if(x != 0 && y == 0)
		{
			gcode_moveto(sInfo.hx,sInfo.y,sInfo.z);
		}
		else if(x != 0 && y != 0)
		{
			gcode_moveto(sInfo.hx,sInfo.hy,sInfo.z);
		}
	}

}

void gcode_moveto(float x, float y, float z)
{


}

void gcode_arc_cw(void)
{


}

void gcode_arc_ccw(void)
{


}
		
