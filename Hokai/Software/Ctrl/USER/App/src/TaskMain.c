//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* 文 件 名 : TaskMain.c
//*
//* 文件描述 : 主服务任务
//*
//* 作    者 :
//* 版    本 :
//* 编 译 器 : IAR EWARM 5.20
//*********************************************************************************************************
//*
#include "TaskMain.h"

void Task_Server(void *pdata)
{
    PMODULESERVER pServer = (PMODULESERVER)pdata;
//    OS_ERR err;
    while(1)
    {
//			  OSTimeDlyHMSM(0,0,1,0, OS_OPT_TIME_DLY,&err); //延时1s
//			  printf("pMsgNotifyProcess !!\n");
        if(pServer != NULL)
        {
            pServer->pMsgNotifyProcess(pServer->m_pBaseData);
        }
    }
}

void Task_One_Process(void *pdata)
{
    PMODULEBASE pServer = (PMODULEBASE)pdata;
    OS_ERR err;
    while(1)
    {
        OSTimeDlyHMSM(0,0,1,0, OS_OPT_TIME_DLY,&err); //延时1s
//        printf("Task_One_Process !!\n");
        if(pServer != NULL)
        {
            pServer->pModele1sProcess(pServer->m_pBaseData);
        }
    }
}

void Task_Two_Process(void *pdata)
{
    PMODULESERVER pServer = (PMODULESERVER)pdata;
    OS_ERR err;
    while(1)
    {
        OSTimeDlyHMSM(0,0,0,50, OS_OPT_TIME_DLY,&err); //延时50ms
//        printf("Task_Two_Process !!\n");
        if(pServer != NULL)
        {
            pServer->pModele50msProcess(pServer->m_pBaseData);
        }
    }
}


void Task_The_Process(void *pdata)
{
    PMODULESERVER pServer = (PMODULESERVER)pdata;
    OS_ERR err;
    while(1)
    {
        OSTimeDlyHMSM(0,0,0,10, OS_OPT_TIME_DLY,&err); //延时10ms
//        printf("Task_The_Process !!\n");
        if(pServer != NULL)
        {
            pServer->pModele10msProcess(pServer->m_pBaseData);
        }
    }
}

void Task_Fou_Process(void *pdata)
{
    PMODULESERVER pServer = (PMODULESERVER)pdata;
    OS_ERR err;
    while(1)
    {
        OSTimeDlyHMSM(0,0,0,1, OS_OPT_TIME_DLY,&err); //延时1ms
//				printf("Task_Fou_Process !!\n");
        if(pServer != NULL)
        {
            pServer->pModele1msProcess(pServer->m_pBaseData);
        }
    }
}

