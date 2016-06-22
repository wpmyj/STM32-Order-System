#include <stm32f10x.h>
#include "Application.h"

/*
	函数功能：主函数
*/
int main(void)
{
	/*硬件初始化*/
	Hardware_Init();
	/*点菜机系统初始化*/
	DCJ_SYSTEM_INIT();
}

