#include "RTC.h"

u32 RTC_CNT;
u8 sec_flag = 0;
const u8 *COMPILED_DATE = __DATE__;//获得编译日期
const u8 *COMPILED_TIME = __TIME__;//获得编译时间

/*
	函数功能：RTC初始化
*/
u8 RTC_Init(void)
{
	u16 i=0;
	
	/*如果没配置就配置,有配置就直接配置RTC->CR寄存器以允许中断*/
	if(BKP_ReadBackupRegister(BKP_DR1) != 0xaaaa){

		/*1.开启备份接口时钟，电源接口时钟*/
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP | RCC_APB1Periph_PWR, ENABLE);
		PWR_BackupAccessCmd(ENABLE);			//允许写入RTC和后备寄存器	
		
		/*2.开启备份域控制寄存器RTC*/
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);//选择LSE振荡器作为RTC时钟；
		
		/*3.等待外部低速LSE（32Khz晶振）就绪*/
		while(!RCC->BDCR &1<<1){
			i ++;
			if(i==250) return 1;
		}
		
		/*4.外部低速振荡器使能*/
		RCC_LSEConfig(RCC_LSE_ON);
		
		/*5.等待RTOFF寄存器值为1*/
		while(!(RTC->CRL&1<<5));
		
		/*6.置CNF值为1，进入配置模式*/
		RTC_EnterConfigMode();	
		
		/*7.RTC相关寄存器配置*/
		RTC->PRLH = 0;			//清除分频计数器高位
		RTC->PRLL = 0x7fff;	//配置分频计数器低位，刚好1s
		RTC_ITConfig(RTC_IT_OW|RTC_IT_SEC, ENABLE);//允许溢出中断 允许秒中断
		/*设置时间*/
		Auto_Set_Time();
		
		/*8. 清除CNF标志位，退出配置模式*/
		RTC_ExitConfigMode();		
		
		/*9. 查询RTOFF，直至RTOFF位变为’1’以确认写操作已经完成。*/
		while(!RTC->CRL&1<<5);
		
		/*10. 查询数据是否被同步*/
		while(!RTC->CRL&1<<3);

		/*11.开启RTC时钟*/
		RCC_RTCCLKCmd(ENABLE);
		/*12.向备份域寄存器1写入标志*/
		BKP_WriteBackupRegister(BKP_DR1, 0xaaaa);
	}else{
		while(!RTC->CRL&1<<5);	//等待RTOFF寄存器的值为1，等待上一次操作完成
		RTC_EnterConfigMode();	//置CNF值为1，进入配置模式
		RTC_ITConfig(RTC_IT_OW|RTC_IT_SEC, ENABLE);//允许溢出中断 允许秒中断
		RTC_ExitConfigMode();		//清除CNF标志位，退出配置模式
	}
	
	/*配置中断*/
	Set_NVIC(RTC_IRQn,2,1);
	
	return 0;
}


/*
	函数功能：RTC中断服务函数
*/
void RTC_IRQHandler(void)
{
	if(RTC_GetITStatus(RTC_IT_SEC))	//秒中断
	{
		sec_flag = 1;
		RTC_CNT = RTC_GetCounter();
	}
	RTC_ClearITPendingBit(RTC_IT_SEC);	//清除标志位
}


