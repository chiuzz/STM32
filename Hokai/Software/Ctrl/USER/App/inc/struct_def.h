//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* �� �� �� : struct_def.h
//*
//* �ļ����� : ϵͳ�ṹ�����ļ�
//*
//* ��    �� : LGL
//* ��    �� :
//* �� �� �� : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __STRUCT_DEF_H__
#define  __STRUCT_DEF_H__

#include "common.h"

#define INVALID_8BIT_VOL 0xff
#define INVALID_16BIT_VOL 0xffff

//typedef struct Struct
//{}STRUCT,*PSTRUCT;
//typedef enum {FALSE = 0, TRUE = !FALSE} bool;

typedef enum
{
    check = 0,
    Stop,
    Cooler,
    Heater,
}	eSystemStatus;

typedef enum
{
    Status_Off = 0, //2017-5-22tommy ������ԭ����On = 1��Off=2,��������on=1��off=0��
    Status_On = 1,
}	eStatus;

typedef enum
{
    Status_I = 0,
    Status_II,
    Status_III,
}	eNoStatus;

typedef enum
{
    NoFocus = 0,
    Temp1Focus,//��������1
    Temp2Focus,//ˮ������
    TempWFocus,//��������2
    AlmVolFocus,//������������
    Cal1Focus,//����У׼����1
    Cal2Focus,//����У׼����2
}	eFocusStatus;

#define ADCALCDATANUM 2
#define SENCALCDATANUM 5
//*********************************************************************************************************
typedef struct SysParamData
{
    //״̬��Ϣ
    eStatus m_Float1Status;	//ˮ·ˮ������1״̬
    eStatus m_Float2Status;	//ˮ·ˮ������2״̬
    eNoStatus m_WaterStatus; //ˮλI,II,III
    eStatus m_Bump1Status; //ˮ��1״̬
    eStatus m_Bump2Status; //ˮ��2״̬
    eStatus m_Cooler; //����״̬
    eStatus m_Heater; //����״̬
    eFocusStatus m_FocusStatus; //����״̬  0-�޽��� 1-6����

    //������Ϣ
    eStatus m_Sensor1OFF; //���������� Status_On-����
    eStatus m_Sensor2OFF; //���������� Status_On-����
    eStatus m_HeaterPOWER; //�������쳣 Status_On-����
    eStatus m_WaterHIGH; //ˮ�³�����״̬ Status_On-����
    eStatus m_WaterTLow; //ˮ�³�����״̬ Status_On-����
    eStatus m_E2PROMERR;//e2prom���� Status_On-����
    eStatus m_WaterLow;//ˮλ��״̬ Status_On-����
    eStatus m_HeaterModeWT1Low; //����ģʽ�£��趨ˮ�µ������� Status_On-����
    eStatus m_HeaterModeWT2Low; //����ģʽ�£��趨ˮ�µ������� Status_On-����
    eStatus m_HeaterModeT1ALM; //����ģʽ�£�����1���ޱ���
    eStatus m_HeaterModeT2ALM; //����ģʽ�£�����2���ޱ���
    eStatus	m_Cycle1Alm; //Һ·1����
    eStatus	m_Cycle2Alm;//Һ·2����
    //������Ϣ
    INT16U m_Temp1;	//����1 �¶�x1000 35551=35.551��
    INT16U m_Temp2;	//����2 �¶�x1000 35551=35.551��
    INT16U m_WaterTemp; //ˮ�� �¶�x100 3555=35.55��
    //�趨������Ϣ
    INT16U m_Temp1Set;	  //����1����ֵ �¶�X10 ����0.5�� 35.5��=355
    INT16U m_Temp2Set;	  //����2����ֵ �¶�X10 ����0.5�� 35.5��=355
    INT16U m_WaterTempSet; //ˮ������ֵ �¶� ����1�� 35��=35
    INT16U m_AlmVolSet; 	//��������ֵ ����1
    INT8S	 m_Cal1Set;			//ˮ��1У׼ֵ
    INT8S	 m_Cal2Set;			//ˮ��2У׼ֵ

//	INT16U m_SystemAlm; //ϵͳ����״̬

    /////////////////Ӳ��У׼����ֵ���������������ݼ�����ȡ/////////////////////
    FP32 m_AD1CalcK; //AD1У׼ֵ
    FP32 m_AD1CalcB; //AD1У׼ֵ
    FP32 m_AD2CalcK; //AD1У׼ֵ
    FP32 m_AD2CalcB; //AD1У׼ֵ
    FP32 m_AD3CalcK; //AD1У׼ֵ
    FP32 m_AD3CalcB; //AD1У׼ֵ

    //////����1��̺ģʽ,����˫̺ģʽ0,

} SYSPARAMDATA,*PSYSPARAMDATA;

#define ALM_LEVEL_LOW 1
#define ALM_LEVEL_MID 2
#define ALM_LEVEL_HIG 3
#define TEMPCALMAX		10			//����У׼���ֵ
#define TEMPCALMIN		-10			//����У׼��Сֵ

