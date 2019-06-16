//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* �� �� �� : ModuleServer.c
//*
//* �ļ����� : ������������
//*
//* ��    �� :
//* ��    �� :
//* �� �� �� : IAR EWARM 5.20
//*********************************************************************************************************
//*
#include "ModuleServer.h"

int SubModInit(int Tag, void* Memory, void* Args)
{
    int ret = 0;
    PSUBMODITEM pSrc = Memory;
//    PSUBMODITEM pDis = Args;
    PMODULEBASE pSubMod = NULL;
    if(pSrc != NULL)
    {
        pSubMod = pSrc->pObj;
        if(pSubMod != NULL)
            pSubMod->pModeleInit(pSubMod->m_pBaseData);
    }
//    PS(pSubMod->m_ModName);
//    printf("%s Init End!!\n",pSubMod->m_ModName);
    return ret;
}

int SubModReset(int Tag, void* Memory, void* Args)
{
    int ret = 0;
    PSUBMODITEM pSrc = Memory;
//    PSUBMODITEM pDis = Args;
    PMODULEBASE pSubMod = NULL;
    if(pSrc != NULL)
    {
        pSubMod = pSrc->pObj;
        if(pSubMod != NULL)
            pSubMod->pModeleReset(pSubMod->m_pBaseData);
    }
    return ret;
}

int SubModStart(int Tag, void* Memory, void* Args)
{
    int ret = 0;
    PSUBMODITEM pSrc = Memory;
//    PSUBMODITEM pDis = Args;
    PMODULEBASE pSubMod = NULL;
    if(pSrc != NULL)
    {
        pSubMod = pSrc->pObj;
        if(pSubMod != NULL)
            pSubMod->pModeleStart(pSubMod->m_pBaseData);
    }
//    printf("%s Start End!!\n",pSubMod->m_ModName);
    return ret;
}

int SubModStop(int Tag, void* Memory, void* Args)
{
    int ret = 0;
    PSUBMODITEM pSrc = Memory;
//    PSUBMODITEM pDis = Args;
    PMODULEBASE pSubMod = NULL;
    if(pSrc != NULL)
    {
        pSubMod = pSrc->pObj;
        if(pSubMod != NULL)
            pSubMod->pModeleStop(pSubMod->m_pBaseData);
    }
    return ret;
}

int SubModRelease(int Tag, void* Memory, void* Args)
{
    int ret = 0;
    PSUBMODITEM pSrc = Memory;
//    PSUBMODITEM pDis = Args;
    PMODULEBASE pSubMod = NULL;
    if(pSrc != NULL)
    {
        pSubMod = pSrc->pObj;
        if(pSubMod != NULL)
            pSubMod->pModeleRelease(pSubMod->m_pBaseData);
    }
    return ret;
}

int SubMod10msProcess(int Tag, void* Memory, void* Args)
{
    int ret = 0;
    PSUBMODITEM pSrc = Memory;
//    PSUBMODITEM pDis = Args;
    PMODULEBASE pSubMod = NULL;
    if(pSrc != NULL)
    {
        pSubMod = pSrc->pObj;
        if(pSubMod != NULL &&  pSubMod->pModele10msProcess!=NULL )
            pSubMod->pModele10msProcess(pSubMod->m_pBaseData);
    }
    return ret;
}

int SubMod50msProcess(int Tag, void* Memory, void* Args)
{
    int ret = 0;
    PSUBMODITEM pSrc = Memory;
//    PSUBMODITEM pDis = Args;
    PMODULEBASE pSubMod = NULL;
    if(pSrc != NULL)
    {
        pSubMod = pSrc->pObj;
        if(pSubMod != NULL && pSubMod->pModele50msProcess!=NULL )
            pSubMod->pModele50msProcess(pSubMod->m_pBaseData);
    }
    return ret;
}

int SubMod1sProcess(int Tag, void* Memory, void* Args)
{
    int ret = 0;
    PSUBMODITEM pSrc = Memory;
//    PSUBMODITEM pDis = Args;
    PMODULEBASE pSubMod = NULL;
    if(pSrc != NULL)
    {
        pSubMod = pSrc->pObj;
        if(pSubMod != NULL && pSubMod->pModele1sProcess!=NULL )
            pSubMod->pModele1sProcess(pSubMod->m_pBaseData);
    }
    return ret;
}


int SubModMsgNotify(int Tag, void* Memory, void* Args)
{
    int ret = 0;
    PSUBMODITEM pSrc = Memory;
    PMSGITEM pDis = Args;
    PMODULEBASE pSubMod = NULL;
    if(pSrc != NULL)
    {
        pSubMod = pSrc->pObj;
        if(pSubMod != NULL)
            pSubMod->pMsgNotify(pSubMod->m_pBaseData,pDis->MsgId, pDis->lParam, pDis->wParam, pDis->pBuf);
    }
    return ret;
}

