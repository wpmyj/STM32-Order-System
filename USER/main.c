#include <stm32f10x.h>
#include "Application.h"

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
	LCD_Init();			//液晶屏初始化
	RTC_Init();			//实时时钟初始化
	
	Login_Func();
	
	while(1){
		key = Key_Scan();
		if(key) LCD_ShowNum(10,10,key,3,16);

	}
}

