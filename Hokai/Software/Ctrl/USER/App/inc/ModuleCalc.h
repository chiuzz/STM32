//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* ÎÄ ¼ş Ãû : ModuleCalc.h
//*
//* ÎÄ¼şÃèÊö : Ö÷·şÎñÈÎÎñÎÄ¼ş
//*
//* ×÷    Õß : LGL
//* °æ    ±¾ : 
//* ±à Òë Æ÷ : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MODULE_CALC_H__
#define  __MODULE_CALC_H__

#include "common.h"
#include "struct_def.h"
#include "EEPROM.h"

#define EOM 0xFF	//°üÎ²
#define SOM 0xEF //°üÍ·
//#define DSOM 0 //°üÍ·
//#define CMD 1 //ÃüÁî
//#define D1 2 	 //Í¨µÀ0¸ß×Ö½Ú
//#define D2 3	 //Í¨µÀ0µÍ×Ö½Ú
//#define D3 4	 //Í¨µÀ1¸ß×Ö½Ú
//#define D4 5	 //Í¨µÀ1µÍ×Ö½Ú
//#define D5 6   //Í¨µÀ2¸ß×Ö½Ú
//#define DCC 7  //Ğ£Ñé
//#define DEOM 8 //°üÎ²
#define CALCBUFMAX 8 //Êı¾İ°ü³¤¶È 
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

#define  ADC_Convert_tims_Calc   20     //ÀÛ¼Æ×ª»»´ÎÊı


typedef struct ModuleCalcData //ÅäÖÃÀàÊı¾İ½á¹¹
{ 
   P_MSGQUEUE m_pMsgQueue;  //ÏûÏ¢¶ÓÁĞ 
   INT16U m_Count; //¼ÆÊ±Æ÷
   BOOLEAN m_PressSta; //´¦Àíµ÷ÓÃ×´Ì¬¼ÇÂ¼
	INT32U Temp1AD_Calc;
	INT32U Temp2AD_Calc;
	INT32U Temp3AD_Calc;
	INT16U ConverTimes_Calc; 
	INT32U AD1Value_Calc;
	INT32U AD2Value_Calc;
	INT32U AD3Value_Calc;
	INT32U UsartSendFlag;
	INT16U m_AD_RFlag;       //½ÓÊÕ×´Ì¬±ê¼Ç
	INT16U m_CheckCH;    //Ğ£×¼Í¨µÀ
	INT16U m_CheckMod;    //Ğ£×¼Ä£Ê½
 //************************ÒÔÏÂÔö¼ÓÄ£¿éÄÚ²¿Ê¹ÓÃµÄ±äÁ¿»òÕßÆäËüÔªËØ******************************//  
   PSYSPARAMDATA m_pSysData; //È«¾Ö±äÁ¿
	 PSYSCONFIGDATA m_pCfgData; //È«¾Ö±äÁ¿
		PSYSCALCDATA m_pCalData; //È«¾Ö±äÁ¿
		PSYSADJDATA m_pAdjData;
	 PUARTCALCDATA m_pData;
	 
}MODULECALCDATA,*PMODULECALCDATA;

typedef struct ModuleCalc //·şÎñÆ÷Àà
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
}MODULECALC,*PMODULECALC;
//*
//********************************************************************************************************
//* º¯ Êı Ãû : void CreateModuleCalc(void)
//**------------------------------------------------------------------------------------------------------
//* Ãè    Êö : ´´½¨Ä£¿é
//**------------------------------------------------------------------------------------------------------
//* ÊäÈë²ÎÊı : PMODULEBASE. ¿ÕÖ¸Õë
//**------------------------------------------------------------------------------------------------------
//* Êä³ö²ÎÊı : PMODULEBASE. ÉêÇëÄÚ´æ¿Õ¼äºó·µ»Ø»ùÀàÖ¸Õë
//**------------------------------------------------------------------------------------------------------
//* ·µ   »Ø  : PMODULECALCDATA.ÉêÇëÄÚ´æ¿Õ¼äºó·µ»Ø»ùÀàÊı¾İÖ¸Õë
//********************************************************************************************************
//*
extern PMODULEBASE CreateModuleCalc(PMODULESERVERDATA pServerData);

//************************ÄÚ²¿´¦Àíº¯ÊıÊµÏÖ******************************//
static BOOLEAN ModuleCalcInit(void* pArg);
static BOOLEAN ModuleCalcReset(void* pArg);
static BOOLEAN ModuleCalcStart(void* pArg);
static BOOLEAN ModuleCalcStop(void* pArg);
static BOOLEAN ModuleCalcRelease(void* pArg);
static void ModuleCalc1sProcess(void* pArg);
static void ModuleCalc10msProcess(void* pArg);
static void ModeleCalcUartProcess(void* pArg);
static void CalcMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);

//************************Ä£¿é¹¦ÄÜÊµÏÖº¯Êı******************************//
extern void SendUartData(uint16_t data); //ÓÉÇı¶¯µ÷ÓÃ£¬»º³åÇøÑ¹ÈëÊı¾İ¼°Êı¾İÁ÷·Ö°ü
//************************ÄÚ²¿´¦Àíº¯ÊıÊµÏÖ******************************//
static void Unpack(void* pArg, INT16U *pData, INT8U len); //ÊäÈëÊı¾İ°ü£¬Ö´ĞĞĞ­Òé½âÎö
static BOOLEAN CheckSum(INT16U* buf, INT8U len); //Ğ£ÑéºÍÖ´ĞĞº¯Êı
static void GetUartData(void* pArg); //³ÌĞò¹¦ÄÜÄ£¿é½â°üÇı¶¯º¯Êı
void SensorCheck(void* pArg); //´«¸ĞÆ÷Ğ£×¼
void  HardwareCheck(void* pArg);  //Ó²¼şĞ£×¼

#endif
