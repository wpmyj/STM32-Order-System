#include "Application.h"

WINDOWS_INIT_TYPE MMS_Win={YELLOW,BROWN,94,"信息","返回","选择"};

void MMS_Func(void)
{
	/*窗口初始化*/
	Windows_Init(MMS_Win);	
	
	do{
		/*获取功能键值*/
		Common_Key((short *)&Null,(short *)&Null,Null,Null, &Menu_flag,&MMS_flag,&Null);
		
	}while(MMS_flag);
	
}
