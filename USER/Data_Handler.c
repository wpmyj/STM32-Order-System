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
u8 Settings_User_flag 				=			0;						//设置界面---用户管理
u8 Settings_LAB_flag 					=			0;						//设置界面---背光及声音
u8 Settings_About_flag 				=			0;						//设置界面---关于
u8 Message_Warming_flag				=			0;						//提示信息界面
/************************	*点菜系统相关数据************************/
u8 LCD_BL_LIGHT								=			10;						//点菜机LCD显示屏亮度级别
u8 Clear_flag 								=			0;						//清除标志 当Clear_flag = 1 时，可清除；为0时，不可清除；
u8 Clear_All									=			1;						//全局清除标志，
u8 Null 											= 		1;						//无效操作空间
/****************************相关数据定义***************************/

ACCOUNT_TYPE DefAcc ={"123456    ","123456    "};

/*******************************************************************
	函数功能：硬件初始化
********************************************************************/
void Hardware_Init(void)
{
	LED_Init();			//LED灯初始化
	Beep_Init();		//蜂鸣器初始化
	KEY_Init();			//按键初始化
	Delay_Init();		//延时函数初始化
	USART1_Init(115200);	//串口初始化
	W25Q64_Init();	//存储芯片初始化
	Font_Init();		//字库初始化	
	LCD_Init();			//液晶屏初始化
	RTC_Init();			//实时时钟初始化
	TIM2_PWM_Init(100,720);//定时器2PWM波输出初始化
}


/*******************************************************************
	函数功能：SYSTEM数据初始化

********************************************************************/
void DCJ_SYSTEM_INIT()
{
	Delay_ms(10);																			//等待系统稳定
	/*获取数据并还原数据*/
	BEEP_EN = FlASH_Read_Byte_Data(BEEP_EN_Addr);				//获取蜂鸣器状态
	KEY_LED = FlASH_Read_Byte_Data(KEY_LED_EN_Addr);		//获取键盘灯状态
	LCD_BL_LIGHT = FlASH_Read_Byte_Data(LCD_BL_Addr);		//获取屏幕亮度级别
	LCD_BL_PWM = LCD_BL_LIGHT *5;												//还原屏幕亮度
	
//	FLASH_Sector_Erase(USER_Addr);
//	FLASH_Serial_Write_Data(USER_Addr, 10, "123456   ");
//	FLASH_Serial_Write_Data(PASSWD_Addr, 10, "123456   ");
//	FLASH_Serial_Read_Data(USER_Addr, 10, DefAcc.User);	//获取用户名
//	FLASH_Serial_Read_Data(PASSWD_Addr, 10, DefAcc.Passwd);	//获取用户名
}

void SAVE_Data(void)
{
	FLASH_Sector_Erase(BEEP_EN_Addr);		//不要乱擦除扇区
	FLASH_Sector_Erase(KEY_LED_EN_Addr);
	FLASH_Sector_Erase(LCD_BL_Addr);
	FLASH_Write_Byte_Data(BEEP_EN_Addr,BEEP_EN);
	FLASH_Write_Byte_Data(KEY_LED_EN_Addr,KEY_LED);
	FLASH_Write_Byte_Data(LCD_BL_Addr,LCD_BL_LIGHT);
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
		if(Settings_User_flag)		Settings_User_Func();				//设置界面--用户管理
		if(Settings_LAB_flag)			Settings_LAB_Func();				//设置界面--背光及声音
		if(Settings_About_flag)		Settings_About_Func();			//设置界面--关于
	}
}

