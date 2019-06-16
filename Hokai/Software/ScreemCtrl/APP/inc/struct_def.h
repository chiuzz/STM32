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

#include "MsgQueue.h"
#include "dllist.h"
#include "os_cpu.h"
#include "common.h"
// #include "os_cpu.h"
//typedef struct Struct
//{}STRUCT,*PSTRUCT;
//typedef enum {FALSE = 0, TRUE = !FALSE} bool;
typedef void*         PVOID;

//*********************************************************************************************************

typedef struct MsgItem  //��Ϣ����Ԫ��
{
//    PVOID pArg;
    INT8U MsgId;
    INT16U lParam;
    INT16U wParam;
    void* pBuf;
} MSGITEM, *PMSGITEM;

//*********************************************************************************************************
//*****************************************    ϵͳ����     *******************************************
//*********************************************************************************************************
typedef enum
{
    CalcMode = 1,
    StartMode,
}	eWorkMode;

//*********************************************************************************************************
//*****************************************    ϵͳ״̬����     *******************************************
//*********************************************************************************************************
#define MAXCHLNUM 7
typedef struct SysStatusData
{
    INT16U m_AdcError; //����Դѹ�� ��λpa
    INT16U m_SensorOff[7];
    INT16U m_AdArr[MAXCHLNUM];
} SYSSTATUSDATA, *PSYSSTATUSDATA;
//*********************************************************************************************************


//*********************************************************************************************************
//*****************************************    ϵͳ��������     *******************************************
//*********************************************************************************************************
// typedef struct SysParamData
// {
//   INT32S m_Vt; //�ܳ�����
// }SYSPARAMDATA,*PSYSPARAMDATA;
//*********************************************************************************************************

//*********************************************************************************************************
//*****************************************    ϵͳ����     *******************************************
//*********************************************************************************************************

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
    NoAlm = BIT1,
    Temp1Alm = BIT2,
    Temp2Alm = BIT3,
    WaterTemp = BIT4,
    WaterStatus = BIT5,
    ConfigErr = BIT6,
}	eSystemAlm;

typedef enum
{
    NoFocus = 0,
    Temp1Focus,
    Temp2Focus,
    TempWFocus,
    AlmVolumFocus,
    Cal1Focus,
    Cal2Focus,
}	eFocusStatus;

typedef enum
{
    NoBeep = 0,
    BeepON,
    AlmBeep1,
    AlmBeep2,
}	eAlmType;

#define ALM_LEVEL_LOW 1
#define ALM_LEVEL_MID 2
#define ALM_LEVEL_HIG 3

