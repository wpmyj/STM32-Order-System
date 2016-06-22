#include "Application.h"

/**********************************************************
	函数功能：主界面
***********************************************************/
void Home_Func(void)
{
	WINDOWS_INIT_TYPE Home_Win={53,"创黑科技点菜宝","退出","菜单"};
	/*窗口初始化*/
	Windows_Init(Home_Win);
	LCD_DrawRecFill(50, 40, 170, 96,Theme_BACK);

	do{
		/*获取功能键值*/
		Common_Key((short *)&Null,(short *)&Null,Null,Null, &Login_flag,&Home_flag,&Menu_flag);
		/*调用时钟显示*/
		RTC_Func();			
		
	}while(Home_flag);
	
}

