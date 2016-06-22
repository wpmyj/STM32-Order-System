#include "Application.h"

#define Menu_YS   40
#define Menu_YE		118

const u16 Menu_Color[10] = {CYAN,DARKBLUE,BLUE,BRED,GRED,GBLUE,RED,MAGENTA,CYAN,DARKBLUE};
const u8 Menu_Name[10][6] = {"  ","开桌","点菜","催菜","加菜","退菜","查询","信息","设置","  "};

/****************************************************************
	函数功能：辅助功能
*****************************************************************/
void Disp_Menu(u8 Menu_Num)
{
	LCD_DrawRecFill(20, Menu_YS, 60, Menu_YE,Menu_Color[Menu_Num+2]);
	LCD_DrawRecFill(80, Menu_YS, 140, Menu_YE,Menu_Color[Menu_Num+1]);
	LCD_DrawRecFill(160, Menu_YS, 200, Menu_YE,Menu_Color[Menu_Num]);	
	BACK_COLOR = Theme_Color;
	Display_String(94,130,80,16,(unsigned char *)Menu_Name[Menu_Num+1],16);
}

/****************************************************************
	函数功能：菜单界面
*****************************************************************/
void Menu_Func(void)
{
	static short Menu_Num=0,temp=0;
	WINDOWS_INIT_TYPE Menu_Win={94,"菜单","返回","选择"};

	/*窗口初始化*/
	Windows_Init(Menu_Win);
	/*彩片块初始化*/
	Disp_Menu(Menu_Num);
	
	do{
		/*获取功能键值*/
		Common_Key((short *)&Null,&Menu_Num,8,Null, &Home_flag,&Menu_flag,(u8*)&Null);
		
		/*更新显示信息*/
		if(temp!=Menu_Num){	
			temp = Menu_Num;
			Disp_Menu(Menu_Num);		
		}
	
	}while(Menu_flag);
	
	/*当Home_flag不被激活时，根据Menu_num选择激活那个界面*/
	if(Home_flag==0)
		switch (Menu_Num){
			case 0 : Newtable_flag 		= 1; break;
			case 1 : Order_flag    		= 1; break;
			case 2 : Reminder_flag 		= 1; break;
			case 3 : AddFood_flag  		= 1; break;
			case 4 : RetreatFood_flag = 1; break;
			case 5 : Query_flag 			= 1; break;
			case 6 : MMS_flag 				=	1; break;
			case 7 : Settings_flag 		= 1; break;
		}
	
}