BOOLEAN ModuleServerInit(void* pArg)
{
//    printf("ModuleServerInit\n");
    BOOLEAN ret = TRUE;
    PMODULESERVERDATA pData = (PMODULESERVERDATA)pArg;
    DLLIST *FindAddr = NULL;
    pData->m_PressSta = FALSE;
    DLWalk((DLLIST*)(pData->m_pSubMouleList),&FindAddr,SubModInit,NULL);
//    printf("ModuleServerInit end\n");
    return ret;
}

BOOLEAN ModuleServerReset(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULESERVERDATA pData = (PMODULESERVERDATA)pArg;
    DLLIST *FindAddr = NULL;
    pData->m_PressSta = FALSE;
    DLWalk((DLLIST*)(pData->m_pSubMouleList),&FindAddr,SubModReset,NULL);
//    printf("ModuleServerReset end\n");
    return ret;
}

BOOLEAN ModuleServerStart(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULESERVERDATA pData = (PMODULESERVERDATA)pArg;
    DLLIST *FindAddr = NULL;
    pData->m_PressSta = TRUE;
    DLWalk((DLLIST*)(pData->m_pSubMouleList),&FindAddr,SubModStart,NULL);
//    printf("ModuleServerStart end\n");
    return ret;
}

BOOLEAN ModuleServerStop(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULESERVERDATA pData = (PMODULESERVERDATA)pArg;
    DLLIST *FindAddr = NULL;
    pData->m_PressSta = FALSE;
    DLWalk((DLLIST*)(pData->m_pSubMouleList),&FindAddr,SubModStop,NULL);
    return ret;
}

BOOLEAN ModuleServerRelease(void* pArg)
{
    BOOLEAN ret = TRUE;
    PMODULESERVERDATA pData = (PMODULESERVERDATA)pArg;

    DLLIST *FindAddr = NULL;
    DLWalk((DLLIST*)(pData->m_pSubMouleList),&FindAddr,SubModRelease,NULL);

    if(pData != NULL)
        free(pData);
    return ret;
}

void ModuleServer1sProcess(void* pArg)
{
//    printf("ModuleServer1sProcess!!\n");
    PMODULESERVERDATA pData = (PMODULESERVERDATA)pArg;
    DLLIST *FindAddr = NULL;
    if(pData->m_PressSta == FALSE)
        return;
    DLWalk((DLLIST*)(pData->m_pSubMouleList),&FindAddr,SubMod1sProcess,NULL);
//  if(pData->m_pMsgQueue != NULL)
//	{
//	  pData->m_pMsgQueue->push_back(pData->m_pMsgQueue->pData,1,0,0,NULL);
//	}
}

void ModuleServer10msProcess(void* pArg)
{
//  printf("ModuleServer10msProcess!!\n");
    PMODULESERVERDATA pData = (PMODULESERVERDATA)pArg;
    DLLIST *FindAddr = NULL;
    if(pData->m_PressSta == FALSE)
        return;
    DLWalk((DLLIST*)(pData->m_pSubMouleList),&FindAddr,SubMod10msProcess,NULL);
}

void ModuleServer50msProcess(void* pArg)
{
//   printf("ModuleServer50msProcess!!\n");
    PMODULESERVERDATA pData = (PMODULESERVERDATA)pArg;
    DLLIST *FindAddr = NULL;
    if(pData->m_PressSta == FALSE)
        return;
    DLWalk((DLLIST*)(pData->m_pSubMouleList),&FindAddr,SubMod50msProcess,NULL);
}

void ServerMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf) //��Ϣ����
{
//    int ret;
    PMODULESERVERDATA pData = (PMODULESERVERDATA)pArg;
//    printf("Get Msg ID: %d\n",MsgId);
    MSGITEM Item;
    DLLIST *FindAddr = NULL;
//    Item.pArg = pData->m_pBaseData;
    Item.MsgId = MsgId;
    Item.lParam = lParam;
    Item.wParam = wParam;
    Item.pBuf = pBuf;
    DLWalk((DLLIST*)(pData->m_pSubMouleList), &FindAddr,SubModMsgNotify, &Item);
}

void MsgNotifyProcess(PVOID pArg)
{
    PMODULESERVERDATA pData = (PMODULESERVERDATA)pArg;
//    printf("MsgNotifyProcess!!\n");
    if(pData->m_pMsgQueue != NULL)
    {
        pData->m_pMsgQueue->pend(pData->m_pMsgQueue->pData);
    }
}


void SubModPushBack(PVOID pArg, PSUBMODITEM pObj)
{
    int ret;
    PMODULESERVERDATA pData = (PMODULESERVERDATA)pArg;
//   if(pData->m_pSubMouleList != NULL)
//     return;
    ret = DLAppend((DLLIST**)&(pData->m_pSubMouleList),pObj->tags,pObj,sizeof(SUBMODITEM));
    if(ret != DL_SUCCESS)
    {
        //     printf("Add %s List Error\n", pObj->pObj->m_ModName);
    }

}

