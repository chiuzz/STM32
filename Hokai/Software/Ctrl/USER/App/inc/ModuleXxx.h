//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* �� �� �� : ModuleXxx.h
//*
//* �ļ����� : �����������ļ�
//*
//* ��    �� : LGL
//* ��    �� : 
//* �� �� �� : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MODULE_XXX_H__
#define  __MODULE_XXX_H__

#include "common.h"
#include "struct_def.h"

typedef struct ModuleXxxData //���������ݽṹ
{ 
   P_MSGQUEUE m_pMsgQueue;  //��Ϣ���� 
   INT16U m_Count; //��ʱ��
   BOOLEAN m_PressSta; //�������״̬��¼
 //************************��������ģ���ڲ�ʹ�õı�����������Ԫ��******************************//  
   
}MODULEXXXDATA,*PMODULEXXXDATA;

typedef struct ModuleXxx //��������
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
}MODULEXXX,*PMODULEXXX;
//*
//********************************************************************************************************
//* �� �� �� : void CreateModuleXxx(void)
//**------------------------------------------------------------------------------------------------------
//* ��    �� : ����ģ��
//**------------------------------------------------------------------------------------------------------
//* ������� : PMODULEBASE. ��ָ��
//**------------------------------------------------------------------------------------------------------
//* ������� : PMODULEBASE. �����ڴ�ռ�󷵻ػ���ָ��
//**------------------------------------------------------------------------------------------------------
//* ��   ��  : PMODULEXXXDATA.�����ڴ�ռ�󷵻ػ�������ָ��
//********************************************************************************************************
//*
extern PMODULEBASE CreateModuleXxx(PMODULESERVERDATA pServerData);

//************************�ڲ�������ʵ��******************************//
static BOOLEAN ModuleXxxInit(void* pArg);
static BOOLEAN ModuleXxxReset(void* pArg);
static BOOLEAN ModuleXxxStart(void* pArg);
static BOOLEAN ModuleXxxStop(void* pArg);
static BOOLEAN ModuleXxxRelease(void* pArg);
static void ModuleXxx1sProcess(void* pArg);
static void XxxMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);

//************************ģ�鹦��ʵ�ֺ���******************************//

//************************�ڲ�������ʵ��******************************//
#endif
