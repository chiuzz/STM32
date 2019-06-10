#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "includes.h"
#include "os_app_hooks.h"

#define				START_TASK_STK_SIZE				64		//��ջ��С�������?
#define				START_TASK_PRIO				5
OS_TCB        TCB_START_TASK;
CPU_STK       START_TASK_STK[START_TASK_STK_SIZE];
void START_TASK(void *p_arg);

int main(void)
{
    OS_ERR err;
    CPU_SR_ALLOC();

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    delay_init(168);
    uart_init(115200);
    OSInit(&err); //1����ʼ��ucos
    OS_CRITICAL_ENTER(); //�����ٽ��
    OSTaskCreate (&TCB_START_TASK,		//2����������
                  "start_task",
                  START_TASK,
                  (void *)0,
                  (OS_PRIO)START_TASK_PRIO,
                  &START_TASK_STK[0],
                  (CPU_STK_SIZE)(START_TASK_STK_SIZE/10),
                  (CPU_STK_SIZE)START_TASK_STK_SIZE,
                  (OS_MSG_QTY)0,
                  (OS_TICK)0,
                  (void*)0,
                  OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                  &err);
    OS_CRITICAL_EXIT(); //�˳��ٽ��
    OSStart(&err); //3����ʼ���������ϵͳ

    while(1);
}


void START_TASK(void *p_arg)
{
    OS_ERR err;
    while(1)
    {
        printf("test-zzz\r\n");
        OSTimeDlyHMSM (0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err);
    }
}



