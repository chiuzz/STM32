#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__
// #include "common.h"


/************设置栈大小（单位为 OS_STK ）************/
#define STARTUP_TASK_STK_SIZE   80   
#define	TASK_LED2_STK_SIZE		80
#define	TASK_LED3_STK_SIZE		80


#define  APP_TASK_160_STK_SIZE            160                                        
#define  APP_TASK_100_STK_SIZE            400                                         
#define  APP_TASK_50_STK_SIZE            50                                         


#define  APP_TASK_START_PRIO                10                                           
#define  APP_TASK_START_ID                  APP_TASK_START_PRIO                         
#define	 APP_TASK_START_STK_SIZE		    APP_TASK_100_STK_SIZE

//#define			Task_Test_Stk_Size		APP_TASK_50_STK_SIZE
#define			Task_Server_Stk_Size	APP_TASK_100_STK_SIZE
#define			Task_1s_Prs_Stk_Size	APP_TASK_100_STK_SIZE
#define			Task_10ms_Prs_Stk_Size	APP_TASK_100_STK_SIZE
#define			Task_50ms_Prs_Stk_Size	APP_TASK_100_STK_SIZE
#define			Task_1ms_Prs_Stk_Size	APP_TASK_50_STK_SIZE

#define			Task_Test_Prio			APP_TASK_START_PRIO+5

#define			Task_Server_Prio	    7
#define			Task_1s_Prs_Prio		9
#define			Task_10ms_Prs_Prio		6
#define			Task_50ms_Prs_Prio		8
#define			Task_1ms_Prs_Prio		5


#endif

