#include "Application.h"

#define Menu_YS   40
#define Menu_YE		118

const u16 Menu_Color[10] = {CYAN,DARKBLUE,BLUE,BRED,GRED,GBLUE,RED,MAGENTA,CYAN,DARKBLUE};
const u8 Menu_Name[10][6] = {"  ","开桌","点菜","催菜","加菜","退菜","查询","信息","设置","  "};

/*
	函数功能：菜单界面
*/
void Menu_Func(void)
{
	u8 key;
	static u8 Menu_Num=1,temp=1;
	
	LCD_Clear(YELLOW);
	BACK_COLOR = BROWN;
	
	LCD_DrawRecFill(0,0,220,20,LBBLUE);
	Display_String(94,3,80,16,"菜单",16);
	
	LCD_DrawRecFill(10, 145, 60, 170,BROWN);
	Display_String(20,150,80,16,"返回",16);
	
	LCD_DrawRecFill(160, 145, 210, 170,BROWN);
	Display_String(170,150,80,16,"选择",16);
	
	LCD_DrawRecFill(20, Menu_YS, 60, Menu_YE,Menu_Color[Menu_Num+1]);
	LCD_DrawRecFill(80, Menu_YS, 140, Menu_YE,Menu_Color[Menu_Num]);
	LCD_DrawRecFill(160, Menu_YS, 200, Menu_YE,Menu_Color[Menu_Num-1]);	
	LCD_Fill(90,126,130,150,YELLOW);
	Display_String(94,130,80,16,(unsigned char *)Menu_Name[Menu_Num],16);
	
	
	do{
		key = Key_Scan();
		
		/*退出*/
		if(key==KEY_ESC){
			Menu_flag = 0;
			Home_flag = 1;
		}
		/*选择*/
		if(key==KEY_WKUP){
			Menu_flag = 0;
		}
		
		/*菜单循环控制*/
		if(Menu_Num>=1&&Menu_Num<=8){
			if(key==KEY_LEFT){
				Menu_Num --;
			}
			if(key==KEY_RIGHT){
				Menu_Num ++;
			}
		}
		if(Menu_Num > 8) Menu_Num = 1;
		if(Menu_Num < 1) Menu_Num = 8;
		
		/*更新显示信息*/
		if(temp!=Menu_Num){
			temp = Menu_Num;
			LCD_DrawRecFill(20, Menu_YS, 60, Menu_YE,Menu_Color[Menu_Num+1]);
			LCD_DrawRecFill(80, Menu_YS, 140, Menu_YE,Menu_Color[Menu_Num]);
			LCD_DrawRecFill(160, Menu_YS, 200, Menu_YE,Menu_Color[Menu_Num-1]);
			LCD_Fill(90,126,130,150,YELLOW);
			Display_String(94,130,80,16,(unsigned char *)Menu_Name[Menu_Num],16);			
		}
	
	}while(Menu_flag);
	
	/*当Home_flag不被激活时，根据Menu_num选择激活那个界面*/
	if(Home_flag==0)
		switch (Menu_Num){
			case 1 : Newtable_flag 		= 1; break;
			case 2 : Order_flag    		= 1; break;
			case 3 : Reminder_flag 		= 1; break;
			case 4 : AddFood_flag  		= 1; break;
			case 5 : RetreatFood_flag = 1; break;
			case 6 : Query_flag 			= 1; break;
			case 7 : MMS_flag 				=	1; break;
			case 8 : Settings_flag 		= 1; break;
		}
	
}

