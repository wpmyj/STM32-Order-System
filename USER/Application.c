#include "Application.h"


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
		sprintf((char*)Date_String,"%d/%d/%d",Disp_Time.year,Disp_Time.month,Disp_Time.day);
		sprintf((char*)Time_String,"%d:%d:%d",Disp_Time.hour,Disp_Time.min,Disp_Time.second);
		/*显示时间*/
		Display_String(80,50,80,16,Date_String,16);
		Display_String(83,70,80,16,Time_String,16);
	}
	
}
