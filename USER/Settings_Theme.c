#include "Application.h"

/*菜单列表*/
const u8 *Theme_title[3] = {"棕黄灰","浅青绿","紫罗兰"};
/*
	函数功能：主题设置
*/
void Settings_Theme_Func(void)
{
	short i=0,tmp=1;
	u8 key,update_flag=0;
	/*名称起始横坐标，按键1，按键2*/
	WINDOWS_INIT_TYPE Settings_Theme_Win={78,"主题设置","返回","选择"};
	/*起始横坐标，起始纵坐标，图标宽度，图标高度，横间隙，纵间隙，窗口贴片横数量，窗口贴片纵数量*/
	WINDOWS_TYPE Theme_Info = {10,25,200,25,5,5,1,3};	
	/*窗口初始化*/
	Windows_Init(Settings_Theme_Win);	
	/*初始化菜单*/
	Windows_Titles(Theme_Info,(u8 **)Theme_title,Theme_BACK);
	/*设置高亮*/
	Windows_Title(Theme_Info,(u8 **)Theme_title,i,0,Theme_SLE);
	
	do{
		/*获取功能键值*/
		key = Common_Key((short *)&i,(short *)&Null,Null,Theme_Info.tls_y, &Settings_flag,&Settings_Theme_flag,&Settings_flag);
		if(key==KEY_WKUP){	
			update_flag = 1;	//更新主题标志位置1
		}
		if(i!=tmp){
			/*恢复高亮*/
			Windows_Title(Theme_Info,(u8 **)Theme_title,tmp,0,Theme_BACK);
			tmp = i;
			/*设置高亮*/
			Windows_Title(Theme_Info,(u8 **)Theme_title,i,0,Theme_SLE);
		}
		
	}while(Settings_Theme_flag);
	
	if(update_flag){						//更新系统主题
		switch(i){
			case 0 :{							//棕黄灰
				Theme_Color = YELLOW;
				Theme_BACK = BROWN;
				Theme_SLE = GRAY;
				break;
			}
			case 1 :{ 							//浅青绿
				Theme_Color = GBLUE;
				Theme_BACK = LBBLUE;
				Theme_SLE = CYAN;			
				break;
			}
			case 2 :{ 							//紫罗兰
				Theme_Color = MAGENTA;
				Theme_BACK = BRRED;
				Theme_SLE = GRED;			
				break;
			}
		}
		SAVE_Data();						//保存数据
	}
	
}
