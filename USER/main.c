#include "Application.h"

#include "cc1101.h"
/**************************************************
	函数功能：主函数
***************************************************/
int main(void)
{
	/*硬件初始化*/
	Hardware_Init();
	/*点菜机系统数据初始化*/
	DCJ_SYSTEM_INIT();
	/*点菜机系统开始*/
	DCJ_SYSTEM_START();
}
/*************************************************/



//int main(void)
//{
//	
//	_RF_Dat *RF_Dat;
//	_RF_Dat Send_Buf;
//	u8 n=0;
//	
//	/*硬件初始化*/
//	Hardware_Init();
//	/*点菜机系统数据初始化*/
////	DCJ_SYSTEM_INIT();
////	/*点菜机系统开始*/
////	DCJ_SYSTEM_START();
//	
//	if(CC1101_Init())
//	{
//		LCD_ShowString(10,10+(n++)*18,200,16,16,"RF_Dat->adr:");
//		LCD_ShowString(10,10+(n++)*18,200,16,16,"RF_Dat->len:");
//		LCD_ShowString(10,10+(n++)*18,200,16,16,"RF_Dat->event:");
//		LCD_ShowString(10,10+(n++)*18,200,16,16,"RF_Dat->status:");
//		LCD_ShowString(10,10+(n++)*18,200,16,16,"RF_Dat->value:");
//		Open_GD0_Interrupt();
//	}		
//	else 	LCD_ShowString(50,10,200,16,16,"CC1101 RESET ERR");				
//		
//	//显示提示信息
//	POINT_COLOR=BLUE;//设置字体为蓝色
//	Send_Buf.value=0;
//	while(1){
//		if(RF_Sta.DatFlag==OK){
//			   RF_Sta.DatFlag=ERR;
//				 RF_Dat=(_RF_Dat *)RF_Read_Buff;
//         n=0; 
//			   LCD_ShowxNum(150,10+(n++)*18,RF_Dat->adr,3,16,0);//
//			   LCD_ShowxNum(150,10+(n++)*18,RF_Dat->len,3,16,0);//
//			   LCD_ShowxNum(150,10+(n++)*18,RF_Dat->event,3,16,0);//
//			   LCD_ShowxNum(150,10+(n++)*18,RF_Dat->status,3,16,0);//
//				 LCD_ShowxNum(150,10+(n++)*18,RF_Dat->value,8,16,0);//
//		 }
//		if(Key_Scan()==KEY_UP){
//				LCD_ShowString(10,10+8*18,200,16,16,"Send value:");
//				Send_Buf.len=sizeof(Send_Buf)-1;//长度字节本身不计入数据总长度
//				Send_Buf.adr=6;
//				Send_Buf.event=0xad;
//				Send_Buf.value++;  
//				LCD_ShowxNum(150,10+8*18,Send_Buf.value,3,16,0);//
//				halRfSendPacket((u8 *)&Send_Buf,sizeof(Send_Buf));
//				Delay_ms(200);
//		}  
//	}
//}


