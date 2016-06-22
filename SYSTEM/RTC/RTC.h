#ifndef _RTC_H_
#define _RTC_H_
#include "stm32f10x.h"
#include "sys.h"
#include "USART.h"
#include "ILI9341.h"

#define year_base 2008			//年基

typedef struct{							//时间结构体
	u16 year;			//年
	u8 month;		//月
	u8 day;			//日
	u8 hour;			//时
	u8 min;			//分
	u8 second;		//秒
}TIME_TYPE;

extern 	u32 RTC_CNT;
extern  u8 sec_flag;
extern const u8 *COMPILED_DATE;//获得编译日期
extern const u8 *COMPILED_TIME;//获得编译时间

u8 RTC_Init(void);									//RTC初始化
void Set_RTC_Time(TIME_TYPE time);	//设置RTC时间
void Get_RTC_Time(u32 RTC_CNT,TIME_TYPE *time);//转换时间

u8 str_cmpx(u8*s1, u8*s2, u8 len);	//对比字符串
void Auto_Set_Time(void);						//自动设置时间

#endif
