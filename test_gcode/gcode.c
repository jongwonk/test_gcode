

#include "gcode.h"
#include "stdio.h"
#include "string.h"

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
		return 0;
	}

	pv1 = 0;
	pv2 = 0;
	isDecimal = 0;
	dcnt = 0;

	while(*ptr != ' ' && *ptr != '\t' && ptr != NULL && *ptr != '\0')
	{
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

	return 1;
}

int gcode_parse(char* str)
{
	float param;
	int len;
	int result;
	float px,py,pz;
	int pf;
	int   rx,ry,rz,rf;

	len = strlen(str);
	char* ptr;

	printf("%s,len = %d\n",str,len);

	px = 0.0f;
	py = 0.0f;
	pz = 0.0f;
	pf = 0;


	result = gcode_getParamPtr(str,'G',&param);
	printf("G:%d\n",(int)param);
	if(result)
	{
		switch((int)param)
		{
			case 0:
				rx = gcode_getParamPtr(str,'X',&px);
				ry = gcode_getParamPtr(str,'Y',&py);
				rz = gcode_getParamPtr(str,'Z',&pz);
				printf("X:%.3f,Y:%.3fd,Z:%.3f\n",px,py,pz);
			break;
			case 1:
				rx = gcode_getParamPtr(str,'X',&px);
				ry = gcode_getParamPtr(str,'Y',&py);
				rz = gcode_getParamPtr(str,'Z',&pz);
				rf = gcode_getParamPtr(str,'F',&param);
				pf = (int)param;
				if(rx)printf("X:%f\n",px);
				if(ry)printf("Y:%f\n",py);
				if(rz)printf("Z:%f\n",pz);
				if(rf)printf("F:%d\n",(int)pf);
			break;
			case 2:

			break;
			case 3:

			break;

			case 20:

			break;
			case 21:

			break;
			case 28:
			break;
			case 90:
			case 91:
			case 92:
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


		}
	}

	result = gcode_getParamPtr(str,'M',&param);
	while(ptr != NULL)
	{
		switch(*ptr)
		{
			case '0':

			break;


		}
	}

	return 0;
}

