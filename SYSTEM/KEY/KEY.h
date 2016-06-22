#ifndef _KEY_H_
#define _KEY_H_
#include <stm32f10x.h>
#include "SYS.h"
#include "delay.h"
#include "Beep.h"

/*相关IO口定义*/
#define KEY_1     1
#define KEY_2		  2
#define KEY_3		  3
#define KEY_4		  4
#define KEY_5		  5
#define KEY_6		  6
#define KEY_7		  7
#define KEY_8		  8
#define KEY_9		  9
#define KEY_X		  10
#define KEY_0		  11
#define KEY_J		  12
#define KEY_UP    13
#define KEY_DOWN  14
#define KEY_LEFT  15
#define KEY_RIGHT 16
#define KEY_ESC		17
#define KEY_WKUP	18

#define S0    PBin(0)
#define S1 		PBin(1)
#define S2 		PBin(2)
#define S3 		PBin(3)
#define S4 		PBin(4)
#define S5 		PBin(5)
#define S6 		PBin(6)
#define S7 		PBin(7)
#define S8 		PBin(8)
#define S9 		PBin(9)
#define S10 	PBin(10)
#define S11 	PBin(11)
#define S12 	PBin(12)
#define S13 	PBin(13)
#define S14 	PBin(14)
#define S15 	PBin(15)
#define S16		PCin(10)
#define S17   PAin(0)
	
/*相关函数声明*/
void KEY_Init(void);
u8 Key_Scan(void);

#endif
