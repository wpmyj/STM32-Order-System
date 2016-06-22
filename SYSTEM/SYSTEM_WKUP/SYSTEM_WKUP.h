#ifndef _SYSTEM_WKUP_H_
#define _SYSTEM_WKUP_H_
#include <stm32f10x.h>
#include "Delay.h"
#include "USART.h"
#include "RTC.h"
#include "string.h"
#include "stdio.h"
#include "sys.h"
#include "Debug.h"

#define WKUP  PAin(0)

void Sys_Standby(void);
void WKUP_Init(void);
u8 Check_WKUP(void);

/*用宏提高速度*/
#define ShutOFF(){\
if(Check_WKUP()){\
Sys_Standby();\
}\
}

#endif

