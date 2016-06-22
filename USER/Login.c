#include "Application.h"

const u8 *name[2] = {"用户:","密码:"};
const u8 *mima[2] = {"        ","        "};

/*
	函数功能：登陆界面
*/
void Login_Func(void)
{
	u8 key=0;
	short i=0,tmp=1;
	ACCOUNT_TYPE Account={0};
	
	/*起始横坐标，起始纵坐标，图标宽度，图标高度，横间隙，纵间隙，窗口贴片横数量，窗口贴片纵数量*/
	WINDOWS_TYPE Login_Name = {20,45,60,28,0,22,1,2};
	WINDOWS_TYPE Login_Info = {95,45,100,28,0,22,1,2};
	/*名称起始横坐标，按键1，按键2*/
	WINDOWS_INIT_TYPE Login_Win = {77,"用户登陆","清除","确认"};
	/*界面初始化*/
	Windows_Init(Login_Win);	
	/*显示菜单*/
	Windows_Titles(Login_Name,(u8 **)name,Theme_BACK);
	Windows_Titles(Login_Info,(u8 **)mima,Theme_BACK);
	
	do{
		
		/*获取功能键值*/
		key = Common_Key((short *)&i,(short *)&Null,Null,Login_Info.tls_y, (u8 *)&Null,(u8 *)&Null,(u8 *)&Null);
		if(key==KEY_WKUP){
			if(!strcmp((const char *)Account.User,	(const char *)DefAcc.User)&&
				 !strcmp((const char *)Account.Passwd,(const char *)DefAcc.Passwd)){
				Login_flag = 0;				//失能登陆界面
				Home_flag = 1;				//使能主界面	
			}
				
			#ifdef Debug_Login
				printf("user:%s\r\npasswd:%s\r\n",Account.User,Account.Passwd);
				printf("DefAcc.user:%s\r\nDefAcc.passwd:%s\r\n",DefAcc.User,DefAcc.Passwd);
			#endif
		}
		
		/*输入获取时间*/	
		Key_Input_Str(Login_Info,i,0,key,8,i?Account.Passwd:Account.User);
		BACK_COLOR = Theme_SLE;
		Display_String((Login_Info.St_x+4),(Login_Info.St_y+i*(Login_Info.Hight+Login_Info.Jx_y)+4),
										88,16,(i?Account.Passwd:Account.User),16);						
	
		/*更新显示*/
		if(tmp!=i){	
			/*恢复原来的图标颜色*/
			DispStr_Win(Login_Info,tmp,0,tmp?Account.Passwd:Account.User,Theme_BACK);		
			tmp = i;
			/*选择新的图标，添加高亮*/
			DispStr_Win(Login_Info,i,0,i?Account.Passwd:Account.User,Theme_SLE);	
		}
		
	}while(Login_flag);
	
}


