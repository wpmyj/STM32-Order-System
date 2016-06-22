#include "Application.h"

/*时间项*/
const u8 *Time[6] = {"年","月","日","时","分","秒"};
const u8 *Null_time[6] = {0};

/*
	函数功能：辅助功能
*/
void Disp_Time_Info(WINDOWS_TYPE t,u8 x,u8 y,u8 *show,u16 color)
{
	LCD_DrawRecFill((t.St_x+y*(t.Weight+t.Jx_x)), (t.St_y+x*(t.Hight+t.Jx_y)), 
									(t.St_x+y*(t.Weight+t.Jx_x)+t.Weight), (t.St_y+x*(t.Hight+t.Jx_y)+t.Hight),color);
	Display_String((t.St_x+y*(t.Weight+t.Jx_x)+4),(t.St_y+x*(t.Hight+t.Jx_y)+4),36,16,show,16);					//显示时间
}

/*
	函数功能：设置时间
*/
void Settings_Time_Func(void)
{
	u8 key;
	u8 set_flag=0;
	short i=0,j=0,tmp1=1,tmp2=1;
	u8 date_time[6][5] = {0};
	TIME_TYPE time;
	
	/*起始横坐标，起始纵坐标，图标宽度，图标高度，横间隙，纵间隙，窗口贴片横数量，窗口贴片纵数量*/
	WINDOWS_TYPE Set_Name_Info = {45,53,25,25,48,10,3,2};
	WINDOWS_TYPE Set_Time_Info = {5,53,40,25,33,10,3,2};
	/*清屏颜色，背景颜色，名称起始横坐标，按键1，按键2*/
	WINDOWS_INIT_TYPE Set_Time_Win={78,"设置时间","取消","确认"};
	/*界面初始化*/
	Windows_Init(Set_Time_Win);	
	/*显示菜单*/
	Windows_Titles(Set_Name_Info,(u8 **)Time,Theme_BACK);
	Windows_Titles(Set_Time_Info,(u8 **)Null_time,Theme_BACK);
	
	do{
		
		/*获取功能键值*/
		key = Common_Key(&i,&j,Set_Time_Info.tls_x,Set_Time_Info.tls_y,&Settings_flag,&Settings_Time_flag,&Settings_flag);		
		if(key==KEY_WKUP){
			set_flag = 1;
		}
		
		/*输入获取时间*/	
		Key_Input1(Set_Time_Info,i,j,key,4,date_time[j+i*Set_Time_Info.tls_x]);
		Display_String((Set_Time_Info.St_x+j*(Set_Time_Info.Weight+Set_Time_Info.Jx_x)+4),	//显示时间
									(Set_Time_Info.St_y+i*(Set_Time_Info.Hight+Set_Time_Info.Jx_y)+4),36,16,date_time[j+i*Set_Time_Info.tls_x],16);					
		
		/*更新显示*/
		if(tmp1!=i||tmp2!=j){	
			/*恢复原来的图标颜色*/
			Disp_Time_Info(Set_Time_Info,tmp1,tmp2,(u8 *)date_time[tmp2+tmp1*Set_Time_Info.tls_x],Theme_BACK);			
			tmp1 = i;
			tmp2 = j;
			/*选择新的图标，添加高亮*/
			Disp_Time_Info(Set_Time_Info,i,j,(u8 *)date_time[tmp2+tmp1*Set_Time_Info.tls_x],Theme_SLE);
		}
		
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



