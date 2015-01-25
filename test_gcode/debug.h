
#ifndef _DEBUG_H_
#define _DEBUG_H_

typedef enum _dev_type
{
	File,
	Uart,
	Spi,
	Eth,
}DEVTYPE;

typedef enum _debug_level
{
	Info,
	Warn,
	Error,

}DBG_LEVEL;

typedef struct _dev_debug
{
	DEVTYPE type;
	char *name;
}DebugDevice;

typedef struct debug_devices
{
	DebugDevice* prev;
	DebugDevice* next;
};

DebugDevice* debug_tx_init(int type,char* dev);
void debug_tx_message(DebugDevice* dd,DBG_LEVEL level,char* msg);

void DebugString(DebugDevice* dd,char* s );
void DebugPrintf(DebugDevice* dd,const char *fmt, ...);
void Num2String( char *s, unsigned char* pPos, unsigned int u32Number, unsigned char u8Base);

#endif
