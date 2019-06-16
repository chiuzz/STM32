//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* �� �� �� : ModuleDect.h
//*
//* �ļ����� : �����������ļ�
//*
//* ��    �� : LGL
//* ��    �� : 
//* �� �� �� : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MODULE_DECT_H__
#define  __MODULE_DECT_H__

#include "common.h"
#include "struct_def.h"

#define MAXDATANUM 10
typedef struct ModuleDectData //���������ݽṹ
{ 
   P_MSGQUEUE m_pMsgQueue;  //��Ϣ���� 
	 PCONFIGDATA m_pSysData;     //ϵͳ����
   INT16U m_Count; //��ʱ��
   BOOLEAN m_PressSta; //�������״̬��¼
 //************************��������ģ���ڲ�ʹ�õı�����������Ԫ��******************************//  
	 INT16U m_LedStatus;
	 INT16U m_ChDataArr[MAXCHLNUM][MAXDATANUM];	
	 INT16U m_TempArr[MAXCHLNUM];
	 INT16U *m_pAdArr;
	
	 INT16U m_PkgIndex;
	
	 FP32 m_MultiK[MAXCHLNUM][TEMPCALDATANUM-1];
	 FP32 m_MultiB[MAXCHLNUM][TEMPCALDATANUM-1];
	 INT16U m_KBNum;
	 FP32 BinomialA[MAXCHLNUM];
	 FP32 BinomialB[MAXCHLNUM];
	 FP32 BinomialC[MAXCHLNUM];
   
}MODULEDECTDATA,*PMODULEDECTDATA;

typedef struct ModuleDect //��������
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
}MODULEDECT,*PMODULEDECT;
//*
//********************************************************************************************************
//* �� �� �� : void CreateModuleDect(void)
//**------------------------------------------------------------------------------------------------------
//* ��    �� : ����ģ��
//**------------------------------------------------------------------------------------------------------
//* ������� : PMODULEBASE. ��ָ��
//**------------------------------------------------------------------------------------------------------
//* ������� : PMODULEBASE. �����ڴ�ռ�󷵻ػ���ָ��
//**------------------------------------------------------------------------------------------------------
//* ��   ��  : PMODULEDECTDATA.�����ڴ�ռ�󷵻ػ�������ָ��
//********************************************************************************************************
//*
extern PMODULEBASE CreateModuleDect(PMODULESERVERDATA pServerData);

//************************�ڲ�������ʵ��******************************//
static BOOLEAN ModuleDectInit(void* pArg);
static BOOLEAN ModuleDectReset(void* pArg);
static BOOLEAN ModuleDectStart(void* pArg);
static BOOLEAN ModuleDectStop(void* pArg);
static BOOLEAN ModuleDectRelease(void* pArg);
static void ModuleDect1sProcess(void* pArg);
static void DectMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);

//************************ģ�鹦��ʵ�ֺ���******************************//

//************************�ڲ�������ʵ��******************************//
static INT16U GetTempAdData(PMODULEDECTDATA pData, INT16U ch, INT16U ad);
static INT8U SendPKGCheckSum(INT8U* pData, INT8U num);
static INT16U CalcTempData(PMODULEDECTDATA pData, INT16U ch);

static INT16U CalcTempDataMulti(PMODULEDECTDATA pData, INT16U ch);
static INT16U CalcTempDataSingle(PMODULEDECTDATA pData, INT16U ch);
static INT16U CalcTempDataBinomial(PMODULEDECTDATA pData, INT16U ch);
static void ModeleDectPrintInfo(PMODULEDECTDATA pData);//��ӡ����
static void GetParamMulti(PMODULEDECTDATA pData);//����У׼����
static void GetParamBinomial(PMODULEDECTDATA pData);//����У׼����
static INT16U CalcTempDataMulti(PMODULEDECTDATA pData, INT16U ch);//�����¶�
static void CalcBinomial(INT16U *pArrAd, INT16U *pArrTemp, FP32 *pa, FP32 *pb, FP32 *pc );
static void ModeleDectSendPkg(PMODULEDECTDATA pData);
#endif
