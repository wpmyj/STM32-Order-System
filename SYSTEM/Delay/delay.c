#include "delay.h"

/*
	函数功能：延时函数毫秒级
	参数：timer (ms)
*/
void delay_72M_ms(u32 timer)
{
	u32 i;
	u8 j,k;
	for(i=0;i<timer;i++)
		for(j=0;j<100;j++)
			for(k=0;k<100;k++);
}

/*
	函数功能：延时函数微秒级
	参数：timer (us)
*/
void delay_72M_us(u32 timer)
{
	u8 j = 12;
	while(timer--){
		j = 6;
		while(j--);
	}
}

/*
	函数功能：定时器6延时函数初始化
*/
void Delay_Init(void)
{
	/*开始定时器6时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	
	/*复位定时器6状态*/
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM6, ENABLE);
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM6, DISABLE);
	
	/*关闭定时器6*/
	TIM_Cmd(TIM6, DISABLE);
}

/*
	函数功能：定时器6延时函数（x）ms级别
*/
void Delay_ms(u32 timer)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	/*配置相关寄存器*/
	TIM_TimeBaseStructure.TIM_Period = timer*10;
	TIM_TimeBaseStructure.TIM_Prescaler = 7200-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM6, & TIM_TimeBaseStructure);
	/*使能定时器*/
	TIM_Cmd(TIM6, ENABLE);
	while(TIM_GetCounter(TIM6)!= (timer * 10));/*等待*/
	TIM_Cmd(TIM6, DISABLE);		//关闭定时器6
}

/*
	函数功能：定时器6延时函数（x）us级别
*/
void Delay_us(u32 timer)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	/*配置相关寄存器*/
	TIM_TimeBaseStructure.TIM_Period = timer;
	TIM_TimeBaseStructure.TIM_Prescaler = 72-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM6, & TIM_TimeBaseStructure);
	/*使能定时器*/
	TIM_Cmd(TIM6, ENABLE);
	while(TIM_GetCounter(TIM6)!= timer);/*等待*/
	TIM_Cmd(TIM6, DISABLE);		//关闭定时器6
}
