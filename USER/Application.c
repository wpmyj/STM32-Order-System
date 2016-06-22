#include "Application.h"

/****************************相应界面激活*************************/
u8 Login_flag 								=			1;						//登陆界面
u8 Home_flag									=			0;						//主界面  
u8 Menu_flag 									=			0;						//菜单界面
u8 Newtable_flag 							=			0;						//开桌界面
u8 Order_flag 								=			0;						//点菜界面
u8 Reminder_flag 							=			0;						//催菜界面
u8 AddFood_flag 							=			0;						//加菜界面
u8 RetreatFood_flag 					=			0;						//退菜界面
u8 Query_flag 								=			0;						//查询界面
u8 MMS_flag 									=			0;						//信息界面
u8 Settings_flag 							=			0;						//设置界面
u8 Settings_Time_flag 				=			0;						//设置界面---时间设置
u8 Settings_Theme_flag 				=			0;						//设置界面---用户管理
u8 Settings_LAB_flag 					=			0;						//设置界面---背光及声音
u8 Settings_About_flag 				=			0;						//设置界面---关于
u8 Message_Warming_flag				=			0;						//提示信息界面

/*****************************主题相关*****************************/
u16 Theme_Color 							= 		GBLUE;				//主题清屏色
u16 Theme_BACK  							= 		LBBLUE;				//主题背景色
u16 Theme_SLE 								= 		CYAN;					//主题选择色

/****************************相关数据定义***************************/
ACCOUNT_TYPE DefAcc ={"123456","123456"};					//默认用户
CUSTOMER_TYPE COUSTOMER;													//顾客

/************************	*点菜系统相关数据************************/
u8 LCD_BL_LIGHT								=			10;						//点菜机LCD显示屏亮度级别
u8 Clear_flag 								=			0;						//清除标志 当Clear_flag = 1 时，可清除；为0时，不可清除；
u32 Null 											= 		1;						//无效操作空间

/*******************************************************************
	函数功能：硬件初始化
********************************************************************/
void Hardware_Init(void)
{
	LED_Init();												//LED灯初始化
	Beep_Init();											//蜂鸣器初始化
	KEY_Init();												//按键初始化
	Delay_Init();											//延时函数初始化
	#ifdef Debug
		USART1_Init(115200);						//串口初始化
	#endif
	W25Q64_Init();										//存储芯片初始化
	Font_Init();											//字库初始化	
	LCD_Init();												//液晶屏初始化
	RTC_Init();												//实时时钟初始化
	TIM2_PWM_Init(100,720);						//定时器2PWM波输出初始化

	if(CC1101_Init())									//初始化433模块
	{
		Open_GD0_Interrupt();
	}		
	else 	LCD_ShowString(50,10,200,16,16,"CC1101 RESET ERR");		
}

