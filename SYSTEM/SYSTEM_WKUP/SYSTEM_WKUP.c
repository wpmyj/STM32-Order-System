#include "SYSTEM_WKUP.h"

//THUMB指令不支持汇编内联
//采用如下方法实现执行汇编指令WFI
//CHECK OK
//091209
//WFI  休眠并且在发生中断时被唤醒
__asm void WFI_SET(void)
{
    WFI;    
}

/********************************************************************
* Function   : Sys_Standby()
* Description: 进入待机模式,这玩意需要有中断唤醒
* Calls      : 
* Called By  : 
* Input      : 无
* Output     : 无
* Return     : 无
* Author     : 杨工
* Others     : 
* date of completion : 2015.09.13
* date of last modify: 2015.09.13
*********************************************************************/
void Sys_Standby(void)
{
    SCB->SCR |= 1 << 2; //使能SLEEPDEEP位 (SYS->CTRL)
    RCC->APB1ENR |= 1 << 28; //使能电源时钟
    PWR->CSR |= 1 << 8;      //设置WKUP用于唤醒
    PWR->CR |= 1 << 2;       //清除Wake-up 标志
    PWR->CR |= 1 << 1;       //PDDS置位
    WFI_SET();               //执行WFI指令
}


/*
	函数功能：开关机初始化
*/
void WKUP_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/*开启PA钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	/*关闭jtag*/
	AFIO->MAPR &= ~(0x7<<24);
	AFIO->MAPR |=  0x04<<24;
	/*配置相关GPIO口*/
	/*配置PA0*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);

	RTC_Init();		//实时时钟初始化
	Delay_Init();	//延时函数初始化.这个是延时检测的必要
}

/*
	函数功能：检查按键是否按下1.5秒
	返回值：是否按下1.5秒 0：没有 1:有
*/
u8 Check_WKUP(void)
{
	u8 i=0;
	while(1){
		if(WKUP)	i ++;
		else			return 0;	//不做任何过滤，因为，开机时，长按在进入到这个函数的时候，按键已经消抖了
												//那一开始没消抖呢，看下一句延时，误触唤醒，但会进行延时消抖了，该进入低功耗模式还是会进入
												//这里有一个问题，耗电量问题没考虑
		Delay_ms(10);				//延时检测，同时提高按键识别灵敏度，这里也算是延时消抖
		if(i>150){					//1.5秒
			i = 0;
			return 1;
		}
	}	
}

