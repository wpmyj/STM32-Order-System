#ifndef _TIM_H_
#define _TIM_H_
#include "stm32f10x.h"
#include "SYS.h"

#define LCD_BL_PWM  TIM2->CCR4

void TIM2_PWM_Init(u32 arr, u32 psc);

#endif
