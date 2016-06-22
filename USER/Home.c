#include "Application.h"


void Home_Func(void)
{
	u8 key;
	
	LCD_Clear(YELLOW);
	BACK_COLOR = BROWN;
	
	LCD_DrawRecFill(0,0,220,20,LBBLUE);
	Display_String(53,3,130,16,"创黑科技点菜宝",16);

	LCD_DrawRecFill(50, 40, 170, 96,BROWN);
	
	LCD_DrawRecFill(10, 145, 60, 170,BROWN);
	Display_String(20,150,80,16,"退出",16);
	
	LCD_DrawRecFill(160, 145, 210, 170,BROWN);
	Display_String(170,150,80,16,"菜单",16);
	
	do{
		key = Key_Scan();
		
		if(key==KEY_ESC){
			Home_flag = 0;
			Login_flag = 1;
		}
		if(key==KEY_WKUP){
			Home_flag = 0;
			Menu_flag = 1;
		}
		
		RTC_Func();				//调用时钟显示
	}while(Home_flag);
	
}

