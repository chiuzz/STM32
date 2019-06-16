//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* ÎÄ ¼ş Ãû : ModuleScreenDriver.h
//*
//* ÎÄ¼şÃèÊö : Ö÷·şÎñÈÎÎñÎÄ¼ş
//*
//* ×÷    Õß : LGL
//* °æ    ±¾ : 
//* ±à Òë Æ÷ : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MODULE_SCREENDRIVER_H__
#define  __MODULE_SCREENDRIVER_H__

#include "common.h"
#include "struct_def.h"

#define SCREOM 0xFF	
#define SCRSOM 0xEF 
//#define DSOM 0 //°üÍ·
//#define CMD 1 //ÃüÁî
//#define D1 2 	 //Í¨µÀ0¸ß×Ö½Ú
//#define D2 3	 //Í¨µÀ0µÍ×Ö½Ú
//#define D3 4	 //Í¨µÀ1¸ß×Ö½Ú
//#define D4 5	 //Í¨µÀ1µÍ×Ö½Ú
//#define D5 6   //Í¨µÀ2¸ß×Ö½Ú
//#define DCC 7  //Ğ£Ñé
//#define DEOM 8 //°üÎ²
#define SCRBUFMAX 8 //Êı¾İ°ü³¤¶È 
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

typedef struct ModuleScreenDriverData //ÅäÖÃÀàÊı¾İ½á¹¹
{ 
   P_MSGQUEUE m_pMsgQueue;  //ÏûÏ¢¶ÓÁĞ 
   INT16U m_Count; //¼ÆÊ±Æ÷
   BOOLEAN m_PressSta; //´¦Àíµ÷ÓÃ×´Ì¬¼ÇÂ¼
 //************************ÒÔÏÂÔö¼ÓÄ£¿éÄÚ²¿Ê¹ÓÃµÄ±äÁ¿»òÕßÆäËüÔªËØ******************************//  
   PUARTSRCDATA m_pData;
	 PSYSPARAMDATA m_pSysData; //È«¾Ö±äÁ¿
	 PSYSCONFIGDATA m_pCfgData; //È«¾Ö±äÁ¿
		PSYSCALCDATA m_pCalData; //È«¾Ö±äÁ¿
		PSYSADJDATA m_pAdjData;
}MODULESCREENDRIVERDATA,*PMODULESCREENDRIVERDATA;

typedef struct ModuleScreenDriver //·şÎñÆ÷Àà
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
}MODULESCREENDRIVER,*PMODULESCREENDRIVER;
//*
//********************************************************************************************************
//* º¯ Êı Ãû : void CreateModuleScreenDriver(void)
//**------------------------------------------------------------------------------------------------------
//* Ãè    Êö : ´´½¨Ä£¿é
//**------------------------------------------------------------------------------------------------------
//* ÊäÈë²ÎÊı : PMODULEBASE. ¿ÕÖ¸Õë
//**------------------------------------------------------------------------------------------------------
//* Êä³ö²ÎÊı : PMODULEBASE. ÉêÇëÄÚ´æ¿Õ¼äºó·µ»Ø»ùÀàÖ¸Õë
//**------------------------------------------------------------------------------------------------------
//* ·µ   »Ø  : PMODULESCREENDRIVERDATA.ÉêÇëÄÚ´æ¿Õ¼äºó·µ»Ø»ùÀàÊı¾İÖ¸Õë
//********************************************************************************************************
//*
extern PMODULEBASE CreateModuleScreenDriver(PMODULESERVERDATA pServerData);
extern void SendSrcUartData(uint16_t data); //ÓÉÇı¶¯µ÷ÓÃ£¬»º³åÇøÑ¹ÈëÊı¾İ¼°Êı¾İÁ÷·Ö°ü
//************************ÄÚ²¿´¦Àíº¯ÊıÊµÏÖ******************************//
static BOOLEAN ModuleScreenDriverInit(void* pArg);
static BOOLEAN ModuleScreenDriverReset(void* pArg);
static BOOLEAN ModuleScreenDriverStart(void* pArg);
static BOOLEAN ModuleScreenDriverStop(void* pArg);
static BOOLEAN ModuleScreenDriverRelease(void* pArg);
static void ModuleScreenDriver50msProcess(void* pArg);
static void ScreenDriverMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);
static void ModeleScreenDriverUartProcess(void* pArg);
//************************Ä£¿é¹¦ÄÜÊµÏÖº¯Êı******************************//

//************************ÄÚ²¿´¦Àíº¯ÊıÊµÏÖ******************************//
static BOOLEAN SrcCheckSum(INT16U* buf, INT8U len); //Ğ£ÑéºÍÖ´ĞĞº¯Êı
static void SrcUnpack(void* pArg, INT16U *pData, INT8U len); //ÊäÈëÊı¾İ°ü£¬Ö´ĞĞĞ­Òé½âÎö
void UsartSendFullData_Screen(void* pArg);//·¢ËÍ´®¿ÚÏûÏ¢µ½ÆÁÄ»
#endif