typedef struct ConfigData
{
    PSYSSTATUSDATA pStatus;
    ///////////////////////ϵͳ״̬���ݣ�������ʼ������/////////////////////////
    eFocusStatus m_FocusStatus; //����״̬  0-�޽��� 1-6����
    eStatus m_SingleMode;
    eStatus m_Bump1Status; //ˮ��1״̬
    eStatus m_Bump2Status; //ˮ��2״̬
    INT16U m_Temp1;	//����1 �¶�x1000 35551=35.551��
    INT16U m_Temp2;	//����2 �¶�x1000 35551=35.551��
    INT16U m_WaterTemp; //ˮ�� �¶�x100 3555=35.55��
    eNoStatus m_WaterStatus; //ˮλI,II,III
    eStatus m_Cooler; //����״̬
    eStatus m_Heater; //����״̬
    eSystemAlm m_SystemAlm; //ϵͳ����״̬
    eSystemStatus m_SystemSta;//ϵͳ����״̬
    eStatus m_Cycle1Set;	//ˮ·1״̬
    eStatus m_Cycle2Set;	//ˮ·2״̬
    INT16U m_AlmVolSet; 	//����������ʾֵ

    ///////////////////////ϵͳ�������ݣ�������E2PROM��ȡ����/////////////////////////
    INT16U m_Temp1Set;	  //����1����ֵ �¶�X10 ����0.5�� 35.5��=355
    INT16U m_Temp2Set;	  //����2����ֵ �¶�X10 ����0.5�� 35.5��=355
    INT16U m_WaterTempSet; //ˮ������ֵ �¶� ����1�� 35��=35
    INT16U m_AlmVolum;		//������������ֵ
    INT8S m_Cal1Set;	  //����1У׼ֵ ����0.1��
    INT8S m_Cal2Set;	  //����2У׼ֵ ����0.1��

    //������Ϣ
    eStatus m_Sensor1OFF; //���������� Status_On-����
    eStatus m_Sensor2OFF; //���������� Status_On-����
    eStatus m_HeaterPOWER; //�������쳣 Status_On-����
    eStatus m_WaterHIGH; //ˮ�³�����״̬ Status_On-����
    eStatus m_WaterTLow; //ˮ�³�����״̬ Status_On-����
    eStatus m_E2PROMERR;//e2prom���� Status_On-����
    eStatus m_WaterLow;//ˮλ��״̬ Status_On-����
    eStatus m_HeaterModeWT1Low; //����ģʽ�£��趨ˮ�µ�������1 Status_On-����
    eStatus m_HeaterModeWT2Low; //����ģʽ�£��趨ˮ�µ�������2 Status_On-����
    eStatus m_HeaterModeT1ALM; //����ģʽ�£�����1���ޱ���
    eStatus m_HeaterModeT2ALM; //����ģʽ�£�����2���ޱ���
    eStatus	m_Cycle1Alm; //Һ·1����
    eStatus	m_Cycle2Alm;//Һ·2����
} CONFIGDATA, *PCONFIGDATA;
//*********************************************************************************************************


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
    //10ms��������
    void (*pModele10msProcess)(void* pArg);
    //50ms��������
    void (*pModele50msProcess)(void* pArg);
    //1s��������
    void (*pModele1sProcess)(void* pArg);
    //1ms��������
    void (*pModele1msProcess)(void* pArg);
    //ģ������ָ��
    PVOID m_pBaseData;
} MODULEBASE, *PMODULEBASE;

//*********************************************************************************************************
//*****************************************   ����ģ��     *******************************************
//*********************************************************************************************************
typedef struct ModeObjData //���������ݽṹ
{
    P_MSGQUEUE m_pMsgQueue;  //��Ϣ����
    PCONFIGDATA m_pSysData;
    eWorkMode m_Id;
    BOOLEAN m_PressSta; //�������״̬��¼
    INT16U m_Count; //��ʱ�� ��λ10ms
//    ePhaseStatus m_Phase;
    BOOLEAN m_ConfigFlag;
//************************��������ģ���ڲ�ʹ�õı�����������Ԫ��******************************//
} MODEOBJDATA, *PMODEOBJDATA;

typedef struct ModeObj //����ӿ� //�ķ��ؽӿ�
{
    BOOLEAN (*pModeInit)(PVOID Self);
    BOOLEAN (*pModeStart)(PVOID Self);
    BOOLEAN (*pModeReset)(PVOID Self);
    BOOLEAN (*pModeStop)(PVOID Self);
    BOOLEAN (*pModeRelease)(PVOID Self);
    void (*pMsgNotify)(PVOID Self, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);
    void (*pMode10msProcess)(PVOID Self);
    void (*pMode50msProcess)(PVOID Self);
    void (*pMode1sProcess)(PVOID Self);
    PVOID m_pBaseData;
    /******************��ģʽ����ʵ��*************************/
} MODEOBJ, *PMODEOBJ;

//*********************************************************************************************************
//*****************************************    ȫ������     *******************************************
//*********************************************************************************************************
typedef struct GlobalData
{
    PMODULEBASE pServer;
//    P_MSGQUEUE g_pMsgQueue;
} GLOBALDATA, *PGLOBALDATA;
//*********************************************************************************************************

typedef struct ModuleServerData //�����������ݽṹ
{
    PCONFIGDATA m_pSysData;     //ϵͳ����
    P_MSGQUEUE m_pMsgQueue;  //��Ϣ����
    DLLIST* m_pSubMouleList; //��ģ������
    BOOLEAN m_PressSta; //�������״̬��¼
} MODULESERVERDATA, *PMODULESERVERDATA;

#endif
