/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * 文件名  ：main.c
 * 描述    ：建立3个任务，每个任务控制一个LED，以固定的频率轮流闪烁（频率可调）。         
 * 实验平台：野火STM32开发板
 * 库版本  ：ST3.0.0
 *
 * 作者    ：wildfire team 
 * 论坛    ：http://www.amobbs.com/forum-1008-1.html
 * 淘宝    ：http://firestm32.taobao.com
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
	OSTaskCreateExt(APP_TaskStart,                                        //void (*task)(void *pd) è???ê×μ??·
                    (void *)0,                                            //void *pdata            êy?Y????
                    &APP_TaskStartStk[APP_TASK_START_STK_SIZE - 1],       //OS_STK *ptos           ???òè??????????￥μ?????
                    (INT8U)APP_TASK_START_PRIO,                           //INT8U prio             è???ó??è??
                    (INT16U)APP_TASK_START_ID,                            //INT16U id              è???μ?IDo?
                    &APP_TaskStartStk[0],                                 //OS_STK *pbos           ???òè?????????μ×μ?????
                    (INT32U)APP_TASK_START_STK_SIZE,                      //INT32U stk_size        ????èYá?
                    (void *)0,                                            //void *pnext            êy?Y????
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);           //INT16U opt    
	OSStart();
  return 0;
 }

/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
