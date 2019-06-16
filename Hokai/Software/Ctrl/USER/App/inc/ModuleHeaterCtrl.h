//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* �� �� �� : ModuleHeaterCtrl.h
//*
//* �ļ����� : �����������ļ�
//*
//* ��    �� : LGL
//* ��    �� :
//* �� �� �� : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MODULE_HEATERCTRL_H__
#define  __MODULE_HEATERCTRL_H__

#include "common.h"
#include "struct_def.h"

typedef enum
{
    HEATER_STOP = 0,
    HEATER_STEP_START,
    HEATER_STEP_WORK,
    HEATER_STEP_WORK_ON,
    HEATER_STEP_WORK_UP,
    HEATER_STEP_WORK_DOWN,
    HEATER_STEP_WORK_COM_UP,
}	eHeaterSMachine;


typedef enum
{
    ALM_STOP = 0,
    ALM_START,
    ALM_MONITOR,
} eHeaterAlmMachine;

#define HEATERALMNUM 2
typedef struct ModuleHeaterCtrlData //���������ݽṹ
{
    P_MSGQUEUE m_pMsgQueue;  //��Ϣ����
    INT16U m_Count; //��ʱ��
    INT16U m_Count2; //��ʱ��2
    BOOLEAN m_PressSta; //�������״̬��¼
//************************��������ģ���ڲ�ʹ�õı�����������Ԫ��******************************//
    PSYSPARAMDATA m_pSysData; //ȫ�ֱ���
    PSYSCONFIGDATA m_pCfgData; //ȫ�ֱ���
    PSYSCALCDATA m_pCalData; //ȫ�ֱ���
    PSYSADJDATA m_pAdjData;
    eHeaterSMachine m_HeaterSMachine;
    eHeaterAlmMachine m_HeaterAlmMac[HEATERALMNUM];
    INT16S m_ErrSum;
    INT16U m_ProcCount;
} MODULEHEATERCTRLDATA,*PMODULEHEATERCTRLDATA;

typedef struct ModuleHeaterCtrl //��������
{
    char m_ModName[16];
    BOOLEAN (*pModeleInit)(void* pArg); //��ʼ�� ����m_pBaseData
    BOOLEAN (*pModeleReset)(void* pArg); //��λ ����m_pBaseData
    BOOLEAN (*pModeleStart)(void* pArg); //��ʼ ����m_pBaseData
    BOOLEAN (*pModeleStop)(void* pArg); //ֹͣ ����m_pBaseData
    BOOLEAN (*pModeleRelease)(void* pArg); //�ͷ� ����m_pBaseData
    void (*pMsgNotify)(PVOID pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf); //��Ϣ���� ������
    void (*pModele1msProcess)(void* pArg); //10ms�������
    void (*pModele10msProcess)(void* pArg); //10ms��������
    void (*pModele50msProcess)(void* pArg); //50ms��������
    void (*pModele1sProcess)(void* pArg);  //1s��������
    void (*pModeleUartProcess)(void* pArg);  //1s��������
    PVOID m_pBaseData;
} MODULEHEATERCTRL,*PMODULEHEATERCTRL;
//*
//********************************************************************************************************
//* �� �� �� : void CreateModuleHeaterCtrl(void)
//**------------------------------------------------------------------------------------------------------
//* ��    �� : ����ģ��
//**------------------------------------------------------------------------------------------------------
//* ������� : PMODULEBASE. ��ָ��
//**------------------------------------------------------------------------------------------------------
//* ������� : PMODULEBASE. �����ڴ�ռ�󷵻ػ���ָ��
//**------------------------------------------------------------------------------------------------------
//* ��   ��  : PMODULEHEATERCTRLDATA.�����ڴ�ռ�󷵻ػ�������ָ��
//********************************************************************************************************
//*
extern PMODULEBASE CreateModuleHeaterCtrl(PMODULESERVERDATA pServerData);

//************************�ڲ�������ʵ��******************************//
static BOOLEAN ModuleHeaterCtrlInit(void* pArg);
static BOOLEAN ModuleHeaterCtrlReset(void* pArg);
static BOOLEAN ModuleHeaterCtrlStart(void* pArg);
static BOOLEAN ModuleHeaterCtrlStop(void* pArg);
static BOOLEAN ModuleHeaterCtrlRelease(void* pArg);
static void ModuleHeaterCtrl1sProcess(void* pArg);
static void ModuleHeaterCtrl50msProcess(void* pArg);
static void HeaterCtrlMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);

//************************ģ�鹦��ʵ�ֺ���******************************//
static void SetHeaterWORK(void* pArg, eStatus sta);
static void HeaterWorkMachineProc(void* pArg);
static void HeaterAlmMachineProc(void* pArg,INT16U index); //ÿ1s����
//************************�ڲ�������ʵ��******************************//
#endif
