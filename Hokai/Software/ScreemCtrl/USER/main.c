/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * �ļ���  ��main.c
 * ����    ������3������ÿ���������һ��LED���Թ̶���Ƶ��������˸��Ƶ�ʿɵ�����         
 * ʵ��ƽ̨��Ұ��STM32������
 * ��汾  ��ST3.0.0
 *
 * ����    ��wildfire team 
 * ��̳    ��http://www.amobbs.com/forum-1008-1.html
 * �Ա�    ��http://firestm32.taobao.com
**********************************************************************************/
#include "includes.h"
#include "app.h"
  
void APP_TaskStart(void *pdata)
{
    AppCycle(CreateMultiTask());
//    OSTaskSuspend(OS_PRIO_SELF);
//    while(1)
//    {
//        OSTimeDlyHMSM(0, 0, 1, 0);
//    }
}

OS_STK APP_TaskStartStk[APP_TASK_100_STK_SIZE]; 
int main(void)
{
  BSP_Init();
	OSInit();
	OSTaskCreateExt(APP_TaskStart,                                        //void (*task)(void *pd) ��???������??��
                    (void *)0,                                            //void *pdata            ��y?Y????
                    &APP_TaskStartStk[APP_TASK_START_STK_SIZE - 1],       //OS_STK *ptos           ???����??????????����?????
                    (INT8U)APP_TASK_START_PRIO,                           //INT8U prio             ��???��??��??
                    (INT16U)APP_TASK_START_ID,                            //INT16U id              ��???��?IDo?
                    &APP_TaskStartStk[0],                                 //OS_STK *pbos           ???����?????????�̡���?????
                    (INT32U)APP_TASK_START_STK_SIZE,                      //INT32U stk_size        ????��Y��?
                    (void *)0,                                            //void *pnext            ��y?Y????
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);           //INT16U opt    
	OSStart();
  return 0;
 }

/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
