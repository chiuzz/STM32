//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* �� �� �� : ModuleConfig.h
//*
//* �ļ����� : �����������ļ�
//*
//* ��    �� : LGL
//* ��    �� : 
//* �� �� �� : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MODULE_CONFIG_H__
#define  __MODULE_CONFIG_H__

#include "common.h"
#include "struct_def.h"

typedef enum 
{
    E2PROM_SAVE,
    E2PROM_LOAD
} eConfigProc;

//***************************���屣��ĵ�ַ****************************//
#define ADDRESS_BASE     0x0
#define DATASIZE sizeof(INT16U)
#define ADDRESS_VREF_START (ADDRESS_BASE)
#define ADDRESS_VREF_END (ADDRESS_VREF_START + DATASIZE)
#define ADDRESS_CALCNUM_START (ADDRESS_VREF_END)
#define ADDRESS_CALCNUM_END (ADDRESS_CALCNUM_START + DATASIZE)
#define ADDRESS_MODE_START (ADDRESS_CALCNUM_END)
#define ADDRESS_MODE_END (ADDRESS_MODE_START + DATASIZE)

#define LEN_CALCDATA DATASIZE*TEMPCALDATANUM
#define ADDRESS_CH0AD_START (ADDRESS_MODE_END)
#define ADDRESS_CH0AD_END (ADDRESS_CH0AD_START + LEN_CALCDATA)
#define ADDRESS_CH1AD_START (ADDRESS_CH0AD_END)
#define ADDRESS_CH1AD_END (ADDRESS_CH1AD_START + LEN_CALCDATA)
#define ADDRESS_CH2AD_START (ADDRESS_CH1AD_END)
#define ADDRESS_CH2AD_END (ADDRESS_CH2AD_START + LEN_CALCDATA)
#define ADDRESS_CH3AD_START (ADDRESS_CH2AD_END)
#define ADDRESS_CH3AD_END (ADDRESS_CH3AD_START + LEN_CALCDATA)
#define ADDRESS_CH4AD_START (ADDRESS_CH3AD_END)
#define ADDRESS_CH4AD_END (ADDRESS_CH4AD_START + LEN_CALCDATA)
#define ADDRESS_CH5AD_START (ADDRESS_CH4AD_END)
#define ADDRESS_CH5AD_END (ADDRESS_CH5AD_START + LEN_CALCDATA)
#define ADDRESS_CH6AD_START (ADDRESS_CH5AD_END)
#define ADDRESS_CH6AD_END (ADDRESS_CH6AD_START + LEN_CALCDATA)

#define ADDRESS_CH0TEMP_START (ADDRESS_CH6AD_END)
#define ADDRESS_CH0TEMP_END (ADDRESS_CH0TEMP_START + LEN_CALCDATA)
#define ADDRESS_CH1TEMP_START (ADDRESS_CH0TEMP_END)
#define ADDRESS_CH1TEMP_END (ADDRESS_CH1TEMP_START + LEN_CALCDATA)
#define ADDRESS_CH2TEMP_START (ADDRESS_CH1TEMP_END)
#define ADDRESS_CH2TEMP_END (ADDRESS_CH2TEMP_START + LEN_CALCDATA)
#define ADDRESS_CH3TEMP_START (ADDRESS_CH2TEMP_END)
#define ADDRESS_CH3TEMP_END (ADDRESS_CH3TEMP_START + LEN_CALCDATA)
#define ADDRESS_CH4TEMP_START (ADDRESS_CH3TEMP_END)
#define ADDRESS_CH4TEMP_END (ADDRESS_CH4TEMP_START + LEN_CALCDATA)
#define ADDRESS_CH5TEMP_START (ADDRESS_CH4TEMP_END)
#define ADDRESS_CH5TEMP_END (ADDRESS_CH5TEMP_START + LEN_CALCDATA)
#define ADDRESS_CH6TEMP_START (ADDRESS_CH5TEMP_END)
#define ADDRESS_CH6TEMP_END (ADDRESS_CH6TEMP_START + LEN_CALCDATA)

