//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* �� �� �� : ModuleCalc.h
//*
//* �ļ����� : �����������ļ�
//*
//* ��    �� : LGL
//* ��    �� : 
//* �� �� �� : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MODULE_CALC_H__
#define  __MODULE_CALC_H__

#include "common.h"
#include "struct_def.h"
#include "EEPROM.h"

#define EOM 0xFF	//��β
#define SOM 0xEF //��ͷ
//#define DSOM 0 //��ͷ
//#define CMD 1 //����
//#define D1 2 	 //ͨ��0���ֽ�
//#define D2 3	 //ͨ��0���ֽ�
//#define D3 4	 //ͨ��1���ֽ�
//#define D4 5	 //ͨ��1���ֽ�
//#define D5 6   //ͨ��2���ֽ�
//#define DCC 7  //У��
//#define DEOM 8 //��β
#define CALCBUFMAX 8 //���ݰ����� 
#define CALCDATABUF (CALCBUFMAX*2)
typedef struct UartCalcData 
{ 
   INT16U m_DataBuf[CALCDATABUF];
   INT16U m_index;
   INT16U m_MarkIndex;
   BOOLEAN m_MarkSta;
   INT16U m_buf[CALCBUFMAX];
   INT8U m_buflen;
   BOOLEAN m_Sta;
}UARTCALCDATA,*PUARTCALCDATA;	

#define  ADC_Convert_tims_Calc   20     //�ۼ�ת������


typedef struct ModuleCalcData //���������ݽṹ
{ 
   P_MSGQUEUE m_pMsgQueue;  //��Ϣ���� 
   INT16U m_Count; //��ʱ��
   BOOLEAN m_PressSta; //�������״̬��¼
	INT32U Temp1AD_Calc;
	INT32U Temp2AD_Calc;
	INT32U Temp3AD_Calc;
	INT16U ConverTimes_Calc; 
	INT32U AD1Value_Calc;
	INT32U AD2Value_Calc;
	INT32U AD3Value_Calc;
	INT32U UsartSendFlag;
	INT16U m_AD_RFlag;       //����״̬���
	INT16U m_CheckCH;    //У׼ͨ��
	INT16U m_CheckMod;    //У׼ģʽ
 //************************��������ģ���ڲ�ʹ�õı�����������Ԫ��******************************//  
   PSYSPARAMDATA m_pSysData; //ȫ�ֱ���
	 PSYSCONFIGDATA m_pCfgData; //ȫ�ֱ���
		PSYSCALCDATA m_pCalData; //ȫ�ֱ���
		PSYSADJDATA m_pAdjData;
	 PUARTCALCDATA m_pData;
	 
}MODULECALCDATA,*PMODULECALCDATA;

typedef struct ModuleCalc //��������
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
}MODULECALC,*PMODULECALC;
//*
//********************************************************************************************************
//* �� �� �� : void CreateModuleCalc(void)
//**------------------------------------------------------------------------------------------------------
//* ��    �� : ����ģ��
//**------------------------------------------------------------------------------------------------------
//* ������� : PMODULEBASE. ��ָ��
//**------------------------------------------------------------------------------------------------------
//* ������� : PMODULEBASE. �����ڴ�ռ�󷵻ػ���ָ��
//**------------------------------------------------------------------------------------------------------
//* ��   ��  : PMODULECALCDATA.�����ڴ�ռ�󷵻ػ�������ָ��
//********************************************************************************************************
//*
extern PMODULEBASE CreateModuleCalc(PMODULESERVERDATA pServerData);

//************************�ڲ�������ʵ��******************************//
static BOOLEAN ModuleCalcInit(void* pArg);
static BOOLEAN ModuleCalcReset(void* pArg);
static BOOLEAN ModuleCalcStart(void* pArg);
static BOOLEAN ModuleCalcStop(void* pArg);
static BOOLEAN ModuleCalcRelease(void* pArg);
static void ModuleCalc1sProcess(void* pArg);
static void ModuleCalc10msProcess(void* pArg);
static void ModeleCalcUartProcess(void* pArg);
static void CalcMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);

//************************ģ�鹦��ʵ�ֺ���******************************//
extern void SendUartData(uint16_t data); //���������ã�������ѹ�����ݼ��������ְ�
//************************�ڲ�������ʵ��******************************//
static void Unpack(void* pArg, INT16U *pData, INT8U len); //�������ݰ���ִ��Э�����
static BOOLEAN CheckSum(INT16U* buf, INT8U len); //У���ִ�к���
static void GetUartData(void* pArg); //������ģ������������
void SensorCheck(void* pArg); //������У׼
void  HardwareCheck(void* pArg);  //Ӳ��У׼

#endif
