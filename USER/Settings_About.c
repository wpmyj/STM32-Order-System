#include "Application.h"

const u8 About[] = "    本点菜系统为深圳市创黑科技有限公司林静伟设计，版权所有！如有需要请联系设计者！                      电话:15017931073          QQ:277579066";

/*
	函数功能：设置界面关于
*/
void Settings_About_Func(void)
{
	u8 key;
	
	LCD_Clear(YELLOW);
	BACK_COLOR = YELLOW;
	
	LCD_DrawRecFill(0,0,220,20,LBBLUE);
	Display_String(94,3,80,16,"关于",16);
	
	LCD_DrawRecFill(10, 145, 60, 170,BROWN);
	Display_String(20,150,80,16,"返回",16);
	
	Display_String(10,25,210,120,(u8 *)About,16);
	
	do{
		key = Key_Scan();
		
		/*退出*/
		if(key==KEY_ESC){
			Settings_About_flag = 0;
			Settings_flag = 1;
		}
		
	}while(Settings_About_flag);
}
