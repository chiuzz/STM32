/**
 * @file System_Init.c
 * @brief 
 * @author LGL
 * 0.010.1
 * @date 2015-05-04
 */

#include "System_Init.h"

void System_Init(void)
{
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//2位抢占优先级，2位相应优先级
	
	 delay_init(168);  	//时钟初始化
	
//	TIM2Init();
	
	 uart_init(115200);
	 uart3_init(19200);
  	uart4_init(57600);
	// uart5_init(9600);
}