typedef struct SysConfigData
{
    ///////////////////////ϵͳ״̬���ݣ�������ʼ������/////////////////////////
    eSystemStatus m_SystemSta;//ϵͳ����״̬
    eStatus m_Cycle1Set;	//ˮ·1״̬
    eStatus m_Cycle2Set;	//ˮ·2״̬
    ///////////////////////ϵͳ�������ݣ�������E2PROM��ȡ/////////////////////////
    INT16U m_Temp1Set_Hot;	  //����1����ֵ �¶�X10 ����0.5�� 35.5��=355
    INT16U m_Temp2Set_Hot;	  //����2����ֵ �¶�X10 ����0.5�� 35.5��=355
    INT16U m_WaterTempSet_Hot; //ˮ������ֵ �¶� ����1�� 35��=35
    INT16U m_Temp1Set_Cool;	  //����1����ֵ �¶�X10 ����0.5�� 35.5��=355
    INT16U m_Temp2Set_Cool;	  //����2����ֵ �¶�X10 ����0.5�� 35.5��=355
    INT16U m_WaterTempSet_Cool; //ˮ������ֵ �¶� ����1�� 35��=35
    INT16U m_AlmVolum;
} SYSCONFIGDATA,*PSYSCONFIGDATA;

typedef struct SysCalcData
{
    /////////////////Ӳ��У׼ֵ��������E2PROM��ȡ/////////////////////
    INT16U m_CH1ADArr[ADCALCDATANUM];
    INT16U m_CH1TEMPArr[ADCALCDATANUM];
    INT16U m_CH2ADArr[ADCALCDATANUM];
    INT16U m_CH2TEMPArr[ADCALCDATANUM];
    INT16U m_CH3ADArr[ADCALCDATANUM];
    INT16U m_CH3TEMPArr[ADCALCDATANUM];
    eStatus m_SingleMode; //TRUE-������̺ģʽ
} SYSCALCDATA,*PSYSCALCDATA;

typedef struct SysAdjData
{
    /////////////////���У׼ֵ��������E2PROM��ȡ/////////////////////
    INT8S m_Cal1Set;	//����1У׼ֵ
    INT8S m_Cal2Set;	//����2У׼ֵ
} SYSADJDATA,*PSYSADJDATA;

typedef struct MsgItem  //��Ϣ����Ԫ��
{
//    PVOID pArg;
    INT8U MsgId;
    INT16U lParam;
    INT16U wParam;
    void* pBuf;
} MSGITEM,*PMSGITEM;


typedef struct ModuleBase //����ӿ� //�ķ��ؽӿ�
{
    //����ģ����
    char m_ModName[16];
    //��ʼ�� ����m_pBaseData
    BOOLEAN (*pModeleInit)(void* pArg);
    //��λ ����m_pBaseData
    BOOLEAN (*pModeleReset)(void* pArg);
    //��ʼ ����m_pBaseData
    BOOLEAN (*pModeleStart)(void* pArg);
    //ֹͣ ����m_pBaseData
    BOOLEAN (*pModeleStop)(void* pArg);
    //�ͷ� ����m_pBaseData
    BOOLEAN (*pModeleRelease)(void* pArg);
    //��Ϣ���� ������
    void (*pMsgNotify)(PVOID pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);
    //1ms��������
    void (*pModele1msProcess)(void* pArg);
    //10ms��������
    void (*pModele10msProcess)(void* pArg);
    //50ms��������
    void (*pModele50msProcess)(void* pArg);
    //1s��������
    void (*pModele1sProcess)(void* pArg);
    //UART��������
    void (*pModeleUartProcess)(void* pArg);
    //ģ������ָ��
    PVOID m_pBaseData;
} MODULEBASE,*PMODULEBASE;

//*********************************************************************************************************
//*****************************************    ȫ������     *******************************************
//*********************************************************************************************************
typedef struct GlobalData
{
    PMODULEBASE pServer;
    //P_MSGQUEUE g_pMsgQueue;
} GLOBALDATA,*PGLOBALDATA;
//*********************************************************************************************************

typedef struct ModuleServerData //�����������ݽṹ
{
    PSYSPARAMDATA m_pSysData; //ϵͳ����
    PSYSCONFIGDATA m_pCfgData; //ϵͳ����
    PSYSCALCDATA m_pCalData; //ϵͳ����
    PSYSADJDATA	m_pAdjData;
    P_MSGQUEUE m_pMsgQueue;  //��Ϣ����
    DLLIST* m_pSubMouleList; //��ģ������
    BOOLEAN m_PressSta; //�������״̬��¼
} MODULESERVERDATA,*PMODULESERVERDATA;

typedef enum
{
    MacStart=1,
    SendStep1,
    ChkStep1,
    SendStep2,
    ChkStep2,
    SendStep3,
    ChkStep3,
    SendStep4,
    ChkStep4,
    SendStep5,
    ChkStep5,
    MacStop,
} eMachineSta;

#define USART_MSG 1
#define USART_STA 2
#define USART_NUL 0
#define _DIFFERENCE_WATER     1  //ˮ�µľ��� 
#define _DIFFERENCE_BODY     10   //����������ʵ�����µĲ���
#define TEMP_ALARM  2800   //��������
#define TEMP_ALARMHIGH 4300
#define ADDR_AD1CalcK    10//ad1��kֵ ��ַ
#define ADDR_AD1CalcB    20//ad1��bֵ��ַ
#define ADDR_AD2CalcK    30 //ad2 ��kֵ��ַ
#define ADDR_AD2CalcB    40  //ad2��bֵ��ַ
#define ADDR_Temp1Set    50	 //��������1�ĵ�ַ
#define ADDR_Temp2Set    60	//��������2�ĵ�ַ
#define ADDR_WaterTempSet  70 //ˮ�����õĵ�ַ
#endif
