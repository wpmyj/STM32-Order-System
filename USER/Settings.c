#include "Application.h"

#define titles				4
#define SE_X					10				
#define SE_Y					25
#define SE_Weight			200
#define SE_Hight			25
#define SE_JX					5

const u8 Settings_title[titles][12] = {"时间设置","用户管理","背光及声音","关于"};

/*
	函数功能：系统设置
*/
void Settings_Func(void)
{
	u8 key;
	short i=0,tmp=1;
	
	LCD_Clear(YELLOW);
	BACK_COLOR = BROWN;
	
	LCD_DrawRecFill(0,0,220,20,LBBLUE);
	Display_String(94,3,80,16,"设置",16);
	
	LCD_DrawRecFill(10, 145, 60, 170,BROWN);
	Display_String(20,150,80,16,"返回",16);
	
	LCD_DrawRecFill(160, 145, 210, 170,BROWN);
	Display_String(170,150,80,16,"选择",16);	
	
	for(i=0;i<titles;i++){
		LCD_DrawRecFill(SE_X, (SE_Y+i*(SE_Hight+SE_JX)), SE_X+SE_Weight, (SE_Y+i*(SE_Hight+SE_JX))+SE_Hight,BROWN);
		Display_String(SE_X+4,(SE_Y+i*(SE_Hight+SE_JX)+4),120,16,(u8 *)Settings_title[i],16);	
	}
	
	i = 0;
	
	do{
		key = Key_Scan();
		
		/*退出*/
		if(key==KEY_ESC){
			Settings_flag = 0;
			Menu_flag = 1;
		}
		/*选择*/
		if(key==KEY_WKUP){
			Settings_flag = 0;
		}
		
		/*控制关标显示*/
		if(key==KEY_UP)		i--;
		if(key==KEY_DOWN)	i++;
		if(i>=titles)			i = 0;
		if(i<0)						i = titles - 1;
		
		/*更新显示*/
		if(tmp!=i){
			LCD_DrawRecFill(SE_X, (SE_Y+tmp*(SE_Hight+SE_JX)), SE_X+SE_Weight, (SE_Y+tmp*(SE_Hight+SE_JX))+SE_Hight,BROWN);
			Display_String(SE_X+4,(SE_Y+tmp*(SE_Hight+SE_JX)+4),120,16,(u8 *)Settings_title[tmp],16);	
			tmp = i;
			LCD_DrawRecFill(SE_X, (SE_Y+i*(SE_Hight+SE_JX)), SE_X+SE_Weight, (SE_Y+i*(SE_Hight+SE_JX))+SE_Hight,CYAN);
			Display_String(SE_X+4,(SE_Y+i*(SE_Hight+SE_JX)+4),120,16,(u8 *)Settings_title[i],16);	
		}
		
	
	}while(Settings_flag);
	
	/*当设置界面不被激活时，根据i的值激活相应界面*/
	if(Menu_flag==0)
		switch(i){
			case 0 : Settings_Time_flag = 1;break;
			case 1 : Settings_User_flag = 1;break;
			case 2 : Settings_LAB_flag = 1;break;
			case 3 : Settings_About_flag = 1;break;
		}
	
}
