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
    CONFIG_STOP = 0,
		CONFIG_INIT,
		CONFIG_SAVE_START,
		CALC_SAVE_START,
		ADJ_SAVE_START,
		CONFIG_CFG_SAVE,
}	eConfigMachine;

typedef struct ModuleConfigData //���������ݽṹ
{
    P_MSGQUEUE m_pMsgQueue;  //��Ϣ����
    INT16U m_Count; //��ʱ��
    BOOLEAN m_PressSta; //�������״̬��¼
//************************��������ģ���ڲ�ʹ�õı�����������Ԫ��******************************//
    PSYSPARAMDATA m_pSysData;
		PSYSCONFIGDATA m_pCfgData; //ȫ�ֱ���
		PSYSCALCDATA m_pCalData; //ȫ�ֱ���
		PSYSADJDATA m_pAdjData;
		INT16U m_Temp;
		eConfigMachine m_ConfigMac;
		BOOLEAN m_ConfigEffective;
		BOOLEAN m_ConfigSaveable;
} MODULECONFIGDATA,*PMODULECONFIGDATA;

typedef struct ModuleConfig //��������
{
    char m_ModName[16];
    BOOLEAN (*pModeleInit)(void* pArg); //��ʼ�� ����m_pBaseData
    BOOLEAN (*pModeleReset)(void* pArg); //��λ ����m_pBaseData
    BOOLEAN (*pModeleStart)(void* pArg); //��ʼ ����m_pBaseData
    BOOLEAN (*pModeleStop)(void* pArg); //ֹͣ ����m_pBaseData
    BOOLEAN (*pModeleRelease)(void* pArg); //�ͷ� ����m_pBaseData
    void (*pMsgNotify)(PVOID pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf); //��Ϣ���� ������
    void (*pModele1msProcess)(void* pArg); //1ms��������
    void (*pModele10msProcess)(void* pArg); //10ms��������
    void (*pModele50msProcess)(void* pArg); //50ms��������
    void (*pModele1sProcess)(void* pArg);  //1s��������
    void (*pModeleUartProcess)(void* pArg);  //1s��������
    PVOID m_pBaseData;
} MODULECONFIG,*PMODULECONFIG;
//*
//********************************************************************************************************
//* �� �� �� : void CreateModuleConfig(void)
//**------------------------------------------------------------------------------------------------------
//* ��    �� : ����ģ��
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
void  ReadMemConfig(PMODULECONFIGDATA pData);   //��ȡ����
void  ReadMemCalc(PMODULECONFIGDATA pData);   //��ȡ����
void  ReadMemAdj(PMODULECONFIGDATA pData);   //��ȡ����
void  WriteMemConfig(PMODULECONFIGDATA pData); //д������
void  WriteMemCalc(PMODULECONFIGDATA pData); //д������
void  WriteMemAdj(PMODULECONFIGDATA pData); //д������
//************************�ڲ�������ʵ��******************************//
static void I2CMemSave(INT16U Addres, PVOID pObj, INT16U len);
static void I2CMemLoad(INT16U Addres, PVOID pObj, INT16U len);

