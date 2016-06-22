#include <stm32f10x.h>
#include "LED.h"
#include "Beep.h"
#include "delay.h"
#include "KEY.h"
#include "USART.h"
#include "W25Q64.h"
#include "Font.h"
#include "ILI9341.h"

/*
	函数功能：主函数
*/
int main(void)
{
	u8 key;
	LED_Init();			//LED灯初始化
	Beep_Init();		//蜂鸣器初始化
	KEY_Init();			//按键初始化
	Delay_Init();		//延时函数初始化
	USART1_Init(115200);	//串口初始化
	W25Q64_Init();	//存储芯片初始化
	Font_Init();		//字库初始化
	
	LCD_Init();			
	
	LCD_Clear(BLUE);
	for(key=0;key<110;key++)
	{
		Draw_Circle(110,88,key,BLACK);								//画圆
	}
	
	LCD_ShowString(110,88,80,16,16,"hello");
	Display_String(10,26,220,16,"屏幕初始完成！",16);
	
	
	while(1){
		key = Key_Scan();
		if(key) LCD_ShowNum(10,10,key,3,16);
	}
}

