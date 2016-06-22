#ifndef _APPLICATION_H_
#define _APPLICATION_H_
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

/*各项菜单全局使能标志*/
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


/*实时时钟*/
void RTC_Func(void);
/*登陆界面*/
void Login_Func(void);
u8 *Input_Scan(void);
/*主界面*/
void Home_Func(void);
/*菜单界面*/
void Menu_Func(void);
/*开桌界面*/
void Newtable_Func(void);
/*点菜界面*/
void Order_Func(void);
/*催菜界面*/
void Reminder_Func(void);
/*加菜界面*/
void AddFood_Func(void);
/*退菜界面*/
void RetreatFood_Func(void);
/*查询界面*/
void Query_Func(void);
/*信息界面*/
void MMS_Func(void);
/*设置界面*/
void Settings_Func(void);

#endif
