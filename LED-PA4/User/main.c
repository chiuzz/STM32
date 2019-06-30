#include "ALL_Includes.h"//���������ͷ�ļ�

#define START_TASK_STK_SIZE 64
#define START_TASK_PRIO 4
static OS_STK start_task_stk[START_TASK_STK_SIZE];
void start_task(void *para);

void ALL_Config(void);
int main(void)
{	
	ALL_Config();

	OSInit();
	OSTaskCreate(start_task, 0, &start_task_stk[START_TASK_STK_SIZE - 1],START_TASK_PRIO);
	OSStart();

	while(1)
	{;}

}

/************************
�������ܣ��ܳ�ʼ��
�����������
�����������
��    ע����
************************/
void ALL_Config(void)
{
    Delay_Init(48);
		LED_Init();
}

void start_task(void *para)
{
	para = para;
	while(1)
	{
		LED_ON();
		OSTimeDlyHMSM(0,0,0,500);
		LED_OFF();
		OSTimeDlyHMSM(0,0,0,500);
	}
}