/*
	函数功能：设置RTC时间
	参数：TIME_DATE :时间结构体类型
*/
void Set_RTC_Time(TIME_TYPE time)
{		
		u32 second_base=0;
		u16 day_base=0;
	
		/*计算从2008年到传进来的时间的天数*/
		day_base += (time.year - year_base)*365 + (time.year - year_base)/4 
								+ (((time.year-year_base/4)&&(time.year-year_base%4))?1:0);		//年 普通年天数+多出来的闰年的次数*1天
		day_base += (time.month-1)*30 + (time.month + ((time.month>8)?1:0))/2 
								- ((time.month<3)?0:((time.year%400==0)||((time.year%4==0)&&(time.year%100))?1:2));						//月	
		day_base += time.day - 1;																																			//日
	
		/*计算总共有多少秒*/
		second_base += day_base * 24 * 3600;
		second_base += time.hour * 3600;																														//时
		second_base += time.min * 60;																															//分
		second_base += time.second;																																//秒
	
		/*开启备份接口时钟，电源接口时钟*/
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP | RCC_APB1Periph_PWR, ENABLE);
		PWR_BackupAccessCmd(ENABLE);			//允许写入RTC和后备寄存器	
	
		while(!RTC->CRL&1<<5);				//等待RTOFF上一次写操作完成
		RTC_EnterConfigMode();				//置CNF值为1，进入配置模式
		RTC_SetCounter(second_base);	//向RTC->CNT里面写入时间
		RTC_ExitConfigMode();					//清除CNF标志位，退出配置模式
	
}

/*
	函数功能：将秒为单位的时间转换为：年月日时分秒
	参数：u32 RTC_CNT
*/
void Get_RTC_Time(u32 RTC_CNT,TIME_TYPE *time)
{
		u8 month_base[12]={31,28,31,30,31,30,31,31,30,31,30,31};
		u8 i=0;
			
		sec_flag = 0;													//清除秒标志
		time->second 	=  RTC_CNT % 60;				//秒
		time->min 		= (RTC_CNT / 60)%60;		//分
		time->hour 		= (RTC_CNT / 3600)%24;	//时
		time->year 		= (RTC_CNT / (3600*24*365)) + year_base;			//计算出哪一年，模糊计算
		time->month 	= 1;
		time->day 		= (RTC_CNT / (3600*24))-((time->year-year_base)*365 + ((time->year-year_base)/4)+1);			//得到剩下一年的天数=总天数-过去几年的天数
		
		if((time->year%400==0)||((time->year%4==0)&&(time->year%100))){							//如果是闰年的话，修改数组month_base[1]为29
			month_base[1]	= 29;
			for(i=0;i<12;i++){																				//循环减12次
				if(time->day>=month_base[i]){														//大于那个月继续减
					time->day = time->day-month_base[i];
					time->month += 1;
				}
			}	
			time->day += 1;
		}else{																											//如果是平年的话，修改数组month_base[1]为28	
			month_base[1] = 28;
			for(i=0;i<12;i++){
				if(time->day>=month_base[i]){
					time->day = time->day-month_base[i] ;
					time->month += 1;
				}
			}
			time->day += 1;
		}
}


/*
	函数功能：比较两个字符串指定长度的内容是否相等
	参数:s1,s2要比较的两个字符串;len,比较长度
	返回值:1,相等;0,不相等
*/
u8 str_cmpx(u8*s1, u8*s2, u8 len)
{
  u8 i;
  for(i=0;i<len;i++){
		if((*s1++) != *s2++)
			return 0;
	}
  return 1;
}

/*
	函数功能：自动设置时间为编译器时间
*/
const u8 Month_Tab[12][3] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
void Auto_Set_Time(void)
{
    u8 month[3];
		u8 i,day,hour,min,second;
		u16 year;
		TIME_TYPE time;		
		
		/*分离字符串*/
		sscanf((char*)COMPILED_DATE,"%s%d%d",month,(int*)&day,(int*)&year);
		sscanf((char*)COMPILED_TIME,"%d:%d:%d",(int*)&hour,(int*)&min,(int*)&second);
		/*解析月份*/
    for(i=0;i<12;i++)
			if(str_cmpx((u8*)Month_Tab[i],month,3))break;
    time.month = i + 1; 			//得到月份
		/*把数值赋给time结构体*/
		time.day = day;
		time.year = year;
		time.hour = hour;
		time.min = min;
		time.second = second;
		/*测试打印时间*/
//		printf("%d %d %d\r\n%d:%d:%d\r\n",time.year,time.month,time.day,time.hour,time.min,time.second);
		/*设置时间*/
		Set_RTC_Time(time);
}


