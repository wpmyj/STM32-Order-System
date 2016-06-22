#include "Application.h"


/********************************************************************************
	函数功能：共同获取桌子号功能界面
	参数：u8 *Old_flag：老的界面标志；
				u8 *Self_flag：自身界面标志；
				u8 *New_flag：新的界面标志；
				u8 *name：窗体名称；
				u8 *show：显示桌子内容；
				u8 *warming：提示内容
*********************************************************************************/
u16 Get_Table_Func(u8 *Old_flag, u8 *Self_flag, u8 *New_flag,u8 *name,u8 *show,u8 *warming)
{
	u8 key;
	u16 table_num;
	u8 *Table;
	/*界面信息*/
	WINDOWS_INIT_TYPE Win={94,"    ","取消","确认"};
	Win.Name = name;
	/*界面初始化*/
	Windows_Init(Win);
	LCD_DrawRecFill(40,40,180,60,Theme_BACK);
	Display_String(43,43,150,16,show,16);
	LCD_DrawRecFill(40,80,180,120,Theme_BACK);
	
	do{
		/*获取功能键值*/
		key = Common_Key((short*)&Null,(short*)&Null,Null,Null, Old_flag,Self_flag,Self_flag);
		if((key==KEY_WKUP)&&Clear_flag){
			*Self_flag = 0;
			Message_Warming_flag = 1;
			sscanf((char *)Table,"%d",(int *)&table_num);
			#ifdef Debug_Get_Table
			printf("桌子号：%d\r\n",table_num);
			#endif
		}
		/*获取桌子号*/
		Table = Key_Input(key,3,&Clear_All);
		Display_String(98,90,80,16,Table,16);
	}while(*Self_flag);
	if(*Old_flag==0)
		Message_Warming_Func(Old_flag,New_flag, warming);
	
	return table_num;
}


/********************************************************************************
	函数功能：开新桌
********************************************************************************/
void Newtable_Func(void)
{
	/*老界面标志，自身界面标志，新界面标志，窗体名称，获取桌子号提示，确认提示*/
	u16 Newtable_num = Get_Table_Func(&Menu_flag, &Newtable_flag,&Order_flag,"开桌","请输入新开桌号：","是否点菜？");
	COUSTOMER.Table = Newtable_num;
}

/********************************************************************************
	函数功能：催菜功能
********************************************************************************/
void Reminder_Func(void)
{
	u8 str[40];
	/*老界面标志，自身界面标志，新界面标志，窗体名称，获取桌子号提示，确认提示*/
	u16 Remider_num = Get_Table_Func(&Menu_flag, &Reminder_flag,&Menu_flag,"催菜","请输入催菜桌号：","是否催菜？");
	COUSTOMER.Table = Remider_num;
	sprintf((char *)str,"%d桌客人在催菜！快点！",COUSTOMER.Table);
	Send_msg(0x08,str);
}

/********************************************************************************
	函数功能：查询功能
********************************************************************************/
void Query_Func(void)
{		
	/*老界面标志，自身界面标志，新界面标志，窗体名称，获取桌子号提示，确认提示*/
	u16 Query_num = Get_Table_Func(&Menu_flag, &Query_flag,&AddFood_flag,"查询","请输入查询桌号：","是否查询？");
	COUSTOMER.Table = Query_num;
}


/********************************************************************************/

