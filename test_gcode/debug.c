
#include "debug.h"
#include "genericDefine.h"
#include "stdio.h"
#include "stdint.h"
#include "stdarg.h"

DebugDevice* debug_tx_init(int type,char* dev)
{

	return NULL;
}

void debug_tx_message(DebugDevice* dd,DBG_LEVEL level,char* msg)
{

}

void enableDebug(DebugDevice* dd)
{


}

void disableDebug(DebugDevice* dd)
{


}

Boolean IsDebugDeviceEnable(DebugDevice* dd)
{

	return True;

}

void DebugString(DebugDevice* dd, char* s ) {


}


void DebugPrintf(DebugDevice* dd,const char *fmt, ...) {
	char sTmp[64];	// String build area.  String lives on the stack!
	uint8_t pos=0;
	char *bp = (char *)fmt;
    va_list ap;
    char c;
    char *p;
    int i;

    va_start(ap, fmt);

    while ((c = *bp++)) {
        if (c != '%') {
            sTmp[pos++] = c;
            continue;
        }

        switch ((c = *bp++)) {
			// d - decimal value
			case 'd':
				Num2String( sTmp, &pos, va_arg(ap, uint32_t), 10);
				break;

			// %x - value in hex
			case 'x':
//				sTmp[pos++] = '0';
//				sTmp[pos++] = 'x';
				Num2String( sTmp, &pos, va_arg(ap, uint32_t), 16);
				break;

			// %b - binary
			case 'b':
//				sTmp[pos++] = '0';
//				sTmp[pos++] = 'b';
				Num2String( sTmp, &pos, va_arg(ap, uint32_t), 2);
				break;

			// %c - character
			case 'c':
				sTmp[pos++] = va_arg(ap, int);
				break;

			// %i - integer
			case 'i':
				i = va_arg(ap, int32_t);
				if(i < 0){
					sTmp[pos++] = '-';
					Num2String( sTmp, &pos, (~i)+1, 10);
				} else {
					Num2String( sTmp, &pos, i, 10);
				}
				break;

			// %s - string
			case 's':
				p = va_arg(ap, char *);
				do {
					sTmp[pos++] = *p++;
				} while (*p);
				break;
			case 'p':
			    i = va_arg(ap, int32_t);
			    Num2String( sTmp, &pos, i, 16);
			    break;
			// %% - output % character
			case '%':
				sTmp[pos++] = '%';
				break;

			// Else, must be something else not handled.
			default:
				sTmp[pos++] = '?';
				break;
        }
    }
    sTmp[pos++] = 0;		// Mark the end of the string.
    DebugString(NULL, sTmp );	// Copy the string into the OS queue.
    return;
}

void Num2String( char *s, unsigned char* pPos, unsigned int u32Number, unsigned char u8Base) {

    char buf[33];
    char *p = buf + 33;
    uint32_t c, n;

    *--p = '\0';
    do {
        n = u32Number / u8Base;
        c = u32Number - (n * u8Base);
        if (c < 10) {
            *--p = '0' + c;
        } else {
            *--p = 'a' + (c - 10);
        }
        u32Number /= u8Base;
    } while (u32Number != 0);

    while (*p){
    	s[ *pPos ] = *p;
    	*pPos += 1;
        p++;
    }
    return;
}

