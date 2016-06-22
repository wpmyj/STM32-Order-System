#include "W25Q64.h"

/*
	函数功能：W25Q64初始化
	硬件连接：PC11 ：FLASH_CS1
						PC12 ：FLASH_CS2
*/
void W25Q64_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/*开启PC时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	/*配置相关GPIO口*/
	/*PC11,PC12推挽输出*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	/*初始化SPI2接口*/
	SPI1_Init();
}

/*
	函数功能：flash芯片擦除
*/
void FLASH_Chip_Erase(void)
{
	FLASH_WriteEnable();				//芯片写使能
	FLASH_CS = 0;								//选中芯片
	SPI1_Write_Read_Byte(0xC7);	//发送芯片擦除指令
	FLASH_CS = 1;								//取消片选
	FLASH_Check_Busy();					//查忙
}

/*
	函数功能：获取设备ID
*/
u16 Get_DeviceID(void)
{
	u16 ID;
	FLASH_CS = 0;								//选中芯片
	SPI1_Write_Read_Byte(0x90);	//发送获取芯片id指令
	SPI1_Write_Read_Byte(0x00);	//发送24位地址高8位
	SPI1_Write_Read_Byte(0x00);	//发送24位地址中8位
	SPI1_Write_Read_Byte(0x00);	//发送24位地址低8位
	
	ID = SPI1_Write_Read_Byte(0x00);	//获取制造厂家ID
	ID = ID <<8 | (u16)SPI1_Write_Read_Byte(0x00);//获取设备ID
	
	FLASH_CS = 1;								//取消选中芯片
	return ID;									//返回ID
}	

/*
	函数功能：从flash里面读取一个字节数据
	参数：u32 ReadAddr 读取的地址
	返回值：读取的字节
*/
u8 FlASH_Read_Byte_Data(u32 addr)
{
	u8 dat;
	FLASH_CS = 0;												//选中芯片
	SPI1_Write_Read_Byte(0x03);					//发送读取数据指令
	
	SPI1_Write_Read_Byte(addr>>16);			//发送地址高8位
	SPI1_Write_Read_Byte(addr>>8);			//发送地址中8位
	SPI1_Write_Read_Byte(addr);					//发送地址低8位
	
	dat = SPI1_Write_Read_Byte(0x00);		//读取数据
	FLASH_CS = 1;												//取消片选
	
	return dat;													//返回数据
}

/*
	函数功能：flash芯片写使能
*/
void FLASH_WriteEnable(void)
{
	FLASH_CS = 0;			//拉低片选
	SPI1_Write_Read_Byte(0x06);	//发送写使能指令
	FLASH_CS = 1;			//拉高片选
}


/*
	函数功能：FLASH查忙
*/
void FLASH_Check_Busy(void)
{
	u8 status;
	FLASH_CS = 0;									//拉低片选
	SPI1_Write_Read_Byte(0x05);		//发送查忙指令
	do{
		status = SPI1_Write_Read_Byte(0x00);	//读状态寄存器1数值
	}while((status & 0x01)!=0);
	FLASH_CS = 1;									//拉高片选
}

/*
	函数功能：flash扇区擦除
	参数：u32 addr 地址
*/
void FLASH_Sector_Erase(u32 addr)
{
	FLASH_WriteEnable();						//写使能
	FLASH_CS = 0;										//拉低片选
	SPI1_Write_Read_Byte(0x20);			//发送扇区擦除指令
	SPI1_Write_Read_Byte(addr>>16);	//发送地址高8位
	SPI1_Write_Read_Byte(addr>>8);	//发送地址中8位
	SPI1_Write_Read_Byte(addr);			//发送地址低8位
	FLASH_CS = 1;										//拉高片选
	FLASH_Check_Busy();							//查忙
}


/*
	函数功能：向flash芯片里面写入一个字节数据
	参数：u32 addr 地址 u8 dat 数据
*/
void FLASH_Write_Byte_Data(u32 addr, u8 dat)
{
	FLASH_WriteEnable();							//写使能
	FLASH_CS = 0;											//拉低片选
	SPI1_Write_Read_Byte(0x02);				//发送页写指令
	SPI1_Write_Read_Byte(addr>>16);		//发送地址高8位
	SPI1_Write_Read_Byte(addr>>8);		//发送地址中8位
	SPI1_Write_Read_Byte(addr);				//发送地址低8位
	SPI1_Write_Read_Byte(dat);				//发送要写入的数据
	FLASH_CS = 1;											//拉高片选
	FLASH_Check_Busy();								//查忙
}


/*
	函数功能：从flash芯片里面读取任意长度数据
	参数：u32 addr 地址，u16 len 长度，u8 *dat 数据首地址
*/
void FLASH_Serial_Read_Data(u32 addr, u16 len, u8 *dat)
{
	u16 i;
	
	FLASH_CS = 0;											//拉低片选
	SPI1_Write_Read_Byte(0x03);				//发送读取指令
	SPI1_Write_Read_Byte(addr>>16);		//发送地址高8位
	SPI1_Write_Read_Byte(addr>>8);		//发送地址中8位
	SPI1_Write_Read_Byte(addr);				//发送地址低8位
	
	for(i=0;i<len;i++){								//读取数据
		dat[i] = SPI1_Write_Read_Byte(0x00);
	}
	
	FLASH_CS = 1;											//拉高片选
}

/*
	函数功能：向FLASH芯片里面写入数据 一个页
	参数：u32 addr 地址 u16 len 字节数量 u8 *dat 接收数据首地址
*/
void FLASH_Page_Write_Data(u32 addr, u16 len, u8 *dat)
{
	u16 i;
	FLASH_WriteEnable();							//写使能
	FLASH_CS = 0;											//拉低片选
	SPI1_Write_Read_Byte(0x02);				//发送页写指令
	SPI1_Write_Read_Byte(addr>>16);		//发送地址高8位
	SPI1_Write_Read_Byte(addr>>8);		//发送地址中8位
	SPI1_Write_Read_Byte(addr);				//发送地址低8位
	
	for(i=0;i<len;i++){
		SPI1_Write_Read_Byte(dat[i]);		//发送要写入的数据
	}
	
	FLASH_CS = 1;											//拉高片选
	FLASH_Check_Busy();								//查忙
}

/*
	函数功能：向FLASH芯片里面任意地址写入任意长度的数据
	参数：u32 addr 地址 u16 len 字节数量 u8 *dat 接收数据首地址
*/
void FLASH_Serial_Write_Data(u32 WriteAddr, u16 len, u8 *dat)
{
	u16 i=0;
	u16 num=0;
	
	num = 0xff - (u8)WriteAddr + 1;			//算这一页剩下多少可写的字节
	if(num>=len){												//剩下能写字节空间大于等于长度时直接调用页写
		FLASH_Page_Write_Data(WriteAddr,len,dat);		
	}else{															//字节空间长度小于长度时
		/*开始不足一页的部分*/													
		FLASH_Page_Write_Data(WriteAddr,num,dat);		//把这一页写完
		len -= num;													//长度减去写去的长度
		WriteAddr += num;										//地址加写去的长度
		dat += num;													//数据指针指向写去的字节的下一位字节
		/*连续完整一页部分*/
		while(len>256){
			FLASH_Page_Write_Data(WriteAddr, 256, dat);		//连续写完一个页
			len -= 256;																		//数量长度减去一个页的数量
			i ++;																					//这个是用来计算多少个完整页
			WriteAddr += i*256;														//地址加一个页
			dat += i*256;																	//数据地址加一个页
		}
		/*剩下不足一页的部分*/
		FLASH_Page_Write_Data(WriteAddr,len,dat);
	}
}


