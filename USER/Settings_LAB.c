#include "Application.h"

/*清屏颜色，背景颜色，名称起始横坐标，按键1，按键2*/
WINDOWS_INIT_TYPE Settings_LAB_Win={YELLOW,BROWN,70,"背光及声音","返回","选择"};

/*起始横坐标，起始纵坐标，图标宽度，图标高度，横间隙，纵间隙，窗口贴片横数量，窗口贴片纵数量*/
WINDOWS_TYPE Settings_LAB_Info = {10,25,200,25,5,5,1,3};

const u8 *Settings_LAB[12] = {"背光开关","调节亮度","声音开关"};

/*
	函数功能：设置背光及声音
*/
void Settings_LAB_Func(void)
{
	u8 key;
	short i=0,tmp=1;
	
	/*窗口初始化*/
	Windows_Init(Settings_LAB_Win);	
	
	/*显示菜单*/
	Windows_Titles(Settings_LAB_Info,(u8 **)Settings_LAB,BROWN);
	
	do{
		
		key = Common_Key(&i,(short*)&Null,Settings_LAB_Info.tls_x, Settings_LAB_Info.tls_y,&Settings_flag,&Settings_LAB_flag,&Null);
		/*选择*/
		if(key==KEY_WKUP){
			Settings_LAB_flag = 1;
			if(i==0){
				KEY_LED = !KEY_LED;
				LCD_DrawRecFill(130, (25+i*(30)), 210, (25+i*(30))+25,CYAN);
				Display_String(160,(25+i*30+4),70,16,(u8 *)(KEY_LED?"开":"关"),16);	
			}
		}
		
		/*更新显示*/
		if(tmp!=i){
			Windows_Title(Settings_LAB_Info,(u8 **)Settings_LAB,tmp,0,BROWN);
			tmp = i;
			Windows_Title(Settings_LAB_Info,(u8 **)Settings_LAB,i,0,CYAN);
		}
	
	}while(Settings_LAB_flag);
}
