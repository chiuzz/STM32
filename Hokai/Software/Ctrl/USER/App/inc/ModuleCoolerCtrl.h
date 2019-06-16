//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* �� �� �� : ModuleCoolerCtrl.h
//*
//* �ļ����� : �����������ļ�
//*
//* ��    �� : LGL
//* ��    �� :
//* �� �� �� : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MODULE_COOLERCTRL_H__
#define  __MODULE_COOLERCTRL_H__

#include "common.h"
#include "struct_def.h"

typedef enum
{
    COOLER_OFF = 0,
    COOLER_ON,
	  COOLER_START_HOLD,
    COOLER_START,
		COOLER_STOP_HOLD,
    COOLER_STOP,
		COOLER_CON_START
}	eCoolerSMachine;

#define MODE_CHANGE_MIN 0.5
#define MODE_CHANGE_ECHO_SEC 20
#define MODE_CHANGE_TIME (MODE_CHANGE_MIN*60*MODE_CHANGE_ECHO_SEC)
typedef struct ModuleCoolerCtrlData //���������ݽṹ
{
    P_MSGQUEUE m_pMsgQueue;  //��Ϣ����
    INT16U m_Count; //��ʱ��
    BOOLEAN m_PressSta; //�������״̬��¼
//************************��������ģ���ڲ�ʹ�õı�����������Ԫ��******************************//
    PSYSPARAMDATA m_pSysData; //ȫ�ֱ���
		PSYSCONFIGDATA m_pCfgData; //ȫ�ֱ���
		PSYSCALCDATA m_pCalData; //ȫ�ֱ���
		PSYSADJDATA m_pAdjData;
    eCoolerSMachine m_CoolerSMachine;
    INT16U m_CoolCount;
} MODULECOOLERCTRLDATA,*PMODULECOOLERCTRLDATA;

typedef struct ModuleCoolerCtrl //��������
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
} MODULECOOLERCTRL,*PMODULECOOLERCTRL;
//*
//********************************************************************************************************
//* �� �� �� : void CreateModuleCoolerCtrl(void)
//**------------------------------------------------------------------------------------------------------
//* ��    �� : ����ģ��
//**------------------------------------------------------------------------------------------------------
//* ������� : PMODULEBASE. ��ָ��
//**------------------------------------------------------------------------------------------------------
//* ������� : PMODULEBASE. �����ڴ�ռ�󷵻ػ���ָ��
//**------------------------------------------------------------------------------------------------------
//* ��   ��  : PMODULECOOLERCTRLDATA.�����ڴ�ռ�󷵻ػ�������ָ��
//********************************************************************************************************
//*
extern PMODULEBASE CreateModuleCoolerCtrl(PMODULESERVERDATA pServerData);

//************************�ڲ�������ʵ��******************************//
static BOOLEAN ModuleCoolerCtrlInit(void* pArg);
static BOOLEAN ModuleCoolerCtrlReset(void* pArg);
static BOOLEAN ModuleCoolerCtrlStart(void* pArg);
static BOOLEAN ModuleCoolerCtrlStop(void* pArg);
static BOOLEAN ModuleCoolerCtrlRelease(void* pArg);
static void ModuleCoolerCtrl1sProcess(void* pArg);
static void ModuleCoolerCtrl50msProcess(void* pArg);
static void CoolerCtrlMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);

//************************ģ�鹦��ʵ�ֺ���******************************//
static void SetCoolerWORK(void* pArg, eStatus sta);
static void CoolerWorkMachineProc(void* pArg);
static INT16U CalcCoolerTempDip(INT16U Temp, INT16U dsp);
//************************�ڲ�������ʵ��******************************//
#endif
