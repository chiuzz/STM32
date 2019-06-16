//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* ÎÄ ¼þ Ãû : ModuleTempProc.h
//*
//* ÎÄ¼þÃèÊö : Ö÷·þÎñÈÎÎñÎÄ¼þ
//*
//* ×÷    Õß : LGL
//* °æ    ±¾ : 
//* ±à Òë Æ÷ : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MODULE_TEMPPROC_H__
#define  __MODULE_TEMPPROC_H__

#include "common.h"
#include "struct_def.h"
#define  ADC_Interval       5     //5ms
#define  ADC_Convert_tims   1000     //ÀÛ¼Æ×ª»»´ÎÊý
//#define  Vref   3299     //²Î¿¼µçÑ¹
//#define  Offset   15     //Æ«ÒÆÁ¿
#define BUFMAX 20
#define DATABUF (BUFMAX*2)

typedef struct UartData 
{ 
   INT16U m_DataBuf[DATABUF];
   INT16U m_index;
   INT16U m_MarkIndex;
   BOOLEAN m_MarkSta;
   INT16U m_buf[BUFMAX];
   INT8U m_buflen;
   BOOLEAN m_Sta;
}UARTDATA,*PUARTDATA;


typedef struct ModuleTempProcData //ÅäÖÃÀàÊý¾Ý½á¹¹
{ 
	P_MSGQUEUE m_pMsgQueue;  //ÏûÏ¢¶ÓÁÐ 
	INT16U T_Count; //¼ÆÊ±Æ÷
	BOOLEAN m_PressSta; //´¦Àíµ÷ÓÃ×´Ì¬¼ÇÂ¼
	INT32U Temp1AD;
	INT32U Temp2AD;
	INT32U Temp3AD;
	INT16U ConverTimes; 
	INT32U AD1Value;
	INT32U AD2Value;
	INT32U AD3Value;
	//************************ÒÔÏÂÔö¼ÓÄ£¿éÄÚ²¿Ê¹ÓÃµÄ±äÁ¿»òÕßÆäËüÔªËØ******************************//  
	PSYSPARAMDATA m_pSysData; //È«¾Ö±äÁ¿
	PSYSCONFIGDATA m_pCfgData; //È«¾Ö±äÁ¿
	PSYSCALCDATA m_pCalData; //È«¾Ö±äÁ¿
	PSYSADJDATA m_pAdjData;
	PUARTDATA m_pData;
   
}MODULETEMPPROCDATA,*PMODULETEMPPROCDATA;

typedef struct ModuleTempProc //·þÎñÆ÷Àà
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
	  void (*pStart)(void* pArg);
}MODULETEMPPROC,*PMODULETEMPPROC;
//*
//********************************************************************************************************
//* º¯ Êý Ãû : void CreateModuleTempProc(void)
//**------------------------------------------------------------------------------------------------------
//* Ãè    Êö : ´´½¨Ä£¿é
//**------------------------------------------------------------------------------------------------------
//* ÊäÈë²ÎÊý : PMODULEBASE. ¿ÕÖ¸Õë
//**------------------------------------------------------------------------------------------------------
//* Êä³ö²ÎÊý : PMODULEBASE. ÉêÇëÄÚ´æ¿Õ¼äºó·µ»Ø»ùÀàÖ¸Õë
//**------------------------------------------------------------------------------------------------------
//* ·µ   »Ø  : PMODULETEMPPROCDATA.ÉêÇëÄÚ´æ¿Õ¼äºó·µ»Ø»ùÀàÊý¾ÝÖ¸Õë
//********************************************************************************************************
//*
extern PMODULEBASE CreateModuleTempProc(PMODULESERVERDATA pServerData);

//************************ÄÚ²¿´¦Àíº¯ÊýÊµÏÖ******************************//
static BOOLEAN ModuleTempProcInit(void* pArg);
static BOOLEAN ModuleTempProcReset(void* pArg);
static BOOLEAN ModuleTempProcStart(void* pArg);
static BOOLEAN ModuleTempProcStop(void* pArg);
static BOOLEAN ModuleTempProcRelease(void* pArg);
static void ModuleTempProc1msProcess(void* pArg);
static void TempProcMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);

//************************Ä£¿é¹¦ÄÜÊµÏÖº¯Êý******************************//
void GetTemp1(PMODULETEMPPROCDATA pData);//ÌåÎÂ1
void GetTemp2(PMODULETEMPPROCDATA pData);//ÌåÎÂ2
void GetWaterTemp(PMODULETEMPPROCDATA pData);//Ë®ÎÂ
void Calc_K_B_Value(PMODULETEMPPROCDATA pData);//¼ÆËãk_bµÄÖµ
//¼ÆËãKÖµ
FP32 calculateSlope(INT16U x_V[2], INT16U y_V[2]);
//¼ÆËã³£Êýb
FP32 calculateConstant(INT16U x_V[2], INT16U y_V[2]);


extern void SendUartData(uint16_t data);
static BOOLEAN CheckSum(INT16U* buf, INT8U len);
static void GetUartData(void* pArg);
static void Start(void* pArg);
static void Unpack(void* pArg, INT16U *pData, INT8U len);

//************************ÄÚ²¿´¦Àíº¯ÊýÊµÏÖ******************************//
#endif
