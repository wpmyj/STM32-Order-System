#include "Application.h"

void AddFood_Func(void)
{
	WINDOWS_INIT_TYPE AddFood_Win={YELLOW,BROWN,94,"加菜","返回","选择"};
	/*界面初始化*/
	Windows_Init(AddFood_Win);
	
	do{
		/*获取功能键值*/
		Common_Key((short *)&Null,(short *)&Null,Null,Null, &Menu_flag,&AddFood_flag,&Null);	
		
	}while(AddFood_flag);
	
}
