#include "Application.h"

/*时间项*/
const u8 *Time[6] = {"    年","    月","    日","    时","    分","    秒"};
u8 date_time[6][11] = {0};

/*
	函数功能：辅助功能
*/
void Disp_Time_Info(WINDOWS_TYPE t,u8 x,u8 y,u16 color)
{
	LCD_DrawRecFill((t.St_x+y*(t.Weight+t.Jx_x)), (t.St_y+x*(t.Hight+t.Jx_x)), (t.St_x+y*(t.Weight+t.Jx_x)+t.Weight), (t.St_y+x*(t.Hight+t.Jx_x)+t.Hight),color);
	Display_String((t.St_x+y*(t.Weight+t.Jx_x)+10),(t.St_y+x*(t.Hight+t.Jx_x)+4),60,16,(u8 *)Time[y+x*3],16);
	Display_String((t.St_x+y*(t.Weight+t.Jx_x)+4),(t.St_y+x*(t.Hight+t.Jx_x)+4),36,16,date_time[y+x*3],16);					//显示时间
}

/*
	函数功能：设置时间
*/
void Settings_Time_Func(void)
{
	u8 key;
	u8 *str;
	u8 set_flag=0;
	static short i=0,j=0,tmp1=0,tmp2=0;
	TIME_TYPE time;
	
	/*起始横坐标，起始纵坐标，图标宽度，图标高度，横间隙，纵间隙，窗口贴片横数量，窗口贴片纵数量*/
	WINDOWS_TYPE Set_Time_Info = {10,53,60,25,10,10,3,2};
	/*清屏颜色，背景颜色，名称起始横坐标，按键1，按键2*/
	WINDOWS_INIT_TYPE Set_Time_Win={YELLOW,BROWN,78,"设置时间","取消","确认"};
	/*界面初始化*/
	Windows_Init(Set_Time_Win);	
	/*显示菜单*/
	Windows_Titles(Set_Time_Info,(u8 **)Time,BROWN);
	Disp_Time_Info(Set_Time_Info,i,j,CYAN);
	do{
		
		/*获取功能键值*/
		key = Common_Key(&i,&j,Set_Time_Info.tls_x,Set_Time_Info.tls_y,&Settings_flag,&Settings_Time_flag,&Settings_flag);		
		if(key==KEY_WKUP){
			set_flag = 1;
			strcpy((char *)date_time[j+i*Set_Time_Info.tls_x],(const char *)str);
		}
		
		/*更新显示*/
		if(tmp1!=i||tmp2!=j){	
			/*恢复原来的图标颜色*/
			strcpy((char *)date_time[tmp2+tmp1*Set_Time_Info.tls_x],(const char *)str);
			Disp_Time_Info(Set_Time_Info,tmp1,tmp2,BROWN);		
			tmp1 = i;
			tmp2 = j;
			Clear_All = 1;
			/*选择新的图标，添加高亮*/
			Disp_Time_Info(Set_Time_Info,i,j,CYAN);
		}
		/*输入获取时间*/
		str = Key_Input(key,4,&Clear_All);			
		Display_String((Set_Time_Info.St_x+j*(Set_Time_Info.Weight+Set_Time_Info.Jx_x)+4),	//显示时间
										(Set_Time_Info.St_y+i*(Set_Time_Info.Hight+Set_Time_Info.Jx_x)+4),36,16,str,16);					
		
	}while(Settings_Time_flag);	
	/*设置时间*/
	if(set_flag){
		sscanf((char *)date_time[0],"%d",(int*)&time.year);
		sscanf((char *)date_time[1],"%d",(int*)&time.month);
		sscanf((char *)date_time[2],"%d",(int*)&time.day);
		sscanf((char *)date_time[3],"%d",(int*)&time.hour);
		sscanf((char *)date_time[4],"%d",(int*)&time.min);
		sscanf((char *)date_time[5],"%d",(int*)&time.second);
		Set_RTC_Time(time);
	}
}




