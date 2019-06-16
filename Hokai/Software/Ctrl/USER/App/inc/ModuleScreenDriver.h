//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* �� �� �� : ModuleScreenDriver.h
//*
//* �ļ����� : �����������ļ�
//*
//* ��    �� : LGL
//* ��    �� : 
//* �� �� �� : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MODULE_SCREENDRIVER_H__
#define  __MODULE_SCREENDRIVER_H__

#include "common.h"
#include "struct_def.h"

#define SCREOM 0xFF	
#define SCRSOM 0xEF 
//#define DSOM 0 //��ͷ
//#define CMD 1 //����
//#define D1 2 	 //ͨ��0���ֽ�
//#define D2 3	 //ͨ��0���ֽ�
//#define D3 4	 //ͨ��1���ֽ�
//#define D4 5	 //ͨ��1���ֽ�
//#define D5 6   //ͨ��2���ֽ�
//#define DCC 7  //У��
//#define DEOM 8 //��β
#define SCRBUFMAX 8 //���ݰ����� 
#define SCRDATABUF (SCRBUFMAX*2)

typedef struct UartSrcData 
{ 
   INT16U m_DataBuf[SCRDATABUF];
   INT16U m_index;
   INT16U m_MarkIndex;
   BOOLEAN m_MarkSta;
   INT16U m_buf[SCRBUFMAX];
   INT8U m_buflen;
   BOOLEAN m_Sta;
}UARTSRCDATA,*PUARTSRCDATA;	

typedef struct ModuleScreenDriverData //���������ݽṹ
{ 
   P_MSGQUEUE m_pMsgQueue;  //��Ϣ���� 
   INT16U m_Count; //��ʱ��
   BOOLEAN m_PressSta; //�������״̬��¼
 //************************��������ģ���ڲ�ʹ�õı�����������Ԫ��******************************//  
   PUARTSRCDATA m_pData;
	 PSYSPARAMDATA m_pSysData; //ȫ�ֱ���
	 PSYSCONFIGDATA m_pCfgData; //ȫ�ֱ���
		PSYSCALCDATA m_pCalData; //ȫ�ֱ���
		PSYSADJDATA m_pAdjData;
}MODULESCREENDRIVERDATA,*PMODULESCREENDRIVERDATA;

typedef struct ModuleScreenDriver //��������
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
}MODULESCREENDRIVER,*PMODULESCREENDRIVER;
//*
//********************************************************************************************************
//* �� �� �� : void CreateModuleScreenDriver(void)
//**------------------------------------------------------------------------------------------------------
//* ��    �� : ����ģ��
//**------------------------------------------------------------------------------------------------------
//* ������� : PMODULEBASE. ��ָ��
//**------------------------------------------------------------------------------------------------------
//* ������� : PMODULEBASE. �����ڴ�ռ�󷵻ػ���ָ��
//**------------------------------------------------------------------------------------------------------
//* ��   ��  : PMODULESCREENDRIVERDATA.�����ڴ�ռ�󷵻ػ�������ָ��
//********************************************************************************************************
//*
extern PMODULEBASE CreateModuleScreenDriver(PMODULESERVERDATA pServerData);
extern void SendSrcUartData(uint16_t data); //���������ã�������ѹ�����ݼ��������ְ�
//************************�ڲ�������ʵ��******************************//
static BOOLEAN ModuleScreenDriverInit(void* pArg);
static BOOLEAN ModuleScreenDriverReset(void* pArg);
static BOOLEAN ModuleScreenDriverStart(void* pArg);
static BOOLEAN ModuleScreenDriverStop(void* pArg);
static BOOLEAN ModuleScreenDriverRelease(void* pArg);
static void ModuleScreenDriver50msProcess(void* pArg);
static void ScreenDriverMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);
static void ModeleScreenDriverUartProcess(void* pArg);
//************************ģ�鹦��ʵ�ֺ���******************************//

//************************�ڲ�������ʵ��******************************//
static BOOLEAN SrcCheckSum(INT16U* buf, INT8U len); //У���ִ�к���
static void SrcUnpack(void* pArg, INT16U *pData, INT8U len); //�������ݰ���ִ��Э�����
void UsartSendFullData_Screen(void* pArg);//���ʹ�����Ϣ����Ļ
#endif
