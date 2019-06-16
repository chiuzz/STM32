/**
 * @file CreateMultiTask.c
 * @brief 
 * @author LGL
 * 0.011
 * @date 2015-05-04
 */
#include "CreateMultiTask.h"
#include "TaskMain.h"

//任务控制块
OS_TCB Task_Server_TCB;
OS_TCB Task_us_TCB;
OS_TCB	Task_10ms_TCB;
OS_TCB	Task_50ms_TCB;
OS_TCB	Task_1s_TCB;
//任务堆栈	
CPU_STK TASK_SERVER_STK[TASK_SERVER_STK_SIZE];
CPU_STK US_TASK_STK[TASK_US_STK_SIZE];
CPU_STK	TASK_10MS_STK[TASK_10MS_STK_SIZE];
CPU_STK	TASK_50MS_STK[TASK_50MS_STK_SIZE];
CPU_STK	TASK_1S_STK[TASK_1S_STK_SIZE];

#include "ModuleServer.h"
#include "ModuleConfig.h"
#include "ModuleCoolerCtrl.h"
#include "ModuleGpioProc.h"
#include "ModuleHeaterCtrl.h"
#include "ModuleScreenDriver.h"
#include "ModuleSystemProc.h"
#include "ModuleTempProc.h"
#include "ModuleCalc.h"

static GLOBALDATA g_Global;

void AppCycle()
{	
		PMODULESERVER pServer = (PMODULESERVER)(g_Global.pServer);	
	  OS_ERR err;
		while(1)
		{
			  if(pServer != NULL)
        {
					OSTimeDlyHMSM(0,0,0,10, OS_OPT_TIME_DLY,&err);
//					printf("AppCycle !!\n");
            pServer->pModeleUartProcess(pServer->m_pBaseData);
        }
		}
}

void AppBase_Init(PGLOBALDATA pGlobal) 
{
    SUBMODITEM Item;
	pGlobal->pServer = CreateModuleServer();		//g_Global变量专门存放服务器类地址
	//pModServer->m_pBaseData->m_pSubMouleList = NULL;

    Item.tags = 0;
    //*******************************添加功能模块****************************************
    //******添加配置管理功能模块********
    Item.pObj =  CreateModuleConfig(pGlobal->pServer->m_pBaseData);
    Item.tags++;		//链表下标
    ((PMODULESERVER)pGlobal->pServer)->pSubModPushBack(pGlobal->pServer->m_pBaseData,&Item);			//pSubModPushBack 链接item
	
	  Item.pObj =  CreateModuleCoolerCtrl(pGlobal->pServer->m_pBaseData);
    Item.tags++;
    ((PMODULESERVER)pGlobal->pServer)->pSubModPushBack(pGlobal->pServer->m_pBaseData,&Item);
	
		Item.pObj =  CreateModuleGpioProc(pGlobal->pServer->m_pBaseData);
    Item.tags++;
    ((PMODULESERVER)pGlobal->pServer)->pSubModPushBack(pGlobal->pServer->m_pBaseData,&Item);
	
		Item.pObj =  CreateModuleHeaterCtrl(pGlobal->pServer->m_pBaseData);
    Item.tags++;
    ((PMODULESERVER)pGlobal->pServer)->pSubModPushBack(pGlobal->pServer->m_pBaseData,&Item);
	
		Item.pObj =  CreateModuleScreenDriver(pGlobal->pServer->m_pBaseData);
    Item.tags++;
    ((PMODULESERVER)pGlobal->pServer)->pSubModPushBack(pGlobal->pServer->m_pBaseData,&Item);
		
		Item.pObj =  CreateModuleSystemProc(pGlobal->pServer->m_pBaseData);
    Item.tags++;
    ((PMODULESERVER)pGlobal->pServer)->pSubModPushBack(pGlobal->pServer->m_pBaseData,&Item);
		
		Item.pObj =  CreateModuleTempProc(pGlobal->pServer->m_pBaseData);
    Item.tags++;
    ((PMODULESERVER)pGlobal->pServer)->pSubModPushBack(pGlobal->pServer->m_pBaseData,&Item);
		
		Item.pObj =  CreateModuleCalc(pGlobal->pServer->m_pBaseData);
    Item.tags++;
    ((PMODULESERVER)pGlobal->pServer)->pSubModPushBack(pGlobal->pServer->m_pBaseData,&Item);
		
    pGlobal->pServer->pModeleInit(pGlobal->pServer->m_pBaseData);
    pGlobal->pServer->pModeleStart(pGlobal->pServer->m_pBaseData);
}

