//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* ÎÄ ¼ş Ãû : ModuleXxx.h
//*
//* ÎÄ¼şÃèÊö : Ö÷·şÎñÈÎÎñÎÄ¼ş
//*
//* ×÷    Õß : LGL
//* °æ    ±¾ : 
//* ±à Òë Æ÷ : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MODULE_XXX_H__
#define  __MODULE_XXX_H__

#include "common.h"
#include "struct_def.h"

typedef struct ModuleXxxData //ÅäÖÃÀàÊı¾İ½á¹¹
{ 
   P_MSGQUEUE m_pMsgQueue;  //ÏûÏ¢¶ÓÁĞ 
   INT16U m_Count; //¼ÆÊ±Æ÷
   BOOLEAN m_PressSta; //´¦Àíµ÷ÓÃ×´Ì¬¼ÇÂ¼
 //************************ÒÔÏÂÔö¼ÓÄ£¿éÄÚ²¿Ê¹ÓÃµÄ±äÁ¿»òÕßÆäËüÔªËØ******************************//  
   
}MODULEXXXDATA,*PMODULEXXXDATA;

typedef struct ModuleXxx //·şÎñÆ÷Àà
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
}MODULEXXX,*PMODULEXXX;
//*
//********************************************************************************************************
//* º¯ Êı Ãû : void CreateModuleXxx(void)
//**------------------------------------------------------------------------------------------------------
//* Ãè    Êö : ´´½¨Ä£¿é
//**------------------------------------------------------------------------------------------------------
//* ÊäÈë²ÎÊı : PMODULEBASE. ¿ÕÖ¸Õë
//**------------------------------------------------------------------------------------------------------
//* Êä³ö²ÎÊı : PMODULEBASE. ÉêÇëÄÚ´æ¿Õ¼äºó·µ»Ø»ùÀàÖ¸Õë
//**------------------------------------------------------------------------------------------------------
//* ·µ   »Ø  : PMODULEXXXDATA.ÉêÇëÄÚ´æ¿Õ¼äºó·µ»Ø»ùÀàÊı¾İÖ¸Õë
//********************************************************************************************************
//*
extern PMODULEBASE CreateModuleXxx(PMODULESERVERDATA pServerData);

//************************ÄÚ²¿´¦Àíº¯ÊıÊµÏÖ******************************//
static BOOLEAN ModuleXxxInit(void* pArg);
static BOOLEAN ModuleXxxReset(void* pArg);
static BOOLEAN ModuleXxxStart(void* pArg);
static BOOLEAN ModuleXxxStop(void* pArg);
static BOOLEAN ModuleXxxRelease(void* pArg);
static void ModuleXxx1sProcess(void* pArg);
static void XxxMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);

//************************Ä£¿é¹¦ÄÜÊµÏÖº¯Êı******************************//

//************************ÄÚ²¿´¦Àíº¯ÊıÊµÏÖ******************************//
#endif
