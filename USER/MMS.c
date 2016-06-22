#include "Application.h"

void MMS_Func(void)
{
	_RF_Dat *RF_Dat;
	u8 n=0;
	
	WINDOWS_INIT_TYPE MMS_Win={94,"信息","返回","选择"};
	/*界面初始化*/
	Windows_Init(MMS_Win);	
	BACK_COLOR = Theme_Color;
	do{
	/*获取功能键值*/
	Common_Key((short *)&Null,(short *)&Null,Null,Null, &Menu_flag,&MMS_flag,&Null);
	/*查询到有信息读取信息并显示出来*/	
	if(RF_Sta.DatFlag==OK){
		 RF_Sta.DatFlag=ERR;
		 RF_Dat=(_RF_Dat *)RF_Read_Buff;
		 Display_String(10,25+(n++)*16,200,16,RF_Dat->str,16);
	 }
	 
	}while(MMS_flag);
	
}

/*
	函数功能：发送数据
	参数：u8 adr：接收器件地址
				u8 *msg：发送的信息
*/
void Send_msg(u8 adr,u8 *msg)
{
		_RF_Dat Send_Buf;
		Send_Buf.adr=adr;																	//发送地址													
		strcpy((char *)Send_Buf.str,(const char *)msg);		//复制字符串
		Send_Buf.len=sizeof(Send_Buf)-1;				//长度字节本身不计入数据总长度
		halRfSendPacket((u8 *)&Send_Buf,sizeof(Send_Buf));//发送数据
		Delay_ms(200);
}

