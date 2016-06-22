#include "SYS.h"

/*
	中断分组定义
*/
#define NVIC_PriorityGroup0  7-0    // 抢占优先级 0 位 子优先级 4 位
#define NVIC_PriorityGroup1  7-1    // 抢占优先级 1 位 子优先级 3 位
#define NVIC_PriorityGroup2  7-2    // 抢占优先级 2 位 子优先级 2 位
#define NVIC_PriorityGroup3  7-3    // 抢占优先级 3 位 子优先级 1 位
#define NVIC_PriorityGroup4  7-4    // 抢占优先级 4 位 子优先级 0 位
#define NVIC_PriorityGroup		NVIC_PriorityGroup2		//实际分组定义

/*
	函数功能：初始化中断优先级和分组
	参数：
		EXTIx_IRQn ：中断线
		PreemptPriority：抢占优先级
		SubPriority：子优先级
		
	函数用法：Set_NVIC (中断线,抢占优先级,子优先级);				
		
*/
void Set_NVIC(IRQn_Type EXTIx_IRQn, u32 PreemptPriority, u32 SubPriority)
{
	u32 Priority;	//优先级编号
	
	/*NVIC配置相关函数----*/
  NVIC_SetPriorityGrouping(NVIC_PriorityGroup);									//设置分组
  Priority = NVIC_EncodePriority (NVIC_PriorityGroup, PreemptPriority, SubPriority);			//设置优先级编号 
 	NVIC_SetPriority(EXTIx_IRQn,Priority); 					//配置EXTIx中断优先级	Pxx
  NVIC_EnableIRQ(EXTIx_IRQn);               			//使能EXTIx对应中断线	Pxx
}