static BOOLEAN TestE2PROM(INT16U D);
static BOOLEAN ChackCalcData(PMODULECONFIGDATA pData);
static BOOLEAN ChackConfigData(PMODULECONFIGDATA pData);
static BOOLEAN ChackAdjData(PMODULECONFIGDATA pData);
static void CalceDataInit(PMODULECONFIGDATA pData);
static void ConfigDataInit(PMODULECONFIGDATA pData);
static void AdjDataInit(PMODULECONFIGDATA pData);
static void ConfigMachineProc(void* pArg);
//***************************???????****************************//
#define ADDRESS_BASE     0x0
#define DATASIZE sizeof(INT16U)
///////////////����1���õ�ַ///////////////////
#define ADDRESS_TEMP1SET_START (ADDRESS_BASE)
#define ADDRESS_TEMP1SET_END (ADDRESS_TEMP1SET_START + DATASIZE)
///////////////����2���õ�ַ///////////////////
#define ADDRESS_TEMP2SET_START (ADDRESS_TEMP1SET_END)
#define ADDRESS_TEMP2SET_END (ADDRESS_TEMP2SET_START + DATASIZE)
///////////////ˮ��2���õ�ַ///////////////////
#define ADDRESS_TEMPWATERSET_START (ADDRESS_TEMP2SET_END)
#define ADDRESS_TEMPWATERSET_END (ADDRESS_TEMPWATERSET_START + DATASIZE)
///////////////CH1ADУ׼���õ�ַ///////////////////
#define ADDRESS_CH1ADARR_START (ADDRESS_TEMPWATERSET_END)
#define ADDRESS_CH1ADARR_END (ADDRESS_CH1ADARR_START + DATASIZE*ADCALCDATANUM)
#define ADDRESS_CH1TEMPARR_START (ADDRESS_CH1ADARR_END)
#define ADDRESS_CH1TEMPARR_END (ADDRESS_CH1TEMPARR_START + DATASIZE*ADCALCDATANUM)
///////////////CH2ADУ׼���õ�ַ///////////////////
#define ADDRESS_CH2ADARR_START (ADDRESS_CH1TEMPARR_END)
#define ADDRESS_CH2ADARR_END (ADDRESS_CH2ADARR_START + DATASIZE*ADCALCDATANUM)
#define ADDRESS_CH2TEMPARR_START (ADDRESS_CH2ADARR_END)
#define ADDRESS_CH2TEMPARR_END (ADDRESS_CH2TEMPARR_START + DATASIZE*ADCALCDATANUM)
///////////////CH3ADУ׼���õ�ַ///////////////////
#define ADDRESS_CH3ADARR_START (ADDRESS_CH2TEMPARR_END)
#define ADDRESS_CH3ADARR_END (ADDRESS_CH3ADARR_START + DATASIZE*ADCALCDATANUM)
#define ADDRESS_CH3TEMPARR_START (ADDRESS_CH3ADARR_END)
#define ADDRESS_CH3TEMPARR_END (ADDRESS_CH3TEMPARR_START + DATASIZE*ADCALCDATANUM)
///////////////sen1ADУ׼���õ�ַ///////////////////
#define ADDRESS_SEN1ADARR_START (ADDRESS_CH3TEMPARR_END)
#define ADDRESS_SEN1ADARR_END (ADDRESS_SEN1ADARR_START + DATASIZE*SENCALCDATANUM)
#define ADDRESS_SEN1TEMPARR_START (ADDRESS_SEN1ADARR_END)
#define ADDRESS_SEN1TEMPARR_END (ADDRESS_SEN1TEMPARR_START + DATASIZE*SENCALCDATANUM)
///////////////sen2ADУ׼���õ�ַ///////////////////
#define ADDRESS_SEN2ADARR_START (ADDRESS_SEN1TEMPARR_END)
#define ADDRESS_SEN2ADARR_END (ADDRESS_SEN2ADARR_START + DATASIZE*SENCALCDATANUM)
#define ADDRESS_SEN2TEMPARR_START (ADDRESS_SEN2ADARR_END)
#define ADDRESS_SEN2TEMPARR_END (ADDRESS_SEN2TEMPARR_START + DATASIZE*SENCALCDATANUM)
///����ģʽ�µ���������,ˮ������
///////////////����1���õ�ַ///////////////////
#define ADDRESS_HOT_TEMP1SET_START (ADDRESS_SEN2TEMPARR_END)
#define ADDRESS_HOT_TEMP1SET_END (ADDRESS_HOT_TEMP1SET_START + DATASIZE)
///////////////����2���õ�ַ///////////////////
#define ADDRESS_HOT_TEMP2SET_START (ADDRESS_HOT_TEMP1SET_END)
#define ADDRESS_HOT_TEMP2SET_END (ADDRESS_HOT_TEMP2SET_START + DATASIZE)
///////////////ˮ��2���õ�ַ///////////////////
#define ADDRESS_HOT_TEMPWATERSET_START (ADDRESS_HOT_TEMP2SET_END)
#define ADDRESS_HOT_TEMPWATERSET_END (ADDRESS_HOT_TEMPWATERSET_START + DATASIZE)

///����ģʽ��
///////////////����1���õ�ַ///////////////////
#define ADDRESS_COOL_TEMP1SET_START (ADDRESS_HOT_TEMPWATERSET_END)
#define ADDRESS_COOL_TEMP1SET_END (ADDRESS_COOL_TEMP1SET_START + DATASIZE)
///////////////����2���õ�ַ///////////////////
#define ADDRESS_COOL_TEMP2SET_START (ADDRESS_COOL_TEMP1SET_END)
#define ADDRESS_COOL_TEMP2SET_END (ADDRESS_COOL_TEMP2SET_START + DATASIZE)
///////////////ˮ��2���õ�ַ///////////////////
#define ADDRESS_COOL_TEMPWATERSET_START (ADDRESS_COOL_TEMP2SET_END)
#define ADDRESS_COOL_TEMPWATERSET_END (ADDRESS_COOL_TEMPWATERSET_START + DATASIZE)
//��¼�ǵ�̺ģʽ,����˫̺ģʽsingleMode
#define ADDRESS_SINGLEMODE_START (ADDRESS_COOL_TEMPWATERSET_END)
#define ADDRESS_SINGLEMODE_END (ADDRESS_SINGLEMODE_START + DATASIZE)

#define ADDRESS_SYSWORKMODE_START (ADDRESS_SINGLEMODE_END)
#define ADDRESS_SYSWORKMODE_END (ADDRESS_SYSWORKMODE_START + DATASIZE)

#define ADDRESS_CYCLE1SET_START (ADDRESS_SYSWORKMODE_END)
#define ADDRESS_CYCLE1SET_END (ADDRESS_CYCLE1SET_START + DATASIZE)

#define ADDRESS_CYCLE2SET_START (ADDRESS_CYCLE1SET_END)
#define ADDRESS_CYCLE2SET_END (ADDRESS_CYCLE2SET_START + DATASIZE)

#define ADDRESS_ALMVOL_START (ADDRESS_CYCLE2SET_END)
#define ADDRESS_ALMVOL_END (ADDRESS_ALMVOL_START + DATASIZE)
///////////////����1У׼���õ�ַ////////////////
#define ADDRESS_CAL1SET_START (ADDRESS_ALMVOL_END)
#define ADDRESS_CAL1SET_END (ADDRESS_CAL1SET_START + DATASIZE)
///////////////����2У׼���õ�ַ////////////////
#define ADDRESS_CAL2SET_START (ADDRESS_CAL1SET_END)
#define ADDRESS_CAL2SET_END (ADDRESS_CAL2SET_START + DATASIZE)

#define ADDRESS_END     ADDRESS_CAL2SET_END
#endif
