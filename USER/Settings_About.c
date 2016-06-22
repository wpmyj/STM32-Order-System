#include "Application.h"

const u8 About[] = "    本点菜系统为深圳市创黑科技有限公司林静伟设计，版权所有！如有需要请联系设计者！                      电话:15017931073          QQ:277579066";

/*
	函数功能：设置界面关于
*/
void Settings_About_Func(void)
{	
	WINDOWS_INIT_TYPE Settings_About_Win={YELLOW,BROWN,94,"关于","返回","确认"};
	/*窗口初始化*/
	Windows_Init(Settings_About_Win);	
	
	BACK_COLOR = YELLOW;
	Display_String(10,25,210,120,(u8 *)About,16);
	
	do{
		/*获取功能键值*/
		Common_Key((short *)&Null,(short *)&Null,Null,Null, &Settings_flag,&Settings_About_flag,&Settings_flag);
		
	}while(Settings_About_flag);
}
