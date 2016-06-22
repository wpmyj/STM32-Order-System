#include "Application.h"

/*菜单列表*/
const u8 *Settings_title[12] = {"时间设置","用户管理","背光及声音","关于"};

/*
	函数功能：系统设置
*/
void Settings_Func(void)
{
	static short i=0,tmp=1;
	/*起始横坐标，起始纵坐标，图标宽度，图标高度，横间隙，纵间隙，窗口贴片横数量，窗口贴片纵数量*/
	WINDOWS_TYPE Settings_Info = {10,25,200,25,5,5,1,4};	
	/*清屏颜色，背景颜色，名称起始横坐标，按键1，按键2*/
	WINDOWS_INIT_TYPE Settings_Win={GBLUE,LBBLUE,94,"设置","返回","选择"};
	/*界面初始化*/
	Windows_Init(Settings_Win);	
	/*初始化菜单*/
	Windows_Titles(Settings_Info,(u8 **)Settings_title,LBBLUE);
	/*设置高亮*/
	Windows_Title(Settings_Info,(u8 **)Settings_title,i,0,CYAN);
	do{
		/*获取功能键值*/
		Common_Key(&i,(short *)&Null,Settings_Info.tls_x,Settings_Info.tls_y, &Menu_flag,&Settings_flag,&Null);
		
		/*更新显示*/
		if(tmp!=i){
			/*恢复高亮*/
			Windows_Title(Settings_Info,(u8 **)Settings_title,tmp,0,LBBLUE);
			tmp = i;
			/*设置高亮*/
			Windows_Title(Settings_Info,(u8 **)Settings_title,i,0,CYAN);
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
