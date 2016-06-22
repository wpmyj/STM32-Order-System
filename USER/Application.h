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

/*实时时钟*/
void RTC_Func(void);
/*登陆界面*/
void Login_Func(void);
u8 *Input_Scan(void);
/*主界面*/
void Home_Func(void);


#endif
