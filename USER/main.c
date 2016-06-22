#include <stm32f10x.h>
#include "Application.h"

/*
	函数功能：主函数
*/
int main(void)
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
	
	while(1){
		if(Login_flag)				Login_Func();						//登陆界面
		if(Home_flag)					Home_Func();						//主界面
		if(Menu_flag)					Menu_Func();						//菜单界面
		if(Newtable_flag) 		Newtable_Func();				//开桌界面
		if(Order_flag)				Order_Func();						//点菜界面
		if(Reminder_flag)			Reminder_Func();				//催菜界面
		if(AddFood_flag)			AddFood_Func();					//加菜界面
		if(RetreatFood_flag)	RetreatFood_Func();			//退菜界面
		if(Query_flag)				Query_Func();						//查询界面
		if(MMS_flag)					MMS_Func();							//信息界面
		if(Settings_flag)			Settings_Func();				//设置界面
	}
}

