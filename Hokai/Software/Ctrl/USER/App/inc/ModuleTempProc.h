//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* �� �� �� : ModuleTempProc.h
//*
//* �ļ����� : �����������ļ�
//*
//* ��    �� : LGL
//* ��    �� : 
//* �� �� �� : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MODULE_TEMPPROC_H__
#define  __MODULE_TEMPPROC_H__

#include "common.h"
#include "struct_def.h"
#define  ADC_Interval       5     //5ms
#define  ADC_Convert_tims   1000     //�ۼ�ת������
//#define  Vref   3299     //�ο���ѹ
//#define  Offset   15     //ƫ����
#define BUFMAX 20
#define DATABUF (BUFMAX*2)

typedef struct UartData 
{ 
   INT16U m_DataBuf[DATABUF];
   INT16U m_index;
   INT16U m_MarkIndex;
   BOOLEAN m_MarkSta;
   INT16U m_buf[BUFMAX];
   INT8U m_buflen;
   BOOLEAN m_Sta;
}UARTDATA,*PUARTDATA;


typedef struct ModuleTempProcData //���������ݽṹ
{ 
	P_MSGQUEUE m_pMsgQueue;  //��Ϣ���� 
	INT16U T_Count; //��ʱ��
	BOOLEAN m_PressSta; //�������״̬��¼
	INT32U Temp1AD;
	INT32U Temp2AD;
	INT32U Temp3AD;
	INT16U ConverTimes; 
	INT32U AD1Value;
	INT32U AD2Value;
	INT32U AD3Value;
	//************************��������ģ���ڲ�ʹ�õı�����������Ԫ��******************************//  
	PSYSPARAMDATA m_pSysData; //ȫ�ֱ���
	PSYSCONFIGDATA m_pCfgData; //ȫ�ֱ���
	PSYSCALCDATA m_pCalData; //ȫ�ֱ���
	PSYSADJDATA m_pAdjData;
	PUARTDATA m_pData;
   
}MODULETEMPPROCDATA,*PMODULETEMPPROCDATA;

typedef struct ModuleTempProc //��������
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
	  void (*pStart)(void* pArg);
}MODULETEMPPROC,*PMODULETEMPPROC;
//*
//********************************************************************************************************
//* �� �� �� : void CreateModuleTempProc(void)
//**------------------------------------------------------------------------------------------------------
//* ��    �� : ����ģ��
//**------------------------------------------------------------------------------------------------------
//* ������� : PMODULEBASE. ��ָ��
//**------------------------------------------------------------------------------------------------------
//* ������� : PMODULEBASE. �����ڴ�ռ�󷵻ػ���ָ��
//**------------------------------------------------------------------------------------------------------
//* ��   ��  : PMODULETEMPPROCDATA.�����ڴ�ռ�󷵻ػ�������ָ��
//********************************************************************************************************
//*
extern PMODULEBASE CreateModuleTempProc(PMODULESERVERDATA pServerData);

//************************�ڲ�������ʵ��******************************//
static BOOLEAN ModuleTempProcInit(void* pArg);
static BOOLEAN ModuleTempProcReset(void* pArg);
static BOOLEAN ModuleTempProcStart(void* pArg);
static BOOLEAN ModuleTempProcStop(void* pArg);
static BOOLEAN ModuleTempProcRelease(void* pArg);
static void ModuleTempProc1msProcess(void* pArg);
static void TempProcMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);

//************************ģ�鹦��ʵ�ֺ���******************************//
void GetTemp1(PMODULETEMPPROCDATA pData);//����1
void GetTemp2(PMODULETEMPPROCDATA pData);//����2
void GetWaterTemp(PMODULETEMPPROCDATA pData);//ˮ��
void Calc_K_B_Value(PMODULETEMPPROCDATA pData);//����k_b��ֵ
//����Kֵ
FP32 calculateSlope(INT16U x_V[2], INT16U y_V[2]);
//���㳣��b
FP32 calculateConstant(INT16U x_V[2], INT16U y_V[2]);


extern void SendUartData(uint16_t data);
static BOOLEAN CheckSum(INT16U* buf, INT8U len);
static void GetUartData(void* pArg);
static void Start(void* pArg);
static void Unpack(void* pArg, INT16U *pData, INT8U len);

//************************�ڲ�������ʵ��******************************//
#endif
