//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* �� �� �� : ModuleKey.h
//*
//* �ļ����� : �����������ļ�
//*
//* ��    �� : LGL
//* ��    �� :
//* �� �� �� : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MODULE_KEY_H__
#define  __MODULE_KEY_H__

#include "common.h"
#include "struct_def.h"

typedef enum
{
    KEY_STOP = 0,
    KEY_INIT,
    KEY_WORK,
}	eKeyWorkStatus;

typedef enum //У��ģʽ
{
    KEY_OFF = 1,
    KEY_ON,
    KEY_TRI,
    KEY_TRI_MIT,
    KEY_TRI_CAL1,
    KEY_TRI_CAL2,
} eKeyScanMachine;


typedef enum //
{
    BEEP_STOP = 1,
    BEEP_ON,
    BEEP_ON_HOLD,
} eBeepMachine;
#define KEYNUM 11
typedef struct ModuleKeyData //���������ݽṹ
{
    P_MSGQUEUE m_pMsgQueue;  //��Ϣ����
    INT16U m_Count; //��ʱ��
    BOOLEAN m_PressSta; //�������״̬��¼
    PCONFIGDATA m_pSysData;     //ϵͳ����
//************************��������ģ���ڲ�ʹ�õı�����������Ԫ��******************************//
    eKeyWorkStatus m_KeyWorkSta;
    eAlmType m_AlmType;
    BOOLEAN m_AlmStatus;

    INT16U m_BeepCount;
    eBeepMachine m_BeepMac;
    eKeyScanMachine m_KeyScanMachine[KEYNUM];
    INT16U m_KeyMark[KEYNUM];
    INT16U m_KeyCount[KEYNUM];
    INT16U m_KeyLast[KEYNUM];

} MODULEKEYDATA, *PMODULEKEYDATA;

typedef struct ModuleKey //��������
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
    void (*pModele1msProcess)(void* pArg);  //1s��������
    PVOID m_pBaseData;
} MODULEKEY, *PMODULEKEY;
//*
//********************************************************************************************************
//* �� �� �� : void CreateModuleKey(void)
//**------------------------------------------------------------------------------------------------------
//* ��    �� : ����ģ��
//**------------------------------------------------------------------------------------------------------
//* ������� : PMODULEBASE. ��ָ��
//**------------------------------------------------------------------------------------------------------
//* ������� : PMODULEBASE. �����ڴ�ռ�󷵻ػ���ָ��
//**------------------------------------------------------------------------------------------------------
//* ��   ��  : PMODULEKEYDATA.�����ڴ�ռ�󷵻ػ�������ָ��
//********************************************************************************************************
//*
extern PMODULEBASE CreateModuleKey(PMODULESERVERDATA pServerData);

//************************�ڲ�������ʵ��******************************//
static BOOLEAN ModuleKeyInit(void* pArg);
static BOOLEAN ModuleKeyReset(void* pArg);
static BOOLEAN ModuleKeyStart(void* pArg);
static BOOLEAN ModuleKeyStop(void* pArg);
static BOOLEAN ModuleKeyRelease(void* pArg);
static void ModuleKey1sProcess(void* pArg);
static void ModuleKey50msProcess(void* pArg);
static void ModuleKey10msProcess(void* pArg);
static void KeyMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);

//************************ģ�鹦��ʵ�ֺ���******************************//
static void GetButtonKey(void* pArg);//��ȡ����
static void BeepTriger(void* pArg);
static void KeyProcess(void* pArg, INT8U val, INT8U index);

static void PrintfKeyNum(INT16U index);
//************************�ڲ�������ʵ��******************************//
#endif
