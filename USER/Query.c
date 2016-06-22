#include "Application.h"

/*************************************************************
	函数功能：查询界面
**************************************************************/
void Query_Func(void)
{	
	WINDOWS_INIT_TYPE Query_Win={YELLOW,BROWN,94,"查询","返回","选择"};
	/*界面初始化*/
	Windows_Init(Query_Win);	
	
	do{
		/*获取功能键值*/
		Common_Key((short *)&Null,(short *)&Null,Null,Null, &Menu_flag,&Query_flag,&Null);	
		
	}while(Query_flag);
}
