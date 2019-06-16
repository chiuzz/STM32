//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* ÎÄ ¼þ Ãû : ModuleCoolerCtrl.h
//*
//* ÎÄ¼þÃèÊö : Ö÷·þÎñÈÎÎñÎÄ¼þ
//*
//* ×÷    Õß : LGL
//* °æ    ±¾ :
//* ±à Òë Æ÷ : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MODULE_COOLERCTRL_H__
#define  __MODULE_COOLERCTRL_H__

#include "common.h"
#include "struct_def.h"

typedef enum
{
    COOLER_OFF = 0,
    COOLER_ON,
	  COOLER_START_HOLD,
    COOLER_START,
		COOLER_STOP_HOLD,
    COOLER_STOP,
		COOLER_CON_START
}	eCoolerSMachine;

#define MODE_CHANGE_MIN 0.5
#define MODE_CHANGE_ECHO_SEC 20
#define MODE_CHANGE_TIME (MODE_CHANGE_MIN*60*MODE_CHANGE_ECHO_SEC)
typedef struct ModuleCoolerCtrlData //ÅäÖÃÀàÊý¾Ý½á¹¹
{
    P_MSGQUEUE m_pMsgQueue;  //ÏûÏ¢¶ÓÁÐ
    INT16U m_Count; //¼ÆÊ±Æ÷
    BOOLEAN m_PressSta; //´¦Àíµ÷ÓÃ×´Ì¬¼ÇÂ¼
//************************ÒÔÏÂÔö¼ÓÄ£¿éÄÚ²¿Ê¹ÓÃµÄ±äÁ¿»òÕßÆäËüÔªËØ******************************//
    PSYSPARAMDATA m_pSysData; //È«¾Ö±äÁ¿
		PSYSCONFIGDATA m_pCfgData; //È«¾Ö±äÁ¿
		PSYSCALCDATA m_pCalData; //È«¾Ö±äÁ¿
		PSYSADJDATA m_pAdjData;
    eCoolerSMachine m_CoolerSMachine;
    INT16U m_CoolCount;
} MODULECOOLERCTRLDATA,*PMODULECOOLERCTRLDATA;

typedef struct ModuleCoolerCtrl //·þÎñÆ÷Àà
{
    char m_ModName[16];
    BOOLEAN (*pModeleInit)(void* pArg); //³õÊ¼»¯ ÊäÈëm_pBaseData
    BOOLEAN (*pModeleReset)(void* pArg); //¸´Î» ÊäÈëm_pBaseData
    BOOLEAN (*pModeleStart)(void* pArg); //¿ªÊ¼ ÊäÈëm_pBaseData
    BOOLEAN (*pModeleStop)(void* pArg); //Í£Ö¹ ÊäÈëm_pBaseData
    BOOLEAN (*pModeleRelease)(void* pArg); //ÊÍ·Å ÊäÈëm_pBaseData
    void (*pMsgNotify)(PVOID pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf); //ÏûÏ¢´¦Àí Ö÷ÈÎÎñ
    void (*pModele1msProcess)(void* pArg); //10msµ÷¶ÈÈÎÎ
    void (*pModele10msProcess)(void* pArg); //10msµ÷¶ÈÈÎÎñ
    void (*pModele50msProcess)(void* pArg); //50msµ÷¶ÈÈÎÎñ
    void (*pModele1sProcess)(void* pArg);  //1sµ÷¶ÈÈÎÎñ
    void (*pModeleUartProcess)(void* pArg);  //1sµ÷¶ÈÈÎÎñ
    PVOID m_pBaseData;
} MODULECOOLERCTRL,*PMODULECOOLERCTRL;
//*
//********************************************************************************************************
//* º¯ Êý Ãû : void CreateModuleCoolerCtrl(void)
//**------------------------------------------------------------------------------------------------------
//* Ãè    Êö : ´´½¨Ä£¿é
//**------------------------------------------------------------------------------------------------------
//* ÊäÈë²ÎÊý : PMODULEBASE. ¿ÕÖ¸Õë
//**------------------------------------------------------------------------------------------------------
//* Êä³ö²ÎÊý : PMODULEBASE. ÉêÇëÄÚ´æ¿Õ¼äºó·µ»Ø»ùÀàÖ¸Õë
//**------------------------------------------------------------------------------------------------------
//* ·µ   »Ø  : PMODULECOOLERCTRLDATA.ÉêÇëÄÚ´æ¿Õ¼äºó·µ»Ø»ùÀàÊý¾ÝÖ¸Õë
//********************************************************************************************************
//*
extern PMODULEBASE CreateModuleCoolerCtrl(PMODULESERVERDATA pServerData);

//************************ÄÚ²¿´¦Àíº¯ÊýÊµÏÖ******************************//
static BOOLEAN ModuleCoolerCtrlInit(void* pArg);
static BOOLEAN ModuleCoolerCtrlReset(void* pArg);
static BOOLEAN ModuleCoolerCtrlStart(void* pArg);
static BOOLEAN ModuleCoolerCtrlStop(void* pArg);
static BOOLEAN ModuleCoolerCtrlRelease(void* pArg);
static void ModuleCoolerCtrl1sProcess(void* pArg);
static void ModuleCoolerCtrl50msProcess(void* pArg);
static void CoolerCtrlMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);

//************************Ä£¿é¹¦ÄÜÊµÏÖº¯Êý******************************//
static void SetCoolerWORK(void* pArg, eStatus sta);
static void CoolerWorkMachineProc(void* pArg);
static INT16U CalcCoolerTempDip(INT16U Temp, INT16U dsp);
//************************ÄÚ²¿´¦Àíº¯ÊýÊµÏÖ******************************//
#endif
