#include "Application.h"

void Settings_User_Func(void)
{
	u8 key;
	
	LCD_Clear(YELLOW);
	BACK_COLOR = BROWN;
	
	LCD_DrawRecFill(0,0,220,20,LBBLUE);
	Display_String(78,3,80,16,"�û�����",16);
	
	LCD_DrawRecFill(10, 145, 60, 170,BROWN);
	Display_String(20,150,80,16,"����",16);
	
	LCD_DrawRecFill(160, 145, 210, 170,BROWN);
	Display_String(170,150,80,16,"ѡ��",16);	
	
	do{
		key = Key_Scan();
		
		/*�˳�*/
		if(key==KEY_ESC){
			Settings_User_flag = 0;
			Settings_flag = 1;
		}
		/*ѡ��*/
		if(key==KEY_WKUP){
			
		}
	
	}while(Settings_User_flag);
}