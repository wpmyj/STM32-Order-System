#ifndef _APPLICATION_H_
#define _APPLICATION_H_
/***************************各项头文件***********************************/
#include <stm32f10x.h>
#include "sys.h"
#include "LED.h"
#include "Beep.h"
#include "delay.h"
#include "KEY.h"
#include "USART.h"
#include "W25Q64.h"
#include "Font.h"
#include "ILI9341.h"
#include "RTC.h"
#include "string.h"
#include "Debug.h"
#include "TIM.h"
/*****************************定义类型***********************************/
/*****************************用户管理***********************************/
typedef struct{
	u8 *User;
	u8 *Passwd;
}ACCOUNT_TYPE;

/*****************************点菜部分***********************************/
typedef struct{
	u8 Table;
	u8 *Food;
	u8 *Num;
}CUSTOMER_TYPE;

/*****************************菜单部分***********************************/
typedef struct{
	u8 **Food;
	u8 **Num;
}LIST_TYPE;

/*****************************窗体信息***********************************/
typedef struct{
	u8 St_x;				//起始x位置
	u8 St_y;				//起始y位置
	u8 Weight;			//宽
	u8 Hight;				//高
	u8 Jx_x;				//横间隙
	u8 Jx_y;				//纵间隙
	u8 tls_x;				//窗口贴片横数量
	u8 tls_y;				//窗口贴片纵数量
}WINDOWS_TYPE;

/**************************窗体初始化信息********************************/
typedef struct{
	u16 Clear_Color;
	u16 Back_Color;
	u8 Location;
	u8 *Name;
	u8 *Button1;
	u8 *Button2;
}WINDOWS_INIT_TYPE;

/****************************各项菜单全局使能标志***********************/
extern u8 Login_flag;
extern u8 Home_flag;
extern u8 Menu_flag;
extern u8 Newtable_flag;
extern u8 Order_flag;
extern u8 Reminder_flag;
extern u8 AddFood_flag;
extern u8 RetreatFood_flag;
extern u8 Query_flag;
extern u8 MMS_flag;
extern u8 Settings_flag;
extern u8 Settings_Time_flag;
extern u8 Settings_User_flag;
extern u8 Settings_LAB_flag;
extern u8 Settings_About_flag;
extern u8 Message_Warming_flag;
extern u8 Clear_flag;
extern u8 Clear_All;
extern u8 Null;
extern u8 LCD_BL_LIGHT;
extern ACCOUNT_TYPE Account;
extern ACCOUNT_TYPE DefAcc;
extern CUSTOMER_TYPE COUSTOMER;
/*****************************数据存储地址*******************************/
#define DATA_BASE								(0x050000)
#define BEEP_EN_Addr						(0x00+DATA_BASE)
#define KEY_LED_EN_Addr					(0x10+DATA_BASE)
#define LCD_BL_Addr							(0x20+DATA_BASE)
#define USER_Addr								(0x30+DATA_BASE)
#define PASSWD_Addr							(0x40+DATA_BASE)

/*****************************函数声明***********************************/
void Hardware_Init(void);								/*硬件部分初始化*/						
void DCJ_SYSTEM_INIT(void);							/*点菜机系统数据初始化*/
void DCJ_SYSTEM_START(void);						/*点菜机系统开始*/
void SAVE_Data(void);										/*保存数据*/
void Login_Func(void);									/*登陆界面*/						
void Home_Func(void);										/*主界面*/							
void Menu_Func(void);										/*菜单界面*/						
void Newtable_Func(void);								/*开桌界面*/								
void Order_Func(void);									/*点菜界面*/						
void Reminder_Func(void);								/*催菜界面*/									
void AddFood_Func(void);								/*加菜界面*/								
void RetreatFood_Func(void);						/*退菜界面*/									
void Query_Func(void);									/*查询界面*/							
void MMS_Func(void);										/*信息界面*/					
void Settings_Func(void);								/*设置界面*/								
void Settings_Time_Func(void);					/*设置界面--设置时间*/										
void Settings_User_Func(void);					/*设置界面--用户管理*/											
void Settings_LAB_Func(void);						/*设置界面--背光及声音*/									
void Settings_About_Func(void);					/*设置界面--关于*/											
void RTC_Func(void);										/*实时时钟*/	
void Message_Warming_Func(u8 *Old_flag, u8 *New_flag, u8 *Str);		/*信息提示界面*/

/*******************************输入相关函数*******************************/
u8 *Input_Scan(void);																								//按键输入不带范围
u8 *Key_Input(u8 key, u8 range, u8 *Clear_All);											//按键输入带范围
void Key_Input1(u8 x1,u8 y1,u8 x2,u8 y2,u8 key,u8 range,u8 *str);
u8 Common_Key(short *i,short *j,u8 tls_x, u8 tls_y,u8 *Old_flag, u8 *Self_flag,u8 *New_flag);	//功能键

/*******************************界面相关函数********************************/
void Windows_Init(WINDOWS_INIT_TYPE windows);												//窗体初始化
void Windows_Title(WINDOWS_TYPE t, u8 **show,u8 i, u8 j,u16 color);	//窗口贴片块
void Windows_Titles(WINDOWS_TYPE t, u8 **show,u16 color);						//窗口贴片

/********************************获取桌子号*********************************/
u16 Get_Table_Func(u8 *Old_flag, u8 *Self_flag, u8 *New_flag,u8 *name,u8 *show,u8 *warming);

#endif
