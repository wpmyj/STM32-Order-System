#ifndef _W25Q64_H_
#define _W25Q64_H_
#include <stm32f10x.h>
#include "SPI.h"
#include "sys.h"

/*选择芯片*/
#define 	FLASH2
#if !defined FLASH2
	#define FLASH_CS 	PCout(11)
#else
	#define FLASH_CS 	PCout(12)
#endif

/*相关函数声明*/
void W25Q64_Init(void);
void FLASH_Chip_Erase(void);
u16 Get_DeviceID(void);
u8 FlASH_Read_Byte_Data(u32 addr);
void FLASH_WriteEnable(void);
void FLASH_Check_Busy(void);
void FLASH_Sector_Erase(u32 addr);
void FLASH_Write_Byte_Data(u32 addr, u8 dat);
void FLASH_Serial_Read_Data(u32 addr, u16 len, u8 *dat);
void FLASH_Page_Write_Data(u32 addr, u16 len, u8 *dat);
void FLASH_Serial_Write_Data(u32 WriteAddr, u16 len, u8 *dat);

#endif
