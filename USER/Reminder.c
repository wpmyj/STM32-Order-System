#include "Application.h"

#define Input_Cnt		3

/*
	函数功能：催菜功能
*/
void Reminder_Func(void)
{
	u8 key;
	u8 *Reminder_Table;
	
	WINDOWS_INIT_TYPE Reminder_Win={YELLOW,BROWN,94,"催菜","取消","确认"};
	/*界面初始化*/
	Windows_Init(Reminder_Win);
	
	LCD_DrawRecFill(40,40,180,60,BROWN);
	Display_String(43,43,150,16,"请输入催菜桌号：",16);
	
	LCD_DrawRecFill(40,80,180,120,BROWN);
	
	do{
	
		/*获取功能键值*/
		key = Common_Key((short *)&Null,(short *)&Null,Null,Null, &Menu_flag,&Reminder_flag,&Menu_flag);	
		
		/*获取催菜桌子号*/
		Reminder_Table = Key_Input(key,Input_Cnt,&Clear_All);
		Display_String(98,90,80,16,Reminder_Table,16);
		
	}while(Reminder_flag);
	Clear_All = 1;
	Clear_flag = 1;
}

