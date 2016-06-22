#include "WDOG.h"

u16 W_WDG_ARR; 				//喂窗口看门狗

/*
	窗口看门狗初始化函数
	psc预分频因子的范围：0--3
	arr窗口值范围：0x7f -- 0x40
*/
void W_WDG_Init(u16 w_arr, u16 arr, u16 psc)
{
	RCC->APB1ENR |= 1<<11;			//开启窗口看门狗时钟
	WWDG->CFR = w_arr;					//配置窗口值
	WWDG->CFR |= psc<<7;				//配置时基(预分频系数) 范围0到3
	WWDG->CFR |= 1<<9;					//使能提前唤醒中断 ，开启窗口看门狗中断
	Set_NVIC(WWDG_IRQn,1,1);		//配置中断分组和优先级
	WWDG->CR = W_WDG_ARR = arr;	//配置T计数值，喂窗口看门狗
	WWDG->CR |= 1<<7;						//使能窗口看门狗
	
}

/*
	窗口看门狗中断服务函数
*/
void WWDG_IRQHandler(void)
{
	
	WWDG->CR |= W_WDG_ARR;		//喂狗
	
	WWDG->SR &= 0; 
}

