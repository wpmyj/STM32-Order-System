#ifndef _DELAY_H_
#define _DELAY_H_
#include "stm32f10x.h"

void delay_72M_ms(u32 timer);	//—” ±ms
void delay_72M_us(u32 timer);	//—” ±us

void Delay_Init(void);
void Delay_ms(u32 timer);
void Delay_us(u32 timer);

#endif
