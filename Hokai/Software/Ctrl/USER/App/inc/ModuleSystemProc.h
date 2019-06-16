//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* �� �� �� : ModuleSystemProc.h
//*
//* �ļ����� : �����������ļ�
//*
//* ��    �� : LGL
//* ��    �� :
//* �� �� �� : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MODULE_SYSTEMPROC_H__
#define  __MODULE_SYSTEMPROC_H__

#define SINGLEMODE 1
#include "common.h"
#include "struct_def.h"

typedef enum
{
    SYSTEM_CHECK = 0,
    SYSTEM_CHEKC_E2PROM,
    SYSTEM_CHEKC_E2PROM_HOLD,
    SYSTEM_MONITOR,
}	eSystemMachine;

typedef enum
{
    SYSTEM_STOP = 0,
    SYSTEM_STOP_HOLD,
    SYSTEM_COOLER,
    SYSTEM_COOLER_HOLD,
    SYSTEM_HEATER,
    SYSTEM_HEATER_HOLD,
    SYSTEM_INVALID = 255,
}	eSystemWorkStatus;

typedef enum
{
    BUMP_STOP = 0,
    BUMP_STOP_HOLD,
    BUMP_START,
    BUMP_START_HOLD,
    BUMP_INVALID = 255,
}	eBumpWorkStatus;

typedef struct ModuleSystemProcData //���������ݽṹ
{
    P_MSGQUEUE m_pMsgQueue;  //��Ϣ����
    INT16U m_Count; //��ʱ��
    BOOLEAN m_PressSta; //�������״̬��¼
//************************��������ģ���ڲ�ʹ�õı�����������Ԫ��******************************//
    INT16U m_Float1Count; //��ʱ��
    INT16U m_Float2Count; //��ʱ��
    PSYSPARAMDATA m_pSysData; //ȫ�ֱ���
    PSYSCONFIGDATA m_pCfgData; //ȫ�ֱ���
    PSYSCALCDATA m_pCalData; //ȫ�ֱ���
    PSYSADJDATA m_pAdjData;
    eSystemMachine m_SystemMAC;
    eSystemWorkStatus m_SystemWorkSta;
    eBumpWorkStatus m_Bump1Sta;
    eBumpWorkStatus m_Bump2Sta;
    BOOLEAN m_WorkModePressKey; //����״̬
    BOOLEAN m_Bump1PressKey; //����״̬
    BOOLEAN m_Bump2PressKey; //����״̬
    BOOLEAN m_E2PROMERROR;

} MODULESYSTEMPROCDATA, *PMODULESYSTEMPROCDATA;

typedef struct ModuleSystemProc //��������
{
    char m_ModName[16];
    BOOLEAN (*pModeleInit)(void* pArg); //��ʼ�� ����m_pBaseData
    BOOLEAN (*pModeleReset)(void* pArg); //��λ ����m_pBaseData
    BOOLEAN (*pModeleStart)(void* pArg); //��ʼ ����m_pBaseData
    BOOLEAN (*pModeleStop)(void* pArg); //ֹͣ ����m_pBaseData
    BOOLEAN (*pModeleRelease)(void* pArg); //�ͷ� ����m_pBaseData
    void (*pMsgNotify)(PVOID pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf); //��Ϣ���� ������
    void (*pModele1msProcess)(void* pArg); //10ms������?
    void (*pModele10msProcess)(void* pArg); //10ms��������
    void (*pModele50msProcess)(void* pArg); //50ms��������
    void (*pModele1sProcess)(void* pArg);  //1s��������
    void (*pModeleUartProcess)(void* pArg);  //1s��������
    PVOID m_pBaseData;
} MODULESYSTEMPROC, *PMODULESYSTEMPROC;

//*
//********************************************************************************************************
//* �� �� �� : void CreateModuleSystemProc(void)
//**------------------------------------------------------------------------------------------------------
//* ��    �� : ����ģ��
//**------------------------------------------------------------------------------------------------------
//* ������� : PMODULEBASE. ��ָ��
//**------------------------------------------------------------------------------------------------------
//* ������� : PMODULEBASE. �����ڴ�ռ�󷵻ػ���ָ��
//**------------------------------------------------------------------------------------------------------
//* ��   ��  : PMODULESYSTEMPROCDATA.�����ڴ�ռ�󷵻ػ�������ָ��
//********************************************************************************************************
//*
extern PMODULEBASE CreateModuleSystemProc(PMODULESERVERDATA pServerData);

//************************�ڲ�������ʵ��******************************//
static BOOLEAN ModuleSystemProcInit(void* pArg);
static BOOLEAN ModuleSystemProcReset(void* pArg);
static BOOLEAN ModuleSystemProcStart(void* pArg);
static BOOLEAN ModuleSystemProcStop(void* pArg);
static BOOLEAN ModuleSystemProcRelease(void* pArg);
static void ModuleSystemProc1sProcess(void* pArg);
static void SystemProcMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);

//************************ģ�鹦��ʵ�ֺ���******************************//
void SetSysAlm(PMODULESYSTEMPROCDATA pData);

//************************�ڲ�������ʵ��******************************//

static void SystemMachineProc(void* pArg);
static void SystemWorkStatusProc(void* pArg);
static void Bump1WorkStatusProc(void* pArg);
static void Bump2WorkStatusProc(void* pArg);
static void SystemMonitor(void* pArg);
static void GetWaterStatus(void* pArg);

static void TrigerAddSet(PMODULESYSTEMPROCDATA pData);//������
static void TrigerDecSet(PMODULESYSTEMPROCDATA pData);//������
static void TrigerTemp1Set(PMODULESYSTEMPROCDATA pData);
static void TrigerTemp2Set(PMODULESYSTEMPROCDATA pData);
static void TrigerTempWaterSet(PMODULESYSTEMPROCDATA pData);
static BOOLEAN SetFocusStatus(PMODULESYSTEMPROCDATA pData, eFocusStatus Focus);
static void TrigerAlmvolSet(PMODULESYSTEMPROCDATA pData);
static void TrigerCal1Set(PMODULESYSTEMPROCDATA pData);
static void TrigerCal2Set(PMODULESYSTEMPROCDATA pData);
#endif
