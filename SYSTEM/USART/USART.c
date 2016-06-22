#include "USART.h"

/*
	函数功能：串口初始化
	硬件连接： TX ：PA9
						 RX ：PA10
*/
void USART1_Init(u32 baud)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	/*开启相关时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
	/*配置相关GPIO口*/
	/*PA9复用推挽输出*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/*PA10浮空输入*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/*配置串口相关寄存器*/
	USART_InitStructure.USART_BaudRate = baud;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART1, &USART_InitStructure);
	/*设置中断*/
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	Set_NVIC(USART1_IRQn,2,2);
	/*使能串口*/
	USART_Cmd(USART1, ENABLE);
	
}

/*
	函数功能：重写putc函数,主要是为了实现printf函数
	函数原型：
	extern _ARMABI int fputc(int \*c*\, FILE * \*stream*\) __attribute__((__nonnull__(2)));
	在“stdio.h”文件第618行
*/
int fputc(int c,FILE *file)
{
	USART_SendData(USART1, c);								//发送数据
	while(RESET==USART_GetFlagStatus(USART1, USART_FLAG_TXE));	//等待发送完成
	return c;											//返回发送的字符
}

/*
	函数功能：重写getc函数，主要是为了实现scanf函数
	函数原型;
	extern _ARMABI int fgetc(FILE * \*stream*\) __attribute__((__nonnull__(1)));
	在“stdio.h”文件第594行
*/
int fgetc(FILE *file)
{
	while(RESET==USART_GetFlagStatus(USART1, USART_FLAG_RXNE));	//等待接收区非空
	return USART_ReceiveData(USART1);						//返回接收区数据
}


///*
//	函数功能：串口中断服务函数
//*/
//void USART1_IRQHandler(void)
//{
//	u16 dat;
//	if(RESET==USART_GetITStatus(USART1, USART_FLAG_RXNE))
//		dat = USART_ReceiveData(USART1);
//	if(RESET==USART_GetITStatus(USART1, USART_FLAG_TXE))
//		USART_SendData(USART1, dat);
//}

