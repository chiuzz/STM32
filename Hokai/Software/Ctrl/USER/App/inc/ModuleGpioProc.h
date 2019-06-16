//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* �� �� �� : ModuleGpioProc.h
//*
//* �ļ����� : �����������ļ�
//*
//* ��    �� : LGL
//* ��    �� :
//* �� �� �� : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MODULE_GPIOPROC_H__
#define  __MODULE_GPIOPROC_H__

#include "common.h"
#include "struct_def.h"



typedef enum
{
    BUMP_WORK_OFF = 0,
    BUMP_WORK_ON,
    BUMP_WORK_STOP,
    BUMP_WORK_START,
}	eBumpWorkMachine;

typedef struct ModuleGpioProcData //���������ݽṹ
{
    P_MSGQUEUE m_pMsgQueue;  //��Ϣ����
    INT16U m_Count; //��ʱ��
    BOOLEAN m_PressSta; //�������״̬��¼
    //************************��������ģ���ڲ�ʹ�õı�����������Ԫ��******************************//
    PSYSPARAMDATA m_pSysData; //ȫ�ֱ���
    PSYSCONFIGDATA m_pCfgData; //ȫ�ֱ���
		PSYSCALCDATA m_pCalData; //ȫ�ֱ���
		PSYSADJDATA m_pAdjData;
    INT16U m_Count50ms;
    eBumpWorkMachine m_Bump1WorkMac;
    eBumpWorkMachine m_Bump2WorkMac;

} MODULEGPIOPROCDATA, *PMODULEGPIOPROCDATA;

typedef struct ModuleGpioProc //��������
{
    char m_ModName[16];
    BOOLEAN (*pModeleInit)(void* pArg); //��ʼ�� ����m_pBaseData
    BOOLEAN (*pModeleReset)(void* pArg); //��λ ����m_pBaseData
    BOOLEAN (*pModeleStart)(void* pArg); //��ʼ ����m_pBaseData
    BOOLEAN (*pModeleStop)(void* pArg); //ֹͣ ����m_pBaseData
    BOOLEAN (*pModeleRelease)(void* pArg); //�ͷ� ����m_pBaseData
    void (*pMsgNotify)(PVOID pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf); //��Ϣ���� ������
    void (*pModele1msProcess)(void* pArg); //1ms�������
    void (*pModele10msProcess)(void* pArg); //10ms��������
    void (*pModele50msProcess)(void* pArg); //50ms��������
    void (*pModele1sProcess)(void* pArg);  //1s��������
    void (*pModeleUartProcess)(void* pArg);  //1s��������
    PVOID m_pBaseData;
} MODULEGPIOPROC, *PMODULEGPIOPROC;
//*
//********************************************************************************************************
//* �� �� �� : void CreateModuleGpioProc(void)
//**------------------------------------------------------------------------------------------------------
//* ��    �� : ����ģ��
//**------------------------------------------------------------------------------------------------------
//* ������� : PMODULEBASE. ��ָ��
//**------------------------------------------------------------------------------------------------------
//* ������� : PMODULEBASE. �����ڴ�ռ�󷵻ػ���ָ��
//**------------------------------------------------------------------------------------------------------
//* ��   ��  : PMODULEGPIOPROCDATA.�����ڴ�ռ�󷵻ػ�������ָ��
//********************************************************************************************************
//*
extern PMODULEBASE CreateModuleGpioProc(PMODULESERVERDATA pServerData);

//************************�ڲ�������ʵ��******************************//
static BOOLEAN ModuleGpioProcInit(void* pArg);
static BOOLEAN ModuleGpioProcReset(void* pArg);
static BOOLEAN ModuleGpioProcStart(void* pArg);
static BOOLEAN ModuleGpioProcStop(void* pArg);
static BOOLEAN ModuleGpioProcRelease(void* pArg);
static void ModuleGpioProc10msProcess(void* pArg);
static void ModuleGpioProc1sProcess(void* pArg);
static void ModuleGpioProc50msProcess(void* pArg);
static void GpioProcMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);

//************************ģ�鹦��ʵ�ֺ���******************************//
//��ȡϵͳ״̬
void GetModuleGpioStatus(PMODULEGPIOPROCDATA pData);

//************************�ڲ�������ʵ��******************************//
static void Bump1WorkMachineProc(void* pArg);
static void Bump2WorkMachineProc(void* pArg);
#endif