/*******************************************************************
	函数功能：SYSTEM数据初始化

********************************************************************/
void DCJ_SYSTEM_INIT()
{
	#ifdef Debug_Save
		u8 i;
		u8 tmp[10]={0};
	#endif
	Delay_ms(100);																		//等待系统稳定
	/*判断系统是否第一次使用*/
	FlASH_Read_Byte_Data(FIRST_USE);									//无意义的操作，第一个不稳 丢掉		
	if(FlASH_Read_Byte_Data(FIRST_USE)!=0xaa){
		FLASH_Sector_Erase(FIRST_USE);									//不要乱擦除扇区
		FLASH_Write_Byte_Data(FIRST_USE,0xaa);					//第一次使用写个标志0xaa
	}else{	
		/*获取数据并还原数据*/
		Theme_Color = (u16)FlASH_Read_Byte_Data(Theme_Addr+0)<<8 | FlASH_Read_Byte_Data(Theme_Addr+1) ;
		Theme_BACK  = (u16)FlASH_Read_Byte_Data(Theme_Addr+2)<<8 | FlASH_Read_Byte_Data(Theme_Addr+3) ;
		Theme_SLE   = (u16)FlASH_Read_Byte_Data(Theme_Addr+4)<<8 | FlASH_Read_Byte_Data(Theme_Addr+5) ;
		
		#ifdef Debug_Save
			FLASH_Serial_Read_Data(Theme_Addr, 6, tmp);
			for(i=0;i<6;i++){
				printf("%X ",tmp[i]);
			}
			printf("Color:%X,Back:%X,SLE:%X\r\n",Theme_Color,Theme_BACK,Theme_SLE);
		#endif
		
		BEEP_EN = FlASH_Read_Byte_Data(BEEP_EN_Addr);				//获取蜂鸣器状态
		KEY_LED = FlASH_Read_Byte_Data(KEY_LED_EN_Addr);		//获取键盘灯状态
		LCD_BL_LIGHT = FlASH_Read_Byte_Data(LCD_BL_Addr);		//获取屏幕亮度级别
		LCD_BL_PWM = LCD_BL_LIGHT *5;												//还原屏幕亮度
	}
}
/*******************************************************************
	函数功能：SYSTEM数据保存

********************************************************************/
void SAVE_Data(void)
{
	FLASH_Sector_Erase(FIRST_USE);										//不要乱擦除扇区
	FLASH_Write_Byte_Data(FIRST_USE,0xaa);					
	FLASH_Write_Byte_Data(BEEP_EN_Addr,BEEP_EN);
	FLASH_Write_Byte_Data(KEY_LED_EN_Addr,KEY_LED);
	FLASH_Write_Byte_Data(LCD_BL_Addr,LCD_BL_LIGHT);
	FLASH_Write_Byte_Data(Theme_Addr+0,Theme_Color>>8);
	FLASH_Write_Byte_Data(Theme_Addr+1,Theme_Color);
	FLASH_Write_Byte_Data(Theme_Addr+2,Theme_BACK>>8);
	FLASH_Write_Byte_Data(Theme_Addr+3,Theme_BACK);
	FLASH_Write_Byte_Data(Theme_Addr+4,Theme_SLE>>8);
	FLASH_Write_Byte_Data(Theme_Addr+5,Theme_SLE);
}
/*******************************************************************
	函数功能：SYSTEM_BACK
********************************************************************/
void DCJ_SYSTEM_BACK(void)
{
	if(
		Login_flag 							==	0 &&
		Home_flag  							==	0 &&
		Menu_flag  							==	0 &&
		Newtable_flag						==	0	&&
		Order_flag 							==	0 &&
		Reminder_flag 					==	0 &&
		AddFood_flag 						==	0 &&
		RetreatFood_flag			  ==	0 &&
		Query_flag							==	0 &&
		MMS_flag 								==	0	&&
		Settings_flag						==	0	&&
		Settings_Time_flag			==	0	&&
		Settings_Theme_flag			==	0	&&
		Settings_LAB_flag				==	0	&&
		Settings_About_flag			==	0	&&
		Message_Warming_flag		==	0	
	)
	{
		Home_Func();															//系统跑偏了回归主菜单
	}
}

/*******************************************************************
	函数功能：SYSTEM开始	
********************************************************************/
void DCJ_SYSTEM_START(void)
{
	while(1){
		if(Login_flag)						Login_Func();								//登陆界面
		if(Home_flag)							Home_Func();								//主界面
		if(Menu_flag)							Menu_Func();								//菜单界面
		if(Newtable_flag) 				Newtable_Func();						//开桌界面
		if(Order_flag)						Order_Func();								//点菜界面
		if(Reminder_flag)					Reminder_Func();						//催菜界面
		if(AddFood_flag)					AddFood_Func();							//加菜界面
		if(RetreatFood_flag)			RetreatFood_Func();					//退菜界面
		if(Query_flag)						Query_Func();								//查询界面
		if(MMS_flag)							MMS_Func();									//信息界面
		if(Settings_flag)					Settings_Func();						//设置界面
		if(Settings_Time_flag)		Settings_Time_Func();				//设置界面--设置时间
		if(Settings_Theme_flag)		Settings_Theme_Func();			//设置界面--主题设置
		if(Settings_LAB_flag)			Settings_LAB_Func();				//设置界面--背光及声音
		if(Settings_About_flag)		Settings_About_Func();			//设置界面--关于
		DCJ_SYSTEM_BACK();																		//系统跑偏了回归主菜单
	}
}

/*******************************************************************
	函数功能：实时时钟
********************************************************************/
void RTC_Func(void)
{
	u8 Date_String[10];				//存放DATE数据
	u8 Time_String[10];				//存放TIME数据
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
	if(*i>tls_y-1) 			*i = 0;
	if(*j>tls_x-1)			*j = 0;
	if(*i<0)					 	*i = tls_y - 1;
	if(*j<0)	 					*j = tls_x - 1;
	
	return key;
}

