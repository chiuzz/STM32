//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* ÎÄ ¼þ Ãû : ModuleGpioProc.h
//*
//* ÎÄ¼þÃèÊö : Ö÷·þÎñÈÎÎñÎÄ¼þ
//*
//* ×÷    Õß : LGL
//* °æ    ±¾ :
//* ±à Òë Æ÷ : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MODULE_GPIOPROC_H__
#define  __MODULE_GPIOPROC_H__

#include "common.h"
#include "struct_def.h"



typedef enum
{
    BUMP_WORK_OFF = 0,
    BUMP_WORK_ON,
    BUMP_WORK_STOP,
    BUMP_WORK_START,
}	eBumpWorkMachine;

typedef struct ModuleGpioProcData //ÅäÖÃÀàÊý¾Ý½á¹¹
{
    P_MSGQUEUE m_pMsgQueue;  //ÏûÏ¢¶ÓÁÐ
    INT16U m_Count; //¼ÆÊ±Æ÷
    BOOLEAN m_PressSta; //´¦Àíµ÷ÓÃ×´Ì¬¼ÇÂ¼
    //************************ÒÔÏÂÔö¼ÓÄ£¿éÄÚ²¿Ê¹ÓÃµÄ±äÁ¿»òÕßÆäËüÔªËØ******************************//
    PSYSPARAMDATA m_pSysData; //È«¾Ö±äÁ¿
    PSYSCONFIGDATA m_pCfgData; //È«¾Ö±äÁ¿
		PSYSCALCDATA m_pCalData; //È«¾Ö±äÁ¿
		PSYSADJDATA m_pAdjData;
    INT16U m_Count50ms;
    eBumpWorkMachine m_Bump1WorkMac;
    eBumpWorkMachine m_Bump2WorkMac;

} MODULEGPIOPROCDATA, *PMODULEGPIOPROCDATA;

typedef struct ModuleGpioProc //·þÎñÆ÷Àà
{
    char m_ModName[16];
    BOOLEAN (*pModeleInit)(void* pArg); //³õÊ¼»¯ ÊäÈëm_pBaseData
    BOOLEAN (*pModeleReset)(void* pArg); //¸´Î» ÊäÈëm_pBaseData
    BOOLEAN (*pModeleStart)(void* pArg); //¿ªÊ¼ ÊäÈëm_pBaseData
    BOOLEAN (*pModeleStop)(void* pArg); //Í£Ö¹ ÊäÈëm_pBaseData
    BOOLEAN (*pModeleRelease)(void* pArg); //ÊÍ·Å ÊäÈëm_pBaseData
    void (*pMsgNotify)(PVOID pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf); //ÏûÏ¢´¦Àí Ö÷ÈÎÎñ
    void (*pModele1msProcess)(void* pArg); //1msµ÷¶ÈÈÎÎ
    void (*pModele10msProcess)(void* pArg); //10msµ÷¶ÈÈÎÎñ
    void (*pModele50msProcess)(void* pArg); //50msµ÷¶ÈÈÎÎñ
    void (*pModele1sProcess)(void* pArg);  //1sµ÷¶ÈÈÎÎñ
    void (*pModeleUartProcess)(void* pArg);  //1sµ÷¶ÈÈÎÎñ
    PVOID m_pBaseData;
} MODULEGPIOPROC, *PMODULEGPIOPROC;
//*
//********************************************************************************************************
//* º¯ Êý Ãû : void CreateModuleGpioProc(void)
//**------------------------------------------------------------------------------------------------------
//* Ãè    Êö : ´´½¨Ä£¿é
//**------------------------------------------------------------------------------------------------------
//* ÊäÈë²ÎÊý : PMODULEBASE. ¿ÕÖ¸Õë
//**------------------------------------------------------------------------------------------------------
//* Êä³ö²ÎÊý : PMODULEBASE. ÉêÇëÄÚ´æ¿Õ¼äºó·µ»Ø»ùÀàÖ¸Õë
//**------------------------------------------------------------------------------------------------------
//* ·µ   »Ø  : PMODULEGPIOPROCDATA.ÉêÇëÄÚ´æ¿Õ¼äºó·µ»Ø»ùÀàÊý¾ÝÖ¸Õë
//********************************************************************************************************
//*
extern PMODULEBASE CreateModuleGpioProc(PMODULESERVERDATA pServerData);

//************************ÄÚ²¿´¦Àíº¯ÊýÊµÏÖ******************************//
static BOOLEAN ModuleGpioProcInit(void* pArg);
static BOOLEAN ModuleGpioProcReset(void* pArg);
static BOOLEAN ModuleGpioProcStart(void* pArg);
static BOOLEAN ModuleGpioProcStop(void* pArg);
static BOOLEAN ModuleGpioProcRelease(void* pArg);
static void ModuleGpioProc10msProcess(void* pArg);
static void ModuleGpioProc1sProcess(void* pArg);
static void ModuleGpioProc50msProcess(void* pArg);
static void GpioProcMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);

//************************Ä£¿é¹¦ÄÜÊµÏÖº¯Êý******************************//
//»ñÈ¡ÏµÍ³×´Ì¬
void GetModuleGpioStatus(PMODULEGPIOPROCDATA pData);

//************************ÄÚ²¿´¦Àíº¯ÊýÊµÏÖ******************************//
static void Bump1WorkMachineProc(void* pArg);
static void Bump2WorkMachineProc(void* pArg);
#endif

