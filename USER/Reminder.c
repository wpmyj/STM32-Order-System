#include "Application.h"

/*
	函数功能：催菜功能
*/
void Reminder_Func(void)
{
	u8 key;
	u8 *Reminder_Table;
	
	LCD_Clear(YELLOW);
	BACK_COLOR = BROWN;
	
	LCD_DrawRecFill(0,0,220,20,LBBLUE);
	Display_String(94,3,80,16,"催菜",16);
	
	LCD_DrawRecFill(10, 145, 60, 170,BROWN);
	Display_String(20,150,80,16,(u8 *)(Clear_flag?"清除":"取消"),16);
	
	LCD_DrawRecFill(160, 145, 210, 170,BROWN);
	Display_String(170,150,80,16,"确认",16);	
	
	LCD_DrawRecFill(40,40,180,60,BROWN);
	Display_String(43,43,150,16,"请输入催菜桌号：",16);
	
	LCD_DrawRecFill(40,80,180,120,BROWN);
	
	do{
		key = Key_Scan();
		
		/*退出*/
		if((key==KEY_ESC)&&Clear_flag==0){
			Reminder_flag = 0;
			Menu_flag = 1;
		}
		/*选择*/
		if((key==KEY_WKUP)&&Clear_flag){
			Reminder_flag = 0;
			Menu_flag = 1;
			/*后期加上发送桌子号*/
		}
	
		/*获取催菜桌子号*/
		Reminder_Table = Key_Input(key);
		Display_String(70,90,120,16,Reminder_Table,16);
		
	}while(Reminder_flag);
	
}

