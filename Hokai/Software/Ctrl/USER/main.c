#include "includes.h"
#include "CreateMultiTask.h"
#include "System_Init.h"
#include "Target_Init.h"

//������ƿ�
OS_TCB Start2UartTaskTCB;
//�����ջ	
CPU_STK START_2_UART_TASK_STK[START_2_UART_STK_SIZE];

int main(void)
{
	OS_ERR err;
	CPU_SR_ALLOC();	
	
	System_Init();
	INTX_DISABLE();		//���ж�,��ֹ�δ�ʱ���������ʼ���Ĵ���
	Target_Init();
	INTX_ENABLE();		//���ж�
	
	OSInit(&err);		//��ʼ��UCOSIII
	OS_CRITICAL_ENTER();//�����ٽ���
	//������ʼ����
	OSTaskCreate((OS_TCB 	* )&Start2UartTaskTCB,		//������ƿ�
								 (CPU_CHAR	* )"start task", 		//��������
                 (OS_TASK_PTR )start_2_uart_task, 			//������
                 (void		* )0,					//���ݸ��������Ĳ���
                 (OS_PRIO	  )START_2_UART_TASK_PRIO,     //�������ȼ�
                 (CPU_STK   * )&START_2_UART_TASK_STK[0],	//�����ջ����ַ
                 (CPU_STK_SIZE)START_2_UART_STK_SIZE/10,	//�����ջ�����λ
                 (CPU_STK_SIZE)START_2_UART_STK_SIZE,		//�����ջ��С
                 (OS_MSG_QTY  )0,					//�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK	  )0,					//��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
                 (void   	* )0,					//�û�����Ĵ洢��
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //����ѡ��
                 (OS_ERR 	* )&err);				//��Ÿú�������ʱ�ķ���ֵ
	OS_CRITICAL_EXIT();	//�˳��ٽ���	 
	OSStart(&err);  //����UCOSIII
	while(1);
}

//��ʼ������
void start_2_uart_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//ͳ������                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//���ʹ���˲����жϹر�ʱ��
    CPU_IntDisMeasMaxCurReset();	
#endif
	
#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //��ʹ��ʱ��Ƭ��ת��ʱ��
	 //ʹ��ʱ��Ƭ��ת���ȹ���,ʱ��Ƭ����Ϊ1��ϵͳʱ�ӽ��ģ���1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif		
		CreateMultiTask();
    AppCycle();
}

