#include "Beep.h"

u8 BEEP_EN = 0;
/***********************************************************
	函数功能：蜂鸣器初始化
	硬件连接：Beep ：PA12
************************************************************/
void Beep_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/*开启PA时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
	/*配置相关GPIO口*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/*配置默认值*/
	GPIO_ResetBits(GPIOA, GPIO_Pin_12);
	
}

/************************************************************
	函数功能：蜂鸣器响一声
*************************************************************/
void Beep_Alarm(void)
{
	if(BEEP_EN){
		Beep = 1;
		Delay_ms(10);
		Beep = 0;
	}
}

/************************************************************/
