#include "Application.h"

/****************************相应界面激活*************************/
u8 Login_flag 								=			0;
u8 Home_flag									=			0;
u8 Menu_flag 									=			0;
u8 Newtable_flag 							=			0;
u8 Order_flag 								=			0;
u8 Reminder_flag 							=			0;
u8 AddFood_flag 							=			0;
u8 RetreatFood_flag 					=			0;
u8 Query_flag 								=			0;
u8 MMS_flag 									=			0;
u8 Settings_flag 							=			0;
u8 Settings_Time_flag 				=			1;
u8 Settings_User_flag 				=			0;
u8 Settings_LAB_flag 					=			0;
u8 Settings_About_flag 				=			0;
u8 Clear_flag 								=			0;
u8 Clear_All									=			1;
u8 Null 											= 		1;
/****************************相关数据定义***************************/
ACCOUNT_TYPE Account={"          ","          "};
ACCOUNT_TYPE DefAcc[4] ={{"123456    ","123456    "}};





/*******************************************************************
	函数功能：实时时钟
********************************************************************/
void RTC_Func(void)
{
	u8 Date_String[20];				//存放DATE数据
	u8 Time_String[20];				//存放TIME数据
	TIME_TYPE Disp_Time;			//存储时间结构体
	
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

/******************************************************************
	函数功能：按键输入处理
	参数：u8 key：外部输入的按键值
				u8 range：输入范围
				u8 *Clear_All：清除标志
	返回值：处理完之后的数据首地址
*******************************************************************/
u8 *Key_Input(u8 key, u8 range, u8 *Clear_All)
{
	static u8 i=0, Esc_flag=1;
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
	
	if(*Clear_All){
		for(i=0;i<11;i++)
			Input_Data[i] = ' ';
		i=0;
		Esc_flag=1;
		*Clear_All = 0;
	}
	
	return Input_Data;
}

/***************************************************************
	函数功能：窗口初始化
	参数：WINDOWS_INIT_TYPE windows 窗体信息
****************************************************************/
void Windows_Init(WINDOWS_INIT_TYPE windows)
{
	Clear_flag = 0;
	Clear_All = 1;
	LCD_Clear(windows.Clear_Color);
	BACK_COLOR = windows.Back_Color;
	
	LCD_DrawRecFill(0,0,220,20,LBBLUE);
	Display_String(windows.Location,3,130,16,windows.Name,16);
	
	LCD_DrawRecFill(10, 145, 60, 170,BROWN);
	Display_String(20,150,80,16,windows.Button1,16);
	
	LCD_DrawRecFill(160, 145, 210, 170,BROWN);
	Display_String(170,150,80,16,windows.Button2,16);
	
}

/************************************************************************
	函数功能：窗口贴片块
	参数：WINDOWS_TYPE t ：窗体信息， 
				u8 **show			 ：显示贴片的内容，
				u8 i					 ：横第几块
				u8 j					 ：纵第几块
				u16 color			 ：贴片颜色
*************************************************************************/
void Windows_Title(WINDOWS_TYPE t, u8 **show,u8 i, u8 j,u16 color)
{
	LCD_DrawRecFill((t.St_x+j*(t.Weight+t.Jx_x)),(t.St_y+i*(t.Hight+t.Jx_y)), 
									(t.St_x+j*(t.Weight+t.Jx_x)+t.Weight), (t.St_y+i*(t.Hight+t.Jx_y)+t.Hight),color);
	Display_String((t.St_x+j*(t.Weight+t.Jx_x)+4),(t.St_y+i*(t.Hight+t.Jx_y)+4),80,16,(u8 *)show[j+i*t.tls_x],16);	
}

/*************************************************************************
	函数功能：窗口贴片
	参数：WINDOWS_TYPE t ：窗体信息， 
				u8 **show			 ：显示贴片的内容，
				u16 color			 ：贴片颜色
**************************************************************************/
void Windows_Titles(WINDOWS_TYPE t, u8 **show,u16 color)
{
	u8 i=0,j=0;
	/*显示菜单*/
	for(i=0;i<t.tls_y;i++){
		for(j=0;j<t.tls_x;j++)
			Windows_Title(t,show,i,j,color);
	}
}

/**************************************************************************
	函数功能：
***************************************************************************/
u8 Common_Key(short *i,short *j,u8 tls_x, u8 tls_y,u8 *Old_flag, u8 *Self_flag,u8 *New_flag)
{
	u8 key;
	key = Key_Scan();
	
	/*退出*/
	if((key==KEY_ESC)&&Clear_flag==0){
		*Self_flag = 0;
		*Old_flag = 1;
	}
	/*选择*/
	if(key==KEY_WKUP){
		*Self_flag = 0;
		*New_flag = 1;
	}	
	
	/*界面上下左右选择*/
	if(key==KEY_DOWN)		*i += 1;
	if(key==KEY_UP)			*i -= 1;
	if(key==KEY_LEFT)		*j -= 1;
	if(key==KEY_RIGHT)	*j += 1;
	if(*i>tls_y-1) *i = 0;
	if(*j>tls_x-1) *j = 0;
	if(*i<0)	 *i = tls_y - 1;
	if(*j<0)	 *j = tls_x - 1;
	
	return key;
}

