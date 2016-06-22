#include <stm32f10x.h>
#include "LED.h"
#include "Beep.h"
#include "delay.h"
#include "KEY.h"
#include "USART.h"
#include "W25Q64.h"
#include "Font.h"
#include "ILI9341.h"

/*
	函数功能：主函数
*/
int main(void)
{
	u8 hz[]="好";
	u32 addr;
	u8 hzm[32];
	
	LED_Init();			//LED灯初始化
	Beep_Init();		//蜂鸣器初始化
	KEY_Init();			//按键初始化
	Delay_Init();		//延时函数初始化
	USART1_Init(115200);	//串口初始化
	W25Q64_Init();	//存储芯片初始化	
	Font_Init();		//字库初始化
	LCD_Init();			//液晶屏初始化

//	/*烧写字库*/
//	printf("串口初始化成功！\n");
//	printf("芯片正在擦除中....\r\n");
//	FLASH_Chip_Erase();				//芯片擦除
//	printf("擦除完成！\r\n");
//	printf("请发送字库文件.....\r\n");
	
	/*验证字库*/
	addr = ((hz[0]-0xa1)*94+(hz[1]-0xa1))*32;
	FLASH_Serial_Read_Data(addr,32, hzm);
	Display_HZ(10,10,hzm,BLACK,16);
	
	while(1){
		KEY_LED = !KEY_LED;
		Delay_ms(1000);
	}
}


/*
	函数功能：串口中断服务函数
*/
void USART1_IRQHandler(void)
{
	u8 dat;
	static u32 i=0;
	if(RESET==USART_GetITStatus(USART1, USART_FLAG_RXNE)){	//接收区非空
		dat = USART_ReceiveData(USART1);			//接收字符
		FLASH_Write_Byte_Data(i++,dat);				//写入字符
	}
}

