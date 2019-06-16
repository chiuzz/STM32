#include "time.h"

/*
*********************************************************************
*��������TIM2Init
*��  �ã���ʱ��2��ʼ��
*��  �Σ���
*����ֵ����
*��  ע��Ҫ���ϵͳʱ���Ƕ��٣��ſ��Լ������ʱʱ��
*********************************************************************
*/

extern void TIM2Init(void)
{
  TIM_TimeBaseInitTypeDef TIMBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);		//ʱ��ʹ��
	
	TIMBaseStructure.TIM_Period= 50;											//���ۣ�TIMBaseStructure.TIM_Period= 50��deltT=100*20us=1000us=1ms
	TIMBaseStructure.TIM_Prescaler=1440;    							//ÿ1/72uS����һ�Σ�T=1440/72=20us
	TIMBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;			//��Ƶѡ��
	TIMBaseStructure.TIM_CounterMode=TIM_CounterMode_Down;//���¼���
	TIM_TimeBaseInit(TIM2,&TIMBaseStructure);							//��ʼ����ʱ������
	TIM_ClearFlag(TIM2,TIM_IT_Update);										//��ձ�־λ	  	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);							//��ʱ��ʹ��
	TIM_Cmd(TIM2,ENABLE); 																//�ж�ʹ��
	
	 NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;						//
//	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;	//
//	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					//
//	 NVIC_InitStructure.NVIC_IRQChannelCmd= ENABLE;							//
	 NVIC_Init(&NVIC_InitStructure);
}

/****************TIM2 IRQ**************************
*���ܣ�
*˵������ʱ2MS

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


