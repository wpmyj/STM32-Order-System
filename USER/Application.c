#include "Application.h"

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

/**************************************************************************
	函数功能：通用功能按键
	参数：short *i: 上下键
				short *j:	左右键
				u8 tls_x:左右范围
				u8 tls_y:上下范围
				u8 *Old_flag:老界面标志
				u8 *Self_flag:自己界面标志
				u8 *New_flag:新界面标志
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

/******************************************************************
	函数功能：按键输入处理
	参数：u8 key：外部输入的按键值
				u8 range：输入范围
				u8 *Clear_All：清除标志
	返回值：处理完之后的数据首地址
*******************************************************************/
u8 *Key_Input(u8 key, u8 range, u8 *Clear)
{
	static u8 i=0, Esc_flag=1;
	static u8 Input[11]="           ";	
	
	/*正常获取数据*/
	if(i<range){								//输入范围
		if((key>0&&key<10))		//输入数字1-9
			Input[i++] = key + 0x30;
		if(key==KEY_0)				//输入数字0
			Input[i++] = '0';
		if(key==KEY_X)				//输入字符*
			Input[i++] = '*';
		if(key==KEY_J)				//输入字符#
			Input[i++] = '#';
	}
	
	/*清除标志位*/
	if((i==1)&&Clear_flag==0){
		LCD_DrawRecFill(10, 145, 60, 170,LBBLUE);//清除效果
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
		LCD_DrawRecFill(10, 145, 60, 170,LBBLUE);//清除效果
		if(i!=0)							//范围最低0
			Input[--i] = ' ';
	}else if(Esc_flag==0){
		Esc_flag = 1;
	}
	
	/*清除全部内容*/
	if(*Clear){
		for(i=0;i<11;i++)
			Input[i] = ' ';
		i=0;
		Esc_flag=1;
		*Clear = 0;
		LCD_DrawRecFill(10, 145, 60, 170,LBBLUE);//清除效果
	}
	
	#ifdef Debug_Input
	printf("key:%d,i:%d,Clear_flag:%d,*Clear_All:%d,Input_Data:%s\r\n",key,i,Clear_flag,*Clear,Input);
	#endif
	
	return Input;
}


void Key_Input1(u8 x1,u8 y1,u8 x2,u8 y2,u8 key,u8 range,u8 *str)
{
	static u8 Esc_flag=1;
	u8 i=strlen((const char *)str);

	#ifdef Debug_Input
		printf("str:%s\r\ni:%d\r\n",str,i);
	#endif
	
	/*正常获取数据*/
	if(i<range){						//输入范围
		if((key>0&&key<10))		//输入数字1-9
			str[i++] = key + 0x30;
		if(key==KEY_0)				//输入数字0
			str[i++] = '0';
		if(key==KEY_X)				//输入字符*
			str[i++] = '*';
		if(key==KEY_J)				//输入字符#
			str[i++] = '#';
	}
	
	/*清除标志位*/
	if((i==1)&&Clear_flag==0){
		LCD_DrawRecFill(10, 145, 60, 170,LBBLUE);//清除效果
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
		LCD_DrawRecFill(10, 145, 60, 170,LBBLUE);//清除效果
		LCD_DrawRecFill(x1,y1,x2,y2,CYAN);
		if(i!=0)							//范围最低0
			str[--i] = '\0';
	}else if(Esc_flag==0){
		Esc_flag = 1;
	}
	
}


/***************************************************************
	函数功能：窗口初始化
	参数：WINDOWS_INIT_TYPE windows 窗体信息
****************************************************************/
void Windows_Init(WINDOWS_INIT_TYPE windows)
{
	/*初始化一些相关参数*/
	Clear_flag = 0;
	Clear_All = 1;
	LCD_Clear(windows.Clear_Color);
	BACK_COLOR = windows.Back_Color;
	/*画状态栏*/
	LCD_DrawRecFill(0,0,220,20,LBBLUE);
	Display_String(windows.Location,3,130,16,windows.Name,16);
	/*画按键1*/
	LCD_DrawRecFill(10, 145, 60, 170,LBBLUE);
	Display_String(20,150,80,16,windows.Button1,16);
	/*画按键2*/
	LCD_DrawRecFill(160, 145, 210, 170,LBBLUE);
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
	BACK_COLOR = color;
	LCD_DrawRecFill((t.St_x+j*(t.Weight+t.Jx_x)),(t.St_y+i*(t.Hight+t.Jx_y)), 
									(t.St_x+j*(t.Weight+t.Jx_x)+t.Weight), (t.St_y+i*(t.Hight+t.Jx_y)+t.Hight),color);
	Display_String((t.St_x+j*(t.Weight+t.Jx_x)+4),(t.St_y+i*(t.Hight+t.Jx_y)+4),160,16,(u8 *)show[j+i*t.tls_x],16);	
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

/***************************************************************************
	函数功能：信息提示框
	参数：u8 *Old_flag：老的界面标志；
				u8 *New_flag：新的界面标志；
				u8 *Str：提示内容；
****************************************************************************/
void Message_Warming_Func(u8 *Old_flag,u8 *New_flag, u8 *Str)
{
	WINDOWS_INIT_TYPE Msg_Win={LIGHTBLUE,LBBLUE,94,"提示"," 否"," 是"};
	/*窗口初始化*/
	Windows_Init(Msg_Win);	
	LCD_DrawRecFill(50, 50, 170, 96,LBBLUE);
	Display_String(70,60,170,96,Str,16);

	do{
		/*获取功能键值*/
		Common_Key((short *)&Null,(short *)&Null,Null,Null,Old_flag,&Message_Warming_flag,New_flag);
		
	}while(Message_Warming_flag);
	
}


/********************************************************************************/

