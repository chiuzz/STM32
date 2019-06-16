#include "time.h"

/*
*********************************************************************
*函数名：TIM2Init
*作  用：定时器2初始化
*形  参：无
*返回值：无
*备  注：要清楚系统时钟是多少！才可以计算出定时时间
*********************************************************************
*/

extern void TIM2Init(void)
{
  TIM_TimeBaseInitTypeDef TIMBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);		//时钟使能
	
	TIMBaseStructure.TIM_Period= 50;											//理论：TIMBaseStructure.TIM_Period= 50，deltT=100*20us=1000us=1ms
	TIMBaseStructure.TIM_Prescaler=1440;    							//每1/72uS计数一次，T=1440/72=20us
	TIMBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;			//分频选择
	TIMBaseStructure.TIM_CounterMode=TIM_CounterMode_Down;//向下计数
	TIM_TimeBaseInit(TIM2,&TIMBaseStructure);							//初始化定时器配置
	TIM_ClearFlag(TIM2,TIM_IT_Update);										//清空标志位	  	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);							//定时器使能
	TIM_Cmd(TIM2,ENABLE); 																//中断使能
	
	 NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;						//
//	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;	//
//	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					//
//	 NVIC_InitStructure.NVIC_IRQChannelCmd= ENABLE;							//
	 NVIC_Init(&NVIC_InitStructure);
}

/****************TIM2 IRQ**************************
*功能：
*说明：定时2MS

**************************************************/


//u8 PUMP_1MS_CNT=0;

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
	{
		TIM_ClearFlag(TIM2,TIM_IT_Update);
//		PUMP_1MS_CNT++;
	}
}


