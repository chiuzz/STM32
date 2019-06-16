#include "includes.h"
#include 	"app.h"			//用户任务函数
#include "ModuleServer.h"
#include "ModuleUart.h"
#include "ModuleScr.h"
#include "ModuleKey.h"
OS_STK			Task_Server_Stk[Task_Server_Stk_Size];
OS_STK			Task_1s_Stk[Task_1s_Prs_Stk_Size];
OS_STK			Task_10ms_Stk[Task_10ms_Prs_Stk_Size];
OS_STK			Task_50ms_Stk[Task_50ms_Prs_Stk_Size];
OS_STK			Task_1ms_Stk[Task_1ms_Prs_Stk_Size]; 

void Task_Server(void *pdata)
{
    PMODULESERVER pServer = (PMODULESERVER)pdata;
    while(1)
    {
//         OSTimeDlyHMSM(0, 0, 1, 0);
        if(pServer != NULL)
        {
            pServer->pMsgNotifyProcess(pServer->m_pBaseData);
        }
    }
}

void Task_1s_Process(void *pdata)
{
    PMODULEBASE pServer = (PMODULEBASE)pdata;
    while(1)
    {
        OSTimeDlyHMSM(0, 0, 1, 0);
        if(pServer != NULL)
        {
            pServer->pModele1sProcess(pServer->m_pBaseData);
        }
    }
}

void Task_50ms_Process(void *pdata)
{
    PMODULESERVER pServer = (PMODULESERVER)pdata;
    while(1)
    {
        OSTimeDlyHMSM(0, 0, 0, 50);
        if(pServer != NULL)
        {
            pServer->pModele50msProcess(pServer->m_pBaseData);
        }
    }
}


void Task_10ms_Process(void *pdata)
{
    PMODULESERVER pServer = (PMODULESERVER)pdata;
    while(1)
    {
        OSTimeDlyHMSM(0, 0, 0, 10);
        if(pServer != NULL)
        {
            pServer->pModele10msProcess(pServer->m_pBaseData);
        }
    }
}

void Task_1ms_Process(void *pdata)
{
    PMODULESERVER pServer = (PMODULESERVER)pdata;
    while(1)
    {
        OSTimeDlyHMSM(0, 0, 0, 1);
        if(pServer != NULL)
        {
            pServer->pModele1msProcess(pServer->m_pBaseData);
        }
    }
}

void* AppBase_Init(PGLOBALDATA pGlobal)
{
   SUBMODITEM Item; 
   pGlobal->pServer = CreateModuleServer();
   Item.tags = 0;
	
	 Item.pObj =  CreateModuleKey(pGlobal->pServer->m_pBaseData);
   Item.tags++;
   ((PMODULESERVER)pGlobal->pServer)->pSubModPushBack(pGlobal->pServer->m_pBaseData,&Item); 

	 Item.pObj =  CreateModuleScr(pGlobal->pServer->m_pBaseData);
   Item.tags++;
   ((PMODULESERVER)pGlobal->pServer)->pSubModPushBack(pGlobal->pServer->m_pBaseData,&Item); 

   Item.pObj =  CreateModuleUart(pGlobal->pServer->m_pBaseData);
   Item.tags++;
   ((PMODULESERVER)pGlobal->pServer)->pSubModPushBack(pGlobal->pServer->m_pBaseData,&Item);  

   pGlobal->pServer->pModeleInit(pGlobal->pServer->m_pBaseData);
   pGlobal->pServer->pModeleStart(pGlobal->pServer->m_pBaseData);
   return Item.pObj;
}

void AppCycle(PVOID pArg)
{
     PMODULEUART pObj = (PMODULEUART)pArg;
//     ASSERT(pObj->pStart!=NULL);
    while(1)
    {
       pObj->pStart(pObj->m_pBaseData);
       //OSTimeDlyHMSM(0, 0, 1, 0);
    }
}

void*  CreateMultiTask (void)
{
    //INT8U err;
    PVOID pObj = NULL;
    
    pObj = AppBase_Init(&g_Global);
//    OSTaskCreate(Task_Test,(void *)0,&Task_Test_Stk[Task_Test_Stk_Size-1], Task_Test_Prio);
    OSTaskCreate(Task_Server,(PVOID)(g_Global.pServer), &Task_Server_Stk[Task_Server_Stk_Size-1], Task_Server_Prio);
//    OSTaskNameSet(Task_Server_Prio, "Task-Server", &err);
    OSTaskCreate(Task_1s_Process,(PVOID)(g_Global.pServer), &Task_1s_Stk[Task_1s_Prs_Stk_Size-1], Task_1s_Prs_Prio);
    OSTaskCreate(Task_10ms_Process,(PVOID)(g_Global.pServer), &Task_10ms_Stk[Task_10ms_Prs_Stk_Size-1], Task_10ms_Prs_Prio);
    OSTaskCreate(Task_50ms_Process,(PVOID)(g_Global.pServer), &Task_50ms_Stk[Task_50ms_Prs_Stk_Size-1], Task_50ms_Prs_Prio);

    OSTaskCreate(Task_1ms_Process,(PVOID)(g_Global.pServer), &Task_1ms_Stk[Task_1ms_Prs_Stk_Size-1], Task_1ms_Prs_Prio);
    
    return pObj;
}

// 	 u16 address = 100000;
//    u8 data = 12;	
// 	  PS("----------IIC TEST WRITE 12 ------------");
//     IIC_Write(address, data);
//     PD(IIC_Read(address));
//     PS("----------IIC TEST WRITE END ------------");
	
