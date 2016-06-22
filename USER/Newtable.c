#include "Application.h"

#define Input_Cnt		3 

/*
	函数功能：开新桌
*/
void Newtable_Func(void)
{
	u8 key;
	u8 *Table;
	
	/*界面信息*/
	WINDOWS_INIT_TYPE Newtable_Win={YELLOW,BROWN,94,"开桌","取消","确认"};
	/*界面初始化*/
	Windows_Init(Newtable_Win);
	
	LCD_DrawRecFill(40,40,180,60,BROWN);
	Display_String(43,43,150,16,"请输入新开桌号：",16);
	
	LCD_DrawRecFill(40,80,180,120,BROWN);
	
	do{
		
		/*获取功能键值*/
		key = Common_Key((short*)&Null,(short*)&Null,Null,Null, &Menu_flag,&Newtable_flag,&Menu_flag);
		
		/*获取新开桌子号*/
		Table = Key_Input(key,Input_Cnt,&Clear_All);
		Display_String(98,90,80,16,Table,16);
		
	}while(Newtable_flag);
	
}