#define MSGQUEUE_ID 1
PMODULEBASE CreateModuleServer()
{
    PMODULESERVER pModServer = NULL;
    PMODULESERVERDATA pData = NULL;
    MsgNotiflyPtr pFun;

    pModServer = (PMODULESERVER)malloc((int)sizeof(MODULESERVER));//�������ṹ
    pData = (PMODULESERVERDATA)malloc(sizeof(MODULESERVERDATA));//����������ݽṹ
    pData->m_pSysData = (PSYSPARAMDATA)malloc(sizeof(SYSPARAMDATA));
    pData->m_pCfgData = (PSYSCONFIGDATA)malloc(sizeof(SYSCONFIGDATA));
    pData->m_pCalData = (PSYSCALCDATA)malloc(sizeof(SYSCALCDATA));
    pData->m_pAdjData = (PSYSADJDATA)malloc(sizeof(SYSADJDATA));
//  ASSERT(pModServer != NULL);
//  ASSERT(pData != NULL);
    //ASSERT(pData->m_pSysData != NULL);
    pModServer->m_pBaseData = (PVOID)pData;
    pFun = ServerMsgNotify;

    //************************����ģ��ӿڱ��븳ֵ******************************
//  printf("sizeof(MODULESERVERDATA) %d\n",(int)sizeof(MODULESERVERDATA));
//  printf("sizeof(MODULESERVER) %d\n",(int)sizeof(MODULESERVER));
    strcpy(pModServer->m_ModName, "ModServer");

    pModServer->pModeleInit = ModuleServerInit; //ʵ��ģ���ʼ��
    pModServer->pModeleReset = ModuleServerReset; //ʵ��ģ�鸴λ
    pModServer->pModeleStart = ModuleServerStart; //ʵ��ģ�鿪ʼ
    pModServer->pModeleStop = ModuleServerStop; //ʵ��ģ�����
    pModServer->pModeleRelease = ModuleServerRelease;//ʵ��
    pModServer->pMsgNotify = ServerMsgNotify;//ʵ����Ϣ���д���
    pModServer->pModele10msProcess = ModuleServer10msProcess;
    pModServer->pModele50msProcess = ModuleServer50msProcess;
    pModServer->pModele1sProcess = ModuleServer1sProcess;//ʵ��1s����
    pModServer->pModele1msProcess = ModuleServer1msProcess;//ʵ��1s����
    pModServer->pMsgNotifyProcess = MsgNotifyProcess;//ʵ����Ϣ����			Task_Server����ʱ
    pModServer->pModeleUartProcess = ModuleServerUartProcess;//ʵ��1s����
    //************************����ģ��ӿڱ��븳ֵ******************************

    //************************��ʼ����Ϣ����************************************
    pData->m_pMsgQueue = MsgQueueCreate(pFun, pModServer->m_pBaseData);
//    printf("MsgQueue %d\n",(int)pData->m_pMsgQueue);

    //***************************��ģ������*************************************
    pModServer->pSubModPushBack = SubModPushBack;
    pData->m_pSubMouleList = NULL;

//  PS("CreateModuleServer end");

    return (PMODULEBASE)pModServer;
}

int SubMod1msProcess(int Tag, void* Memory, void* Args)
{
    int ret = 0;
    PSUBMODITEM pSrc = Memory;
//    PSUBMODITEM pDis = Args;
    PMODULEBASE pSubMod = NULL;
    if(pSrc != NULL)
    {
        pSubMod = pSrc->pObj;
        if(pSubMod != NULL && pSubMod->pModele1msProcess!=NULL )
            pSubMod->pModele1msProcess(pSubMod->m_pBaseData);
    }
    return ret;
}

int SubModUartProcess(int Tag, void* Memory, void* Args)
{
    int ret = 0;
    PSUBMODITEM pSrc = Memory;
//    PSUBMODITEM pDis = Args;
    PMODULEBASE pSubMod = NULL;
    if(pSrc != NULL)
    {
        pSubMod = pSrc->pObj;
        if(pSubMod != NULL && pSubMod->pModeleUartProcess!=NULL )
            pSubMod->pModeleUartProcess(pSubMod->m_pBaseData);
    }
    return ret;
}

void ModuleServer1msProcess(void* pArg)
{
    PMODULESERVERDATA pData = (PMODULESERVERDATA)pArg;
    DLLIST *FindAddr = NULL;
    if(pData->m_PressSta == FALSE)
        return;

    DLWalk((DLLIST*)(pData->m_pSubMouleList),&FindAddr,SubMod1msProcess,NULL);
}

void ModuleServerUartProcess(void* pArg)		//10ms����
{
    PMODULESERVERDATA pData = (PMODULESERVERDATA)pArg;
    DLLIST *FindAddr = NULL;
    if(pData->m_PressSta == FALSE)
        return;

    DLWalk((DLLIST*)(pData->m_pSubMouleList),&FindAddr,SubModUartProcess,NULL);
}
