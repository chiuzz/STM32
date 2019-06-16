//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* 文 件 名 : ModuleDect.h
//*
//* 文件描述 : 主服务任务文件
//*
//* 作    者 : LGL
//* 版    本 : 
//* 编 译 器 : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MODULE_DECT_H__
#define  __MODULE_DECT_H__

#include "common.h"
#include "struct_def.h"

#define MAXDATANUM 10
typedef struct ModuleDectData //配置类数据结构
{ 
   P_MSGQUEUE m_pMsgQueue;  //消息队列 
	 PCONFIGDATA m_pSysData;     //系统数据
   INT16U m_Count; //计时器
   BOOLEAN m_PressSta; //处理调用状态记录
 //************************以下增加模块内部使用的变量或者其它元素******************************//  
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

typedef struct ModuleDect //服务器类
{ 
    char m_ModName[16];  
    BOOLEAN (*pModeleInit)(void* pArg); //初始化 输入m_pBaseData
    BOOLEAN (*pModeleReset)(void* pArg); //复位 输入m_pBaseData
    BOOLEAN (*pModeleStart)(void* pArg); //开始 输入m_pBaseData
    BOOLEAN (*pModeleStop)(void* pArg); //停止 输入m_pBaseData
    BOOLEAN (*pModeleRelease)(void* pArg); //释放 输入m_pBaseData
		void (*pMsgNotify)(PVOID pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf); //消息处理 主任务
    void (*pModele10msProcess)(void* pArg); //10ms调度任务
    void (*pModele50msProcess)(void* pArg); //50ms调度任务
    void (*pModele1sProcess)(void* pArg);  //1s调度任务
		void (*pModele1msProcess)(void* pArg);  //1ms调度任务
    PVOID m_pBaseData;
}MODULEDECT,*PMODULEDECT;
//*
//********************************************************************************************************
//* 函 数 名 : void CreateModuleDect(void)
//**------------------------------------------------------------------------------------------------------
//* 描    述 : 创建模块
//**------------------------------------------------------------------------------------------------------
//* 输入参数 : PMODULEBASE. 空指针
//**------------------------------------------------------------------------------------------------------
//* 输出参数 : PMODULEBASE. 申请内存空间后返回基类指针
//**------------------------------------------------------------------------------------------------------
//* 返   回  : PMODULEDECTDATA.申请内存空间后返回基类数据指针
//********************************************************************************************************
//*
extern PMODULEBASE CreateModuleDect(PMODULESERVERDATA pServerData);

//************************内部处理函数实现******************************//
static BOOLEAN ModuleDectInit(void* pArg);
static BOOLEAN ModuleDectReset(void* pArg);
static BOOLEAN ModuleDectStart(void* pArg);
static BOOLEAN ModuleDectStop(void* pArg);
static BOOLEAN ModuleDectRelease(void* pArg);
static void ModuleDect1sProcess(void* pArg);
static void DectMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);

//************************模块功能实现函数******************************//

//************************内部处理函数实现******************************//
static INT16U GetTempAdData(PMODULEDECTDATA pData, INT16U ch, INT16U ad);
static INT8U SendPKGCheckSum(INT8U* pData, INT8U num);
static INT16U CalcTempData(PMODULEDECTDATA pData, INT16U ch);

static INT16U CalcTempDataMulti(PMODULEDECTDATA pData, INT16U ch);
static INT16U CalcTempDataSingle(PMODULEDECTDATA pData, INT16U ch);
static INT16U CalcTempDataBinomial(PMODULEDECTDATA pData, INT16U ch);
static void ModeleDectPrintInfo(PMODULEDECTDATA pData);//打印参数
static void GetParamMulti(PMODULEDECTDATA pData);//计算校准参数
static void GetParamBinomial(PMODULEDECTDATA pData);//计算校准参数
static INT16U CalcTempDataMulti(PMODULEDECTDATA pData, INT16U ch);//计算温度
static void CalcBinomial(INT16U *pArrAd, INT16U *pArrTemp, FP32 *pa, FP32 *pb, FP32 *pc );
static void ModeleDectSendPkg(PMODULEDECTDATA pData);
#endif
