#include "Application.h"

u8 Login_flag = 1;
u8 Home_flag = 0;
u8 Menu_flag = 0;
u8 Newtable_flag = 0;
u8 Order_flag = 0;
u8 Reminder_flag = 0;
u8 AddFood_flag = 0;
u8 RetreatFood_flag = 0;
u8 Query_flag = 0;
u8 MMS_flag = 0;
u8 Settings_flag = 0;


/*
	函数功能：实时时钟
*/
void RTC_Func(void)
{
	u8 Date_String[20];				//存放DATE数据
	u8 Time_String[20];				//存放TIME数据
	TIME_TYPE Disp_Time;			//存储时间结构体
	
	Display_HZ(220,60," ",16);	//等一下，无意义的操作
	
	/*秒中断完成后更新显示*/
	if(sec_flag){
		/*获取时间*/
		Get_RTC_Time(RTC_CNT,&Disp_Time);
		/*格式转换 XXXX/XX/XX  XX:XX:XX*/
		sprintf((char*)Date_String,"%04d/%02d/%02d",Disp_Time.year,Disp_Time.month,Disp_Time.day);
		sprintf((char*)Time_String,"%02d:%02d:%02d",Disp_Time.hour,Disp_Time.min,Disp_Time.second);
		/*显示时间*/
		Display_String(70,50,80,16,Date_String,16);
		Display_String(78,70,80,16,Time_String,16);
	}
	
}
