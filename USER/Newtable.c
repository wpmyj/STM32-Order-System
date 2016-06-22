#include "Application.h"


/*
	函数功能：开新桌
*/
void Newtable_Func(void)
{
	u8 key;
	u8 *Table;
	
	LCD_Clear(YELLOW);
	BACK_COLOR = BROWN;
	
	LCD_DrawRecFill(0,0,220,20,LBBLUE);
	Display_String(94,3,80,16,"开桌",16);
	
	LCD_DrawRecFill(10, 145, 60, 170,BROWN);
	Display_String(20,150,80,16,(u8 *)(Clear_flag?"清除":"取消"),16);
	
	LCD_DrawRecFill(160, 145, 210, 170,BROWN);
	Display_String(170,150,80,16,"确认",16);	
	
	LCD_DrawRecFill(40,40,180,60,BROWN);
	Display_String(43,43,150,16,"请输入新开桌号：",16);
	
	LCD_DrawRecFill(40,80,180,120,BROWN);
	
	do{
		key = Key_Scan();
		
		/*退出*/
		if((key==KEY_ESC)&&Clear_flag==0){
			Newtable_flag = 0;
			Menu_flag = 1;
		}
		/*选择*/
		if((key==KEY_WKUP)&&Clear_flag){
			Newtable_flag = 0;
			Menu_flag = 1;
			/*后期加上发送桌子号*/
		}
		
		/*获取新开桌子号*/
		Table = Key_Input(key);
		Display_String(70,90,120,16,Table,16);
		
	}while(Newtable_flag);
	
}


