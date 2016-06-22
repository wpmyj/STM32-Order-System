#include "Application.h"

const u8 *Settings_LAB[3] = {"背光开关","调节亮度","声音开关"};
/*
	函数功能：辅助功能
	参数：u8 i：第几行
				u8 num：显示调节亮度的级别
				u8 flag：哪一项标志
				u16 color：颜色
*/
void Display_Info(u8 i,u8 num,u8 flag,u16 color)
{
	LCD_DrawRecFill(130, (25+i*(30)), 210, (25+i*(30))+25,color);
	if(i==0||i==2){	
		Display_String(160,(25+i*30+4),70,16,(u8 *)(flag?"开":"关"),16);
	}
	if(i==1){
		BACK_COLOR = color;
		LCD_ShowNum(160,(25+i*30+4),num,2,16);	
	}
}

/*
	函数功能：设置背光及声音
*/
void Settings_LAB_Func(void)
{
	u8 key,tmp;
	short i=0,j=LCD_BL_LIGHT,tmp1=1,tmp2=10;
	/*起始横坐标，起始纵坐标，图标宽度，图标高度，横间隙，纵间隙，窗口贴片横数量，窗口贴片纵数量*/
	WINDOWS_TYPE Settings_LAB_Info = {10,25,200,25,5,5,1,3};
	/*清屏颜色，背景颜色，名称起始横坐标，按键1，按键2*/
	WINDOWS_INIT_TYPE Settings_LAB_Win={GBLUE,LBBLUE,70,"背光及声音","返回","选择"};
	/*窗口初始化*/
	Windows_Init(Settings_LAB_Win);	
	/*显示菜单*/
	Windows_Titles(Settings_LAB_Info,(u8 **)Settings_LAB,LBBLUE);
	for(tmp=0;tmp<3;tmp++)
		Display_Info(tmp,j,(tmp?BEEP_EN:KEY_LED),LBBLUE);
	
	do{
		
		key = Common_Key(&i,&j,21, Settings_LAB_Info.tls_y,&Settings_flag,&Settings_LAB_flag,&Null);
		/*选择开关*/
		if(key==KEY_WKUP){
			Settings_LAB_flag = 1;
			if(i==0)	KEY_LED = !KEY_LED;
			if(i==2)	BEEP_EN = !BEEP_EN;
			Display_Info(i,j,(i?BEEP_EN:KEY_LED),CYAN);
		}
		
		/*调节亮度*/
		if((tmp2!=j)&&i==1){
			LCD_BL_PWM = j * 5;
			tmp2 = j;
			BACK_COLOR = CYAN;
			Display_Info(i,j,(i?BEEP_EN:KEY_LED),CYAN);
		}
		
		/*更新显示*/
		if(tmp1!=i){
			/*显示旧的信息，取消高亮*/
			Windows_Title(Settings_LAB_Info,(u8 **)Settings_LAB,tmp1,0,LBBLUE);
			Display_Info(tmp1,j,(tmp1?BEEP_EN:KEY_LED),LBBLUE);
			tmp1 = i;
			/*显示新的信息，设置高亮*/
			Windows_Title(Settings_LAB_Info,(u8 **)Settings_LAB,i,0,CYAN);
			Display_Info(i,j,(i?BEEP_EN:KEY_LED),CYAN);
		}
	
	}while(Settings_LAB_flag);
	
	/*保存数据*/
	LCD_BL_LIGHT = j;
	SAVE_Data();
}