//#define LEN_CALCDATA_T DATASIZE*TEMPCALDATANUM_TWO
//#define ADDRESS_CH0AD_T_START (ADDRESS_CH6TEMP_END)
//#define ADDRESS_CH0AD_T_END (ADDRESS_CH0AD_T_START + LEN_CALCDATA_T)
//#define ADDRESS_CH1AD_T_START (ADDRESS_CH0AD_T_END)
//#define ADDRESS_CH1AD_T_END (ADDRESS_CH1AD_T_START + LEN_CALCDATA_T)
//#define ADDRESS_CH2AD_T_START (ADDRESS_CH1AD_T_END)
//#define ADDRESS_CH2AD_T_END (ADDRESS_CH2AD_T_START + LEN_CALCDATA_T)
//#define ADDRESS_CH3AD_T_START (ADDRESS_CH2AD_T_END)
//#define ADDRESS_CH3AD_T_END (ADDRESS_CH3AD_T_START + LEN_CALCDATA_T)
//#define ADDRESS_CH4AD_T_START (ADDRESS_CH3AD_T_END)
//#define ADDRESS_CH4AD_T_END (ADDRESS_CH4AD_T_START + LEN_CALCDATA_T)
//#define ADDRESS_CH5AD_T_START (ADDRESS_CH4AD_T_END)
//#define ADDRESS_CH5AD_T_END (ADDRESS_CH5AD_T_START + LEN_CALCDATA_T)
//#define ADDRESS_CH6AD_T_START (ADDRESS_CH5AD_T_END)
//#define ADDRESS_CH6AD_T_END (ADDRESS_CH6AD_T_START + LEN_CALCDATA_T)

//#define ADDRESS_CH0TEMP_T_START (ADDRESS_CH6AD_T_END)
//#define ADDRESS_CH0TEMP_T_END (ADDRESS_CH0TEMP_T_START + LEN_CALCDATA_T)
//#define ADDRESS_CH1TEMP_T_START (ADDRESS_CH0TEMP_T_END)
//#define ADDRESS_CH1TEMP_T_END (ADDRESS_CH1TEMP_T_START + LEN_CALCDATA_T)
//#define ADDRESS_CH2TEMP_T_START (ADDRESS_CH1TEMP_T_END)
//#define ADDRESS_CH2TEMP_T_END (ADDRESS_CH2TEMP_T_START + LEN_CALCDATA_T)
//#define ADDRESS_CH3TEMP_T_START (ADDRESS_CH2TEMP_T_END)
//#define ADDRESS_CH3TEMP_T_END (ADDRESS_CH3TEMP_T_START + LEN_CALCDATA_T)
//#define ADDRESS_CH4TEMP_T_START (ADDRESS_CH3TEMP_T_END)
//#define ADDRESS_CH4TEMP_T_END (ADDRESS_CH4TEMP_T_START + LEN_CALCDATA_T)
//#define ADDRESS_CH5TEMP_T_START (ADDRESS_CH4TEMP_T_END)
//#define ADDRESS_CH5TEMP_T_END (ADDRESS_CH5TEMP_T_START + LEN_CALCDATA_T)
//#define ADDRESS_CH6TEMP_T_START (ADDRESS_CH5TEMP_T_END)
//#define ADDRESS_CH6TEMP_T_END (ADDRESS_CH6TEMP_T_START + LEN_CALCDATA_T)

#define LEN_CALCDATA_E DATASIZE*TEMPCALDATANUM_THE
#define ADDRESS_CH0AD_E_START (ADDRESS_CH6TEMP_END)
#define ADDRESS_CH0AD_E_END (ADDRESS_CH0AD_E_START + LEN_CALCDATA_E)
#define ADDRESS_CH1AD_E_START (ADDRESS_CH0AD_E_END)
#define ADDRESS_CH1AD_E_END (ADDRESS_CH1AD_E_START + LEN_CALCDATA_E)
#define ADDRESS_CH2AD_E_START (ADDRESS_CH1AD_E_END)
#define ADDRESS_CH2AD_E_END (ADDRESS_CH2AD_E_START + LEN_CALCDATA_E)
#define ADDRESS_CH3AD_E_START (ADDRESS_CH2AD_E_END)
#define ADDRESS_CH3AD_E_END (ADDRESS_CH3AD_E_START + LEN_CALCDATA_E)
#define ADDRESS_CH4AD_E_START (ADDRESS_CH3AD_E_END)
#define ADDRESS_CH4AD_E_END (ADDRESS_CH4AD_E_START + LEN_CALCDATA_E)
#define ADDRESS_CH5AD_E_START (ADDRESS_CH4AD_E_END)
#define ADDRESS_CH5AD_E_END (ADDRESS_CH5AD_E_START + LEN_CALCDATA_E)
#define ADDRESS_CH6AD_E_START (ADDRESS_CH5AD_E_END)
#define ADDRESS_CH6AD_E_END (ADDRESS_CH6AD_E_START + LEN_CALCDATA_E)

