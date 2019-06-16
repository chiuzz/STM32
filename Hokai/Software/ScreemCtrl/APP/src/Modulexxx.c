//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* 文 件 名 : ModuleXxx.c
//*
//* 文件描述 : XXX任务
//*
//* 作    者 :
//* 版    本 :
//* 编 译 器 : IAR EWARM 5.20
//*********************************************************************************************************
//*
#include "ModuleXxx.h"

#include "usart.h"

BOOLEAN ModuleXxxInit(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULEXXXDATA pData = (PMODULEXXXDATA)pArg;
    if(pData != NULL)
    {
    }
    return ret;
}

BOOLEAN ModuleXxxReset(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULEXXXDATA pData = (PMODULEXXXDATA)pArg;
    pData->m_PressSta = FALSE;
    pData->m_Count = 0;
    return ret;
}

BOOLEAN ModuleXxxStart(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULEXXXDATA pData = (PMODULEXXXDATA)pArg;
    pData->m_PressSta = TRUE;
    return ret;
}

BOOLEAN ModuleXxxStop(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULEXXXDATA pData = (PMODULEXXXDATA)pArg;
    pData->m_PressSta = FALSE;
    return ret;
}

BOOLEAN ModuleXxxRelease(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULEXXXDATA pData = (PMODULEXXXDATA)pArg;
    if(pData != NULL)
        free(pData);
    return ret;
}

void ModuleXxx1sProcess(void* pArg)
{
    PMODULEXXXDATA pData = (PMODULEXXXDATA)pArg;
//     printf("ModuleXxx1sProcess !! \n");
    if(pData->m_PressSta == FALSE)
        return;
    pData->m_Count++;
    if(pData->m_Count > 60)
    {
        pData->m_Count = 0;
        //执行配置保存，调用处理函数
        //  if(pData->m_pMsgQueue != NULL)
//	        {
//	            pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData,MS_XXX_SAVE,1,0,NULL);
//	        }
    }


//    uint16_t data = 0xff;
//    UartSendData(&data,  1);
}

void XxxMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf) //消息处理
{

//    switch(MsgId)
//    {
//        case MSG_XXX_SAVE:
//          if(lParam == 1)
//          {
//            //立即执行配置保存，调用处理函数
//              XxxSave();
//          }
//          break;
//        default:break;
//    }
//    printf("Receive MSG !!!\n");

}

PMODULEBASE CreateModuleXxx(PMODULESERVERDATA pServerData)
{
    PMODULEXXX pModXxx = NULL;
    PMODULEXXXDATA pData = NULL;

    pModXxx = (PMODULEXXX)malloc(sizeof(MODULEXXX));//申请基类结构
    pData = (PMODULEXXXDATA)malloc(sizeof(MODULEXXXDATA));//申请基类数据结构
    ASSERT(pModXxx != NULL);
    ASSERT(pData != NULL);
    pData->m_pMsgQueue = pServerData->m_pMsgQueue;
    pModXxx->m_pBaseData = (PVOID)pData;

    //************************以下模块接口必须赋值******************************
    pModXxx->pModeleInit = ModuleXxxInit; //实现模块初始化
    pModXxx->pModeleReset = ModuleXxxReset; //实现模块复位
    pModXxx->pModeleStart = ModuleXxxStart; //实现模块开始
    pModXxx->pModeleStop = ModuleXxxStop; //实现模块结束
    pModXxx->pModeleRelease = ModuleXxxRelease;//实现
    pModXxx->pMsgNotify = XxxMsgNotify;//实现消息队列处理
    pModXxx->pModele10msProcess = NULL;//不实现，置为NULL
    pModXxx->pModele50msProcess = NULL;//不实现，置为NULL
    pModXxx->pModele1sProcess = ModuleXxx1sProcess;//实现1s调用
    strcpy(pModXxx->m_ModName, "ModXxx");

    printf("CreateModuleXxx!!\n");
    return (PMODULEBASE)pModXxx;
}


