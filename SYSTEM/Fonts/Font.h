#ifndef _FONT_H_
#define _FONT_H_
#include "stm32f10x.h"
#include "W25Q64.h"
#include "ILI9341.h"

typedef struct
{
	u32 F16Addr;		//GBK16地址
	u32 F24Addr;		//GBK24地址
}Font_Info;				//存放字体地址信息

extern Font_Info Font_Addr;		//字体地址

/*相关函数声明*/
void Font_Init(void);
void Get_Font_Data(u8 *HZ,u8 *buff,u8 size);
void Display_HZ(u16 x,u16 y,u8 *font,u8 size);
void Display_String(u16 x,u16 y,u16 width,u16 height,u8*str,u8 size);


#endif