/******************************************************************
	函数功能：按键输入处理
	参数：u8 key：外部输入的按键值
				u8 range：输入范围
				u8 *Clear_All：清除标志
	返回值：处理完之后的数据首地址
*******************************************************************/
u8 *Key_Input(u8 key, u8 range)
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
		LCD_DrawRecFill(10, 145, 60, 170,Theme_BACK);//清除效果
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
		LCD_DrawRecFill(10, 145, 60, 170,Theme_BACK);//清除效果
		if(i!=0)							//范围最低0
			Input[--i] = ' ';
	}else if(Esc_flag==0){
		Esc_flag = 1;
	}
	
	#ifdef Debug_Input
	printf("key:%d,i:%d,Clear_flag:%d,Input_Data:%s\r\n",key,i,Clear_flag,Input);
	#endif
	
	return Input;
}

/******************************************************************
	函数功能：按键输入处理
	参数：WINDOWS_TYPE t：窗体信息
				u8 x：窗体贴片横第几块
				u8 y：窗体贴片纵第几块
				u8 key：  外部输入的按键值
				u8 range：输入范围
				u8 *str： 处理完获取的字符
	返回值：处理完之后的数据首地址
*******************************************************************/
void Key_Input_Str(WINDOWS_TYPE t,u8 x,u8 y,u8 key,u8 range,u8 *str)
{
	static u8 Esc_flag=1;
	u8 i=strlen((const char *)str);

	BACK_COLOR = Theme_BACK;
	
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
		LCD_DrawRecFill(10, 145, 60, 170,Theme_BACK);//清除效果
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
		LCD_DrawRecFill(10, 145, 60, 170,Theme_BACK);//清除键效果
		LCD_DrawRecFill((t.St_x+y*(t.Weight+t.Jx_x)),												//x1
										(t.St_y+x*(t.Hight+t.Jx_y)), 												//y1
										(t.St_x+y*(t.Weight+t.Jx_x)+t.Weight),							//x2
										(t.St_y+x*(t.Hight+t.Jx_y)+t.Hight),								//y2
										 Theme_SLE);
		if(i!=0)	str[--i] = '\0';									//范围最低0
		
	}else if(Esc_flag==0){
		Esc_flag = 1;
	}
	
}


/***************************************************************
	函数功能：带窗体显示字符串
	参数：WINDOWS_INIT_TYPE windows 窗体信息
				u8 x：横第几块窗体
				u8 y：纵第几块窗体
				u8 *show：显示的字符串
				u16 color：显示窗体的颜色
****************************************************************/
void DispStr_Win(WINDOWS_TYPE t,u8 x,u8 y,u8 *show,u16 color)
{
	BACK_COLOR = color;
	LCD_DrawRecFill((t.St_x+y*(t.Weight+t.Jx_x)),								//x1 
									(t.St_y+x*(t.Hight+t.Jx_y)), 								//y1
									(t.St_x+y*(t.Weight+t.Jx_x)+t.Weight), 			//x2
									(t.St_y+x*(t.Hight+t.Jx_y)+t.Hight),color);	//y2
	Display_String((t.St_x+y*(t.Weight+t.Jx_x)+4),(t.St_y+x*(t.Hight+t.Jx_y)+4),88,16,show,16);					//显示字符串
}

/***************************************************************
	函数功能：窗口初始化
	参数：WINDOWS_INIT_TYPE windows 窗体信息
****************************************************************/
void Windows_Init(WINDOWS_INIT_TYPE windows)
{
	/*初始化一些相关参数*/
	Clear_flag = 0;
	LCD_Clear(Theme_Color);
	BACK_COLOR = Theme_BACK;
	/*画状态栏*/
	LCD_DrawRecFill(0,0,220,20,Theme_BACK);
	Display_String(windows.Location,3,130,16,windows.Name,16);
	/*画按键1*/
	LCD_DrawRecFill(10, 145, 60, 170,Theme_BACK);
	Display_String(20,150,80,16,windows.Button1,16);
	/*画按键2*/
	LCD_DrawRecFill(160, 145, 210, 170,Theme_BACK);
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
	WINDOWS_INIT_TYPE Msg_Win={94,"提示"," 否"," 是"};
	/*窗口初始化*/
	Windows_Init(Msg_Win);	
	LCD_DrawRecFill(50, 50, 170, 96,Theme_BACK);
	Display_String(70,60,170,96,Str,16);

	do{
		/*获取功能键值*/
		Common_Key((short *)&Null,(short *)&Null,Null,Null,Old_flag,&Message_Warming_flag,New_flag);
		
	}while(Message_Warming_flag);
	
}

/********************************END****************************************/

