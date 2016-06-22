#include "Application.h"

u8 Login_flag = 0;
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
u8 Settings_Time_flag = 1;
u8 Settings_User_flag = 0;
u8 Settings_LAB_flag = 0;
u8 Settings_About_flag = 0;
u8 Clear_flag = 0;

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

/*
	函数功能：按键输入处理
	参数：u8 key：外部输入的按键值
	返回值：处理完之后的数据首地址
*/
u8 *Key_Input(u8 key, u8 range)
{
	static u8 i=0,Esc_flag=1;
	static u8 Input_Data[11]="          ";
	
	/*正常获取数据*/
	if(i<range){								//输入范围
		if((key>0&&key<10))		//输入数字1-9
			Input_Data[i++] = key + 0x30;
		if(key==KEY_0)				//输入数字0
			Input_Data[i++] = '0';
		if(key==KEY_X)				//输入字符*
			Input_Data[i++] = '*';
		if(key==KEY_J)				//输入字符#
			Input_Data[i++] = '#';
	}
	
	/*清除标志位*/
	if((i==1)&&Clear_flag==0){
		LCD_DrawRecFill(10, 145, 60, 170,BROWN);//清除效果
	}	
	if(i!=0){
		Clear_flag = 1;
		Display_String(20,150,80,16,"清除",16);
	}else{
		Clear_flag = 0;
		Display_String(20,150,80,16,"取消",16);
	}

	/*清除数据*/
	if(key==KEY_ESC){				//清除键
		Esc_flag = 0;
		LCD_DrawRecFill(10, 145, 60, 170,BROWN);//清除效果
		if(i!=0)							//范围最低0
			Input_Data[--i] = ' ';
	}else if(Esc_flag==0){
		Esc_flag = 1;
	}
	
	return Input_Data;
}

