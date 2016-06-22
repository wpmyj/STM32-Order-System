#include "Application.h"

static u8 Home_flag=0; 

void Home_Func(void)
{
	u8 key;
	
	Home_flag = 0;
	
	LCD_DrawRecFill(0,0,220,20,LBBLUE);
	
	LCD_DrawRecFill(10, 145, 60, 170,BROWN);
	Display_String(20,150,80,16,"退出",16);
	
	LCD_DrawRecFill(160, 145, 210, 170,BROWN);
	Display_String(170,150,80,16,"菜单",16);
	
	do{
		key = Key_Scan();
		if(key==KEY_ESC)
			Home_flag = 1;
		RTC_Func();				//调用时钟显示
	}while(!Home_flag);
}

