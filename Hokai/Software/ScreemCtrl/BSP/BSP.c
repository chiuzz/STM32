#include "includes.h"

/*
 * ��������BSP_Init
 * ����  ��ʱ�ӳ�ʼ����Ӳ����ʼ��
 * ����  ����
 * ���  ����
 */
void BSP_Init(void)
{
    SystemInit();		/* ����ϵͳʱ��Ϊ72M */	
		SysTick_init();		/* ��ʼ����ʹ��SysTick��ʱ�� */
    LED_GPIO_Config();  /* LED �˿ڳ�ʼ�� */
// 		USART_INIT();
		USART1_Config();
		uart3_init(19200);
//  		ADC_INIT();
//  		I2C_EE_Init();
}

/*
 * ��������SysTick_init
 * ����  ������SysTick��ʱ��
 * ����  ����
 * ���  ����
 */
void SysTick_init(void)
{
    SysTick_Config(SystemFrequency/OS_TICKS_PER_SEC);//��ʼ����ʹ��SysTick��ʱ��
}