#define ADDRESS_CH0TEMP_E_START (ADDRESS_CH6AD_E_END)
#define ADDRESS_CH0TEMP_E_END (ADDRESS_CH0TEMP_E_START + LEN_CALCDATA_E)
#define ADDRESS_CH1TEMP_E_START (ADDRESS_CH0TEMP_E_END)
#define ADDRESS_CH1TEMP_E_END (ADDRESS_CH1TEMP_E_START + LEN_CALCDATA_E)
#define ADDRESS_CH2TEMP_E_START (ADDRESS_CH1TEMP_E_END)
#define ADDRESS_CH2TEMP_E_END (ADDRESS_CH2TEMP_E_START + LEN_CALCDATA_E)
#define ADDRESS_CH3TEMP_E_START (ADDRESS_CH2TEMP_E_END)
#define ADDRESS_CH3TEMP_E_END (ADDRESS_CH3TEMP_E_START + LEN_CALCDATA_E)
#define ADDRESS_CH4TEMP_E_START (ADDRESS_CH3TEMP_E_END)
#define ADDRESS_CH4TEMP_E_END (ADDRESS_CH4TEMP_E_START + LEN_CALCDATA_E)
#define ADDRESS_CH5TEMP_E_START (ADDRESS_CH4TEMP_E_END)
#define ADDRESS_CH5TEMP_E_END (ADDRESS_CH5TEMP_E_START + LEN_CALCDATA_E)
#define ADDRESS_CH6TEMP_E_START (ADDRESS_CH5TEMP_E_END)
#define ADDRESS_CH6TEMP_E_END (ADDRESS_CH6TEMP_E_START + LEN_CALCDATA_E)
//*********************************************************************//

#define SAVECOUNT 5

typedef struct ModuleConfigData //���������ݽṹ
{ 
   P_MSGQUEUE m_pMsgQueue;  //��Ϣ���� 
   PCONFIGDATA m_pSysData;     //ϵͳ����
   BOOLEAN m_PressSta; //�������״̬��¼
	 INT8U m_Count;
   
   INT8U m_SaveCount;
   BOOLEAN m_SaveStatus;
   INT8U m_SaveStep;
}MODULECONFIGDATA,*PMODULECONFIGDATA;

typedef struct ModuleConfig //��������
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
}MODULECONFIG,*PMODULECONFIG;
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
extern PMODULEBASE CreateModuleConfig(PMODULESERVERDATA pServerData);

//************************�ڲ�������ʵ��******************************//
static BOOLEAN ModuleConfigInit(void* pArg);
static BOOLEAN ModuleConfigReset(void* pArg);
static BOOLEAN ModuleConfigStart(void* pArg);
static BOOLEAN ModuleConfigStop(void* pArg);
static BOOLEAN ModuleConfigRelease(void* pArg);
static void ModuleConfig1sProcess(void* pArg);
static void ConfigMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf); 

//************************ģ�鹦��ʵ�ֺ���******************************//
static void ConfigSave(void* pArg);

static void ConfigSaveProc(void* pArg);//��������

static void ConfigSave(void* pArg);//�ñ���ʵ�ֺ���
static void ConfigLoad(void* pArg);//��ȡ����ʵ�ֺ���
static void Config_T_Save(void* pArg);//�ñ���ʵ�ֺ���
static void Config_T_Load(void* pArg);//��ȡ����ʵ�ֺ���
static void Config_E_Save(void* pArg);//�ñ���ʵ�ֺ���
static void Config_E_Load(void* pArg);//��ȡ����ʵ�ֺ���
static void ConfigSave_Base(void* pArg);//�ñ���ʵ�ֺ���
static void ConfigLoad_Base(void* pArg);

static void MallocSysData(PMODULECONFIGDATA pData);
//************************�ڲ�������ʵ��******************************//
static void I2CMemSave(INT16U Addres, PVOID pObj, INT16U len);
static void I2CMemLoad(INT16U Addres, PVOID pObj, INT16U len);
static void ModuleConfigPrintInfo(PMODULECONFIGDATA pData);
static void ModuleConfigPrint(INT16U *pData, INT16U len);
#endif
