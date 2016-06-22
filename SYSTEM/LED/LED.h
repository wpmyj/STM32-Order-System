#ifndef _LED_H_
#define _LED_H_
#include <stm32f10x.h>
#include "SYS.h"

/*相关IO口定义*/
#define KEY_LED  PAout(2)
#define LCD_BL   PAout(3)


/*函数声明*/
void LED_Init(void);

#endif

