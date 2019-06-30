//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* �� �� �� : ModuleServer.h
//*
//* �ļ����� : �����������ļ� ʵ�ֵ��ȣ���Ϣ���У�ģ������
//*
//* ��    �� : LGL
//* ��    �� :
//* �� �� �� : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MODULE_SERVER_H__
#define  __MODULE_SERVER_H__

#include "common.h"
#include "struct_def.h"


typedef struct SubModItem  //����Ԫ��
{
    PMODULEBASE pObj;
    INT8U tags;
} SUBMODITEM,*PSUBMODITEM;

typedef struct ModuleServer //��������
{
    char m_ModName[16];
    BOOLEAN (*pModeleInit)(void* pArg); //��ʼ�� ����m_pBaseData
    BOOLEAN (*pModeleReset)(void* pArg); //��λ ����m_pBaseData
    BOOLEAN (*pModeleStart)(void* pArg); //��ʼ ����m_pBaseData
    BOOLEAN (*pModeleStop)(void* pArg); //ֹͣ ����m_pBaseData
    BOOLEAN (*pModeleRelease)(void* pArg); //�ͷ� ����m_pBaseData
    void (*pMsgNotify)(PVOID pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf); //��Ϣ���� ������
    void (*pModele10msProcess)(void* pArg); //10ms��������
    void (*pModele50msProcess)(void* pArg); //50ms��������
    void (*pModele1sProcess)(void* pArg);  //1s��������
    void (*pModele1msProcess)(void* pArg);  //1ms��������
    PVOID m_pBaseData;
    void (*pMsgNotifyProcess)(PVOID pArg);
    void (*pSubModPushBack)(PVOID pArg, PSUBMODITEM pObj);
} MODULESERVER,*PMODULESERVER;

//*
//********************************************************************************************************
//* �� �� �� : void CreateModuleConfig(void)
//**------------------------------------------------------------------------------------------------------
//* ��    �� : �������ù���ģ��
//**------------------------------------------------------------------------------------------------------
//* ������� : PMODULEBASE. ��ָ��
//**------------------------------------------------------------------------------------------------------
//* ������� : PMODULEBASE. �����ڴ�ռ�󷵻ػ���ָ��
//**------------------------------------------------------------------------------------------------------
//* ��   ��  : PMODULECONFIGDATA.�����ڴ�ռ�󷵻ػ�������ָ��
//********************************************************************************************************
//*
extern PMODULEBASE CreateModuleServer(void);

//************************�ڲ���������ʵ��******************************//
static BOOLEAN ModuleServerInit(void* pArg);
static BOOLEAN ModuleServerReset(void* pArg);
static BOOLEAN ModuleServerStart(void* pArg);
static BOOLEAN ModuleServerStop(void* pArg);
static BOOLEAN ModuleServerRelease(void* pArg);
static void ModuleServer10msProcess(void* pArg);
static void ModuleServer50msProcess(void* pArg);
static void ModuleServer1sProcess(void* pArg);
static void ModuleServer1msProcess(void* pArg);
static void ServerMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);
static void MsgNotifyProcess(PVOID pArg);

static void SubModPushBack(PVOID pArg, PSUBMODITEM pObj);
static int SubModReset(int Tag, void* Memory, void* Args);
static int SubModStart(int Tag, void* Memory, void* Args);
static int SubModStop(int Tag, void* Memory, void* Args);
static int SubModRelease(int Tag, void* Memory, void* Args);
static int SubMod10msProcess(int Tag, void* Memory, void* Args);
static int SubMod1msProcess(int Tag, void* Memory, void* Args);
static int SubMod50msProcess(int Tag, void* Memory, void* Args);
static int SubMod1sProcess(int Tag, void* Memory, void* Args);
static int SubModMsgNotify(int Tag, void* Memory, void* Args);
//************************ģ�鹦��ʵ�ֺ���******************************//
//static void ConfigSave();//�ñ���ʵ�ֺ���
//************************�ڲ���������ʵ��******************************//
#endif