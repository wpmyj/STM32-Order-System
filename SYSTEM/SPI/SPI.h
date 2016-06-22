#ifndef _SPI_H_
#define _SPI_H_
#include <stm32f10x.h>

void SPI1_Init(void);
u8 SPI1_Write_Read_Byte(u8 Write_Dat);

#endif
