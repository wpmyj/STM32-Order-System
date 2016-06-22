#include "Application.h"



void Settings_User_Func(void)
{
	WINDOWS_INIT_TYPE Settings_User_Win={YELLOW,BROWN,78,"用户管理","返回","选择"};
	/*窗口初始化*/
	Windows_Init(Settings_User_Win);	
	
	do{
		/*获取功能键值*/
		Common_Key((short *)&Null,(short *)&Null,Null,Null, &Settings_flag,&Settings_User_flag,&Settings_flag);
		
	}while(Settings_User_flag);
}
