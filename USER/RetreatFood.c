#include "Application.h"

WINDOWS_INIT_TYPE RetreatFood_Win={YELLOW,BROWN,94,"退菜","返回","选择"};

/*
	函数功能：退菜界面
*/
void RetreatFood_Func(void)
{
	/*窗口初始化*/
	Windows_Init(RetreatFood_Win);
	
	do{
		/*获取功能键值*/
		Common_Key((short *)&Null,(short *)&Null,Null,Null, &Menu_flag,&RetreatFood_flag,&Null);
		
	}while(RetreatFood_flag);
	
}

