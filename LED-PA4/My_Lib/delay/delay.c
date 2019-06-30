
#include "ALL_Includes.h"
#include "delay.h"
#define delay_ostickspersec	OS_TICKS_PER_SEC

u16 fac_ms;//ȫ�ֱ���
u8 fac_us;//ȫ�ֱ���

/****************************************************
�������ܣ�ms����ʱ
���������nms : ����
�����������
��    ע�����ô˺���ǰ����Ҫ��ʼ��Delay_Init()����
*****************************************************/							    
void delay_ms(u16 nms)
{
   	SysTick->LOAD = (u32)fac_ms*nms-1;//����ʱ��ֵ
	  SysTick->VAL = 1;//���д��ֵ��������ؼĴ�����ֵ
	  SysTick->CTRL |= BIT(0);//SysTickʹ��
	  while(!(SysTick->CTRL&(1<<16)));//�ж��Ƿ����0
	  SysTick->CTRL &=~BIT(0);//�ر�SysTick
}

/****************************************************
�������ܣ���ʱ��ʼ��
���������SYSCLK : ϵͳʱ��(72)MHZ
�����������
��    ע����
*****************************************************/
void Delay_Init(u8 SYSCLK)
{
	u32 reload;
	SysTick->CTRL &=~BIT(2);//ѡ���ⲿʱ��
	reload=SYSCLK/8;						//ÿ���ӵļ������� ��λΪM	   systemtickʱ��Ƶ��
	reload*=1000000/delay_ostickspersec;	//ÿ��ʱ��Ƭ�����ʱ��(us)*ÿus�ļ���ֵ=ÿ��ʱ��Ƭ��Ӧ�ļ���ֵ 
	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;   	//����SYSTICK�ж�
	SysTick->LOAD=reload; 					//ÿ1/delay_ostickspersec���ж�һ��	
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk; 	//����SYSTICK    

	fac_us = SYSCLK/8;//�����SysTick����ֵ
	fac_ms = (u16)fac_us*1000;	 
}

/****************************************************
�������ܣ�us����ʱ
���������nus : ΢��
�����������
��    ע�����ô˺���ǰ����Ҫ��ʼ��Delay_Init()����
*****************************************************/		    								   
void delay_us(u32 nus)
{		
	  SysTick->LOAD = (u32)fac_us*nus-1;//����ʱ��ֵ
	  SysTick->VAL = 1;//���д��ֵ��������ؼĴ�����ֵ
	  SysTick->CTRL |= BIT(0);//SysTickʹ��
	  while(!(SysTick->CTRL&(1<<16)));//�ж��Ƿ����0
	  SysTick->CTRL &=~BIT(0);//�ر�SysTick
}

void SysTick_Handler(void)
{
    OS_CPU_SR  cpu_sr;


    OS_ENTER_CRITICAL();                         /* Tell uC/OS-II that we are starting an ISR          */
    OSIntNesting++;
    OS_EXIT_CRITICAL();

    OSTimeTick();                                /* Call uC/OS-II's OSTimeTick()                       */

    OSIntExit();                                 /* Tell uC/OS-II that we are leaving the ISR          */
}
