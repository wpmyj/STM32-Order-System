#include "Application.h"


/*
	函数功能：信息提示框
*/
void Message_Warming_Func(u8 *Old_flag,u8 *New_flag, u8 *Str)
{
	WINDOWS_INIT_TYPE Msg_Win={LIGHTBLUE,LBBLUE,94,"提示"," 否"," 是"};
	/*窗口初始化*/
	Windows_Init(Msg_Win);	
	LCD_DrawRecFill(50, 50, 170, 96,WHITE);
	Display_String(70,60,170,96,Str,16);

	do{
		/*获取功能键值*/
		Common_Key((short *)&Null,(short *)&Null,Null,Null,Old_flag,&Message_Warming_flag,New_flag);
		
	}while(Message_Warming_flag);
	
}