void CreateMultiTask()
{
    OS_ERR err;
    AppBase_Init(&g_Global);

    OSTaskCreate((OS_TCB 	* )&Task_Server_TCB,		
            (CPU_CHAR	* )"server task", 		
            (OS_TASK_PTR )Task_Server, 			 			
            (PVOID)(g_Global.pServer),
//						(OS_TASK_PTR )server_task, 
//						(	void *)0,	
            (OS_PRIO	  )TASK_SERVER_PRIO,     
            (CPU_STK   * )&TASK_SERVER_STK[0],	
            (CPU_STK_SIZE)TASK_SERVER_STK_SIZE/10,	
            (CPU_STK_SIZE)TASK_SERVER_STK_SIZE,		
            (OS_MSG_QTY  )0,					
            (OS_TICK	  )0,					
            (void   	* )0,					
            (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
            (OS_ERR 	* )&err);				

    OSTaskCreate((OS_TCB 	* )&Task_us_TCB,		
            (CPU_CHAR	* )"us task", 		
            (OS_TASK_PTR )Task_One_Process, 	
//            (OS_TASK_PTR )us_task, 			
            (PVOID)(g_Global.pServer),					
            (OS_PRIO	  )TASK_US_PRIO,     	
            (CPU_STK   * )&US_TASK_STK[0],	
            (CPU_STK_SIZE)TASK_US_STK_SIZE/10,	
            (CPU_STK_SIZE)TASK_US_STK_SIZE,		
            (OS_MSG_QTY  )0,					
            (OS_TICK	  )0,					
            (void   	* )0,				
            (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
            (OS_ERR 	* )&err);

    OSTaskCreate((OS_TCB 	* )&Task_10ms_TCB,		
            (CPU_CHAR	* )"10ms test task", 		
            (OS_TASK_PTR )Task_Two_Process, 
//            (OS_TASK_PTR )task_10ms, 			
            (PVOID)(g_Global.pServer),					
            (OS_PRIO	  )TASK_10MS_PRIO,     	
            (CPU_STK   * )&TASK_10MS_STK[0],	
            (CPU_STK_SIZE)TASK_10MS_STK_SIZE/10,	
            (CPU_STK_SIZE)TASK_10MS_STK_SIZE,		
            (OS_MSG_QTY  )0,					
            (OS_TICK	  )0,					
            (void   	* )0,				
            (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
            (OS_ERR 	* )&err);				 

    OSTaskCreate((OS_TCB 	* )&Task_50ms_TCB,		
            (CPU_CHAR	* )"50ms test task", 		
             (OS_TASK_PTR )Task_The_Process, 	
//            (OS_TASK_PTR )task_50ms, 			
            (PVOID)(g_Global.pServer),					
            (OS_PRIO	  )TASK_50MS_PRIO,     	
            (CPU_STK   * )&TASK_50MS_STK[0],	
            (CPU_STK_SIZE)TASK_50MS_STK_SIZE/10,	
            (CPU_STK_SIZE)TASK_50MS_STK_SIZE,		
            (OS_MSG_QTY  )0,					
            (OS_TICK	  )0,					
            (void   	* )0,				
            (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
            (OS_ERR 	* )&err);				 

    OSTaskCreate((OS_TCB 	* )&Task_1s_TCB,		
            (CPU_CHAR	* )"1s test task", 		
            (OS_TASK_PTR )Task_Fou_Process, 			 
//            (OS_TASK_PTR )task_1s, 			
            (PVOID)(g_Global.pServer),					
            (OS_PRIO	  )TASK_1S_PRIO,     	
            (CPU_STK   * )&TASK_1S_STK[0],	
            (CPU_STK_SIZE)TASK_1S_STK_SIZE/10,	
            (CPU_STK_SIZE)TASK_1S_STK_SIZE,		
            (OS_MSG_QTY  )0,					
            (OS_TICK	  )0,					
            (void   	* )0,				
            (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
            (OS_ERR 	* )&err);		
}

