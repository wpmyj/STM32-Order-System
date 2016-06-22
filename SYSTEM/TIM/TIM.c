#include "TIM.h"

/*
	函数功能：定时器输出PWM波
	参数：u32 arr：重装载值
				u32 psc：预分频值
*/
void TIM2_PWM_Init(u32 arr, u32 psc)
{
	/*开启定时器2 PA时钟*/
	RCC->APB1ENR |= 1<<0;
	RCC->APB2ENR |= 1<<2;
	GPIOA->CRL &= 0xffff0fff;			//配置PA3为复用推挽输出
	GPIOA->CRL |= 0x0000b000;
	
	/*配置TIM2控制器1*/
	TIM2->CR1 &= ~(1<<7);			//TIMx_ARR 寄存器没有缓冲，不使用影子功能
	TIM2->CR1 &= ~(1<<3);			//在发生更新事件时，计数器不停止，禁止使用单脉冲模式
	TIM2->CR1 &= ~(1<<2); 		//使能更新请求源
	TIM2->CR1 &= ~(1<<1);			//使能更新事件（UEV）

	/*配置PWM 相关寄存器*/
	TIM2->CCMR2 &= 0x00;		//清空寄存器
	TIM2->CCMR2 |= 0x64<<8;		//通道4 开启通道输出 预装载 PWM 模式1
	
	TIM2->CCER |= 0x1<<12;			//开启通道4 OC1-4信号输出到对应的输出引脚
	
	/*配置定时器2的自动重装载值和预分频系数*/
	TIM2->PSC = psc - 1;
	TIM2->ARR = arr;
	TIM2->CCR4 = arr>>1;
	
	/*开启定时器2*/
	TIM2->CR1 |= 1<<0;
	
}

