#ifndef _BEEP_H_
#define _BEEP_H_
#include <stm32f10x.h>
#include "SYS.h"

/*相关IO口定义*/
#define Beep	PAout(12)

/*相关函数声明*/
void Beep_Init(void);

#endif

