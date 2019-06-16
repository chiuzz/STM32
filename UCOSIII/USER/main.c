#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "usart2.h"
#include "led.h"
#include "includes.h"
#include "os_app_hooks.h"

#define				START_TASK_STK_SIZE				256		//堆栈大小如何设置?
#define				START_TASK_PRIO				5
OS_TCB        TCB_START_TASK;
CPU_STK       START_TASK_STK[START_TASK_STK_SIZE];
void START_TASK(void *p_arg);

#define				TASK1_STK_SIZE				256
#define				TASK1_PRIO				10
OS_TCB        TCB_TASK1;
CPU_STK       TASK1_STK[TASK1_STK_SIZE];
void TASK1(void *p_arg);

#define				TASK2_STK_SIZE				256
#define				TASK2_PRIO				11
OS_TCB        TCB_TASK2;
CPU_STK       TASK2_STK[TASK2_STK_SIZE];
void TASK2(void *p_arg);

OS_Q        Msg_Que;
typedef struct student_tab {
    char stu_name[10];
    u8 num;
} STU;

int main(void)
{
    OS_ERR err;
    CPU_SR_ALLOC();

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    delay_init(168);
    uart_init(115200);
    uart2_init(115200);
    OSInit(&err); //1、初始化ucos
    OS_CRITICAL_ENTER(); //进入临界段
    OSTaskCreate (&TCB_START_TASK,		//2、创建任务
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
    OS_CRITICAL_EXIT(); //退出临界段
    OSStart(&err); //3、开始多任务管理系统

    while(1);
}


void START_TASK(void *p_arg)
{
    OS_ERR err;
    CPU_SR_ALLOC();

    OSQCreate (&Msg_Que,
               "Msg_Que",
               10,
               &err);

#if OS_CFG_SCHED_ROUND_ROBIN_EN > 0u
    OSSchedRoundRobinCfg (DEF_ENABLED, (OS_TICK)1, &err);		//打开时间片轮转调度功能，设置默认时间片长度1
#endif
    OS_CRITICAL_ENTER(); //进入临界段
    OSTaskCreate (&TCB_TASK1,		//2、创建任务
                  "TASK1",
                  TASK1,
                  (void *)0,
                  (OS_PRIO)TASK1_PRIO,
                  &TASK1_STK[0],
                  (CPU_STK_SIZE)(TASK1_STK_SIZE/10),
                  (CPU_STK_SIZE)TASK1_STK_SIZE,
                  (OS_MSG_QTY)0,
                  (OS_TICK)2,		//2个时间片
                  (void*)0,
                  OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                  &err);

    OSTaskCreate (&TCB_TASK2,		//2、创建任务
                  "TASK2",
                  TASK2,
                  (void *)0,
                  (OS_PRIO)TASK2_PRIO,
                  &TASK2_STK[0],
                  (CPU_STK_SIZE)(TASK2_STK_SIZE/10),
                  (CPU_STK_SIZE)TASK2_STK_SIZE,
                  (OS_MSG_QTY)0,
                  (OS_TICK)2,		//2个时间片
                  (void*)0,
                  OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                  &err);
    OS_CRITICAL_EXIT(); //退出临界段
    //OSTaskSuspend ((OS_TCB *)0, &err);			//挂起任务，可以传入NULL或自己的TCB来挂起自己
    OSTaskDel ((OS_TCB *)0,&err);			//删除任务，可以传入NULL或自己的TCB来删除自己

    while(1)
    {
        printf("test-zzz0\r\n");
        OSTimeDlyHMSM (0,0,5,0,OS_OPT_TIME_HMSM_STRICT,&err);
    }
}

u8 ShareBuf[20];

void TASK1(void *p_arg)
{
    u8 j=0;
    u16 size;
    OS_ERR err;
    STU *pSTU;
//    CPU_SR_ALLOC();
    u8 buf[USART_REC_LEN2]= {0};
    while(1)
    {
        if(USART_RX_STA2&0x8000) {
            USART_RX_STA2=0;
            Str_Copy((CPU_CHAR*)buf,(CPU_CHAR*)USART_RX_BUF2);
            for(j=0; j<USART_REC_LEN2; j++) {
                USART_RX_BUF2[j]=0;
            }
        }
        pSTU=(STU *)OSQPend (&Msg_Que,
                             0,
                             OS_OPT_PEND_BLOCKING,
                             (OS_MSG_SIZE *)&size,
                             0,
                             &err);

        printf("student name:%s, num:%d, size:%d\r\n",pSTU->stu_name,pSTU->num,size);
        OSTimeDlyHMSM (0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err);
    }
}

void TASK2(void *p_arg)
{
    OS_ERR err;
    u8 j=0;
    STU stu1;
    Str_Copy((CPU_CHAR*)stu1.stu_name,(CPU_CHAR*)"Chiuzz_");
    stu1.num=Str_Len(stu1.stu_name);

//    CPU_SR_ALLOC();
    while(1)
    {
        OSQPost (&Msg_Que,
                 (void *)&stu1,
                 (OS_MSG_SIZE) sizeof(stu1),
                 OS_OPT_POST_FIFO,
                 &err);
        OSTimeDlyHMSM (0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err);
    }
}

