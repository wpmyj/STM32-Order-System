#include "Application.h"

/*
	函数功能：开新桌
*/
void Newtable_Func(void)
{
	/*老界面标志，自身界面标志，新界面标志，窗体名称，获取桌子号提示，确认提示*/
	Get_Table_Func(&Menu_flag, &Newtable_flag,&Order_flag,"开桌","请输入新开桌号：","是否点菜？");
}

/*
	函数功能：催菜功能
*/
void Reminder_Func(void)
{
	/*老界面标志，自身界面标志，新界面标志，窗体名称，获取桌子号提示，确认提示*/
	Get_Table_Func(&Menu_flag, &Reminder_flag,&RetreatFood_flag,"催菜","请输入催菜桌号：","是否催菜？");
}


void Query_Func(void)
{		
	/*老界面标志，自身界面标志，新界面标志，窗体名称，获取桌子号提示，确认提示*/
	Get_Table_Func(&Menu_flag, &Query_flag,&AddFood_flag,"查询","请输入查询桌号：","是否查询？");
}
