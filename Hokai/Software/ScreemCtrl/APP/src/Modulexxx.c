//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* �� �� �� : ModuleXxx.c
//*
//* �ļ����� : XXX����
//*
//* ��    �� :
//* ��    �� :
//* �� �� �� : IAR EWARM 5.20
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
        //ִ�����ñ��棬���ô�����
        //  if(pData->m_pMsgQueue != NULL)
//	        {
//	            pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData,MS_XXX_SAVE,1,0,NULL);
//	        }
    }


//    uint16_t data = 0xff;
//    UartSendData(&data,  1);
}

void XxxMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf) //��Ϣ����
{

//    switch(MsgId)
//    {
//        case MSG_XXX_SAVE:
//          if(lParam == 1)
//          {
//            //����ִ�����ñ��棬���ô�����
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

    pModXxx = (PMODULEXXX)malloc(sizeof(MODULEXXX));//�������ṹ
    pData = (PMODULEXXXDATA)malloc(sizeof(MODULEXXXDATA));//����������ݽṹ
    ASSERT(pModXxx != NULL);
    ASSERT(pData != NULL);
    pData->m_pMsgQueue = pServerData->m_pMsgQueue;
    pModXxx->m_pBaseData = (PVOID)pData;

    //************************����ģ��ӿڱ��븳ֵ******************************
    pModXxx->pModeleInit = ModuleXxxInit; //ʵ��ģ���ʼ��
    pModXxx->pModeleReset = ModuleXxxReset; //ʵ��ģ�鸴λ
    pModXxx->pModeleStart = ModuleXxxStart; //ʵ��ģ�鿪ʼ
    pModXxx->pModeleStop = ModuleXxxStop; //ʵ��ģ�����
    pModXxx->pModeleRelease = ModuleXxxRelease;//ʵ��
    pModXxx->pMsgNotify = XxxMsgNotify;//ʵ����Ϣ���д���
    pModXxx->pModele10msProcess = NULL;//��ʵ�֣���ΪNULL
    pModXxx->pModele50msProcess = NULL;//��ʵ�֣���ΪNULL
    pModXxx->pModele1sProcess = ModuleXxx1sProcess;//ʵ��1s����
    strcpy(pModXxx->m_ModName, "ModXxx");

    printf("CreateModuleXxx!!\n");
    return (PMODULEBASE)pModXxx;
}


