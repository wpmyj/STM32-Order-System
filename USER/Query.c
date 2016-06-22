#include "Application.h"

/*************************************************************
	函数功能：查询界面
**************************************************************/
void Query_Func(void)
{		
	u8 key;
	u8 *Query_Table;
	
	/*界面信息*/
	WINDOWS_INIT_TYPE Query_Win={YELLOW,BROWN,94,"查询","取消","确认"};
	/*界面初始化*/
	Windows_Init(Query_Win);
	LCD_DrawRecFill(40,40,180,60,BROWN);
	Display_String(43,43,150,16,"请输入查询桌号：",16);
	LCD_DrawRecFill(40,80,180,120,BROWN);
	
	do{
		
		/*获取功能键值*/
		key = Common_Key((short*)&Null,(short*)&Null,Null,Null, &Menu_flag,&Query_flag,&AddFood_flag);
		if((key==KEY_WKUP)&&Clear_flag){
			
		}
			
		/*获取查询桌子号*/
		Query_Table = Key_Input(key,3,&Clear_All);
		Display_String(98,90,80,16,Query_Table,16);
		
	}while(Query_flag);
}
