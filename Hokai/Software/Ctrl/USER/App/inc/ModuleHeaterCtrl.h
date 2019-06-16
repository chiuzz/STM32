//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* ÎÄ ¼ş Ãû : ModuleHeaterCtrl.h
//*
//* ÎÄ¼şÃèÊö : Ö÷·şÎñÈÎÎñÎÄ¼ş
//*
//* ×÷    Õß : LGL
//* °æ    ±¾ :
//* ±à Òë Æ÷ : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MODULE_HEATERCTRL_H__
#define  __MODULE_HEATERCTRL_H__

#include "common.h"
#include "struct_def.h"

typedef enum
{
    HEATER_STOP = 0,
    HEATER_STEP_START,
    HEATER_STEP_WORK,
    HEATER_STEP_WORK_ON,
    HEATER_STEP_WORK_UP,
    HEATER_STEP_WORK_DOWN,
    HEATER_STEP_WORK_COM_UP,
}	eHeaterSMachine;


typedef enum
{
    ALM_STOP = 0,
    ALM_START,
    ALM_MONITOR,
} eHeaterAlmMachine;

#define HEATERALMNUM 2
typedef struct ModuleHeaterCtrlData //ÅäÖÃÀàÊı¾İ½á¹¹
{
    P_MSGQUEUE m_pMsgQueue;  //ÏûÏ¢¶ÓÁĞ
    INT16U m_Count; //¼ÆÊ±Æ÷
    INT16U m_Count2; //¼ÆÊ±Æ÷2
    BOOLEAN m_PressSta; //´¦Àíµ÷ÓÃ×´Ì¬¼ÇÂ¼
//************************ÒÔÏÂÔö¼ÓÄ£¿éÄÚ²¿Ê¹ÓÃµÄ±äÁ¿»òÕßÆäËüÔªËØ******************************//
    PSYSPARAMDATA m_pSysData; //È«¾Ö±äÁ¿
    PSYSCONFIGDATA m_pCfgData; //È«¾Ö±äÁ¿
    PSYSCALCDATA m_pCalData; //È«¾Ö±äÁ¿
    PSYSADJDATA m_pAdjData;
    eHeaterSMachine m_HeaterSMachine;
    eHeaterAlmMachine m_HeaterAlmMac[HEATERALMNUM];
    INT16S m_ErrSum;
    INT16U m_ProcCount;
} MODULEHEATERCTRLDATA,*PMODULEHEATERCTRLDATA;

typedef struct ModuleHeaterCtrl //·şÎñÆ÷Àà
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
} MODULEHEATERCTRL,*PMODULEHEATERCTRL;
//*
//********************************************************************************************************
//* º¯ Êı Ãû : void CreateModuleHeaterCtrl(void)
//**------------------------------------------------------------------------------------------------------
//* Ãè    Êö : ´´½¨Ä£¿é
//**------------------------------------------------------------------------------------------------------
//* ÊäÈë²ÎÊı : PMODULEBASE. ¿ÕÖ¸Õë
//**------------------------------------------------------------------------------------------------------
//* Êä³ö²ÎÊı : PMODULEBASE. ÉêÇëÄÚ´æ¿Õ¼äºó·µ»Ø»ùÀàÖ¸Õë
//**------------------------------------------------------------------------------------------------------
//* ·µ   »Ø  : PMODULEHEATERCTRLDATA.ÉêÇëÄÚ´æ¿Õ¼äºó·µ»Ø»ùÀàÊı¾İÖ¸Õë
//********************************************************************************************************
//*
extern PMODULEBASE CreateModuleHeaterCtrl(PMODULESERVERDATA pServerData);

//************************ÄÚ²¿´¦Àíº¯ÊıÊµÏÖ******************************//
static BOOLEAN ModuleHeaterCtrlInit(void* pArg);
static BOOLEAN ModuleHeaterCtrlReset(void* pArg);
static BOOLEAN ModuleHeaterCtrlStart(void* pArg);
static BOOLEAN ModuleHeaterCtrlStop(void* pArg);
static BOOLEAN ModuleHeaterCtrlRelease(void* pArg);
static void ModuleHeaterCtrl1sProcess(void* pArg);
static void ModuleHeaterCtrl50msProcess(void* pArg);
static void HeaterCtrlMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);

//************************Ä£¿é¹¦ÄÜÊµÏÖº¯Êı******************************//
static void SetHeaterWORK(void* pArg, eStatus sta);
static void HeaterWorkMachineProc(void* pArg);
static void HeaterAlmMachineProc(void* pArg,INT16U index); //Ã¿1sÔËĞĞ
//************************ÄÚ²¿´¦Àíº¯ÊıÊµÏÖ******************************//
#endif
