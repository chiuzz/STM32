//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* 文 件 名 : ModuleTempProc.h
//*
//* 文件描述 : 主服务任务文件
//*
//* 作    者 : LGL
//* 版    本 : 
//* 编 译 器 : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MODULE_TEMPPROC_H__
#define  __MODULE_TEMPPROC_H__

#include "common.h"
#include "struct_def.h"
#define  ADC_Interval       5     //5ms
#define  ADC_Convert_tims   1000     //累计转换次数
//#define  Vref   3299     //参考电压
//#define  Offset   15     //偏移量
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


typedef struct ModuleTempProcData //配置类数据结构
{ 
	P_MSGQUEUE m_pMsgQueue;  //消息队列 
	INT16U T_Count; //计时器
	BOOLEAN m_PressSta; //处理调用状态记录
	INT32U Temp1AD;
	INT32U Temp2AD;
	INT32U Temp3AD;
	INT16U ConverTimes; 
	INT32U AD1Value;
	INT32U AD2Value;
	INT32U AD3Value;
	//************************以下增加模块内部使用的变量或者其它元素******************************//  
	PSYSPARAMDATA m_pSysData; //全局变量
	PSYSCONFIGDATA m_pCfgData; //全局变量
	PSYSCALCDATA m_pCalData; //全局变量
	PSYSADJDATA m_pAdjData;
	PUARTDATA m_pData;
   
}MODULETEMPPROCDATA,*PMODULETEMPPROCDATA;

typedef struct ModuleTempProc //服务器类
{ 
    char m_ModName[16];  
    BOOLEAN (*pModeleInit)(void* pArg); //初始化 输入m_pBaseData
    BOOLEAN (*pModeleReset)(void* pArg); //复位 输入m_pBaseData
    BOOLEAN (*pModeleStart)(void* pArg); //开始 输入m_pBaseData
    BOOLEAN (*pModeleStop)(void* pArg); //停止 输入m_pBaseData
    BOOLEAN (*pModeleRelease)(void* pArg); //释放 输入m_pBaseData
	  void (*pMsgNotify)(PVOID pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf); //消息处理 主任务
		void (*pModele1msProcess)(void* pArg); //10ms调度任�
    void (*pModele10msProcess)(void* pArg); //10ms调度任务
    void (*pModele50msProcess)(void* pArg); //50ms调度任务
    void (*pModele1sProcess)(void* pArg);  //1s调度任务
		void (*pModeleUartProcess)(void* pArg);  //1s调度任务
    PVOID m_pBaseData;
	  void (*pStart)(void* pArg);
}MODULETEMPPROC,*PMODULETEMPPROC;
//*
//********************************************************************************************************
//* 函 数 名 : void CreateModuleTempProc(void)
//**------------------------------------------------------------------------------------------------------
//* 描    述 : 创建模块
//**------------------------------------------------------------------------------------------------------
//* 输入参数 : PMODULEBASE. 空指针
//**------------------------------------------------------------------------------------------------------
//* 输出参数 : PMODULEBASE. 申请内存空间后返回基类指针
//**------------------------------------------------------------------------------------------------------
//* 返   回  : PMODULETEMPPROCDATA.申请内存空间后返回基类数据指针
//********************************************************************************************************
//*
extern PMODULEBASE CreateModuleTempProc(PMODULESERVERDATA pServerData);

//************************内部处理函数实现******************************//
static BOOLEAN ModuleTempProcInit(void* pArg);
static BOOLEAN ModuleTempProcReset(void* pArg);
static BOOLEAN ModuleTempProcStart(void* pArg);
static BOOLEAN ModuleTempProcStop(void* pArg);
static BOOLEAN ModuleTempProcRelease(void* pArg);
static void ModuleTempProc1msProcess(void* pArg);
static void TempProcMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);

//************************模块功能实现函数******************************//
void GetTemp1(PMODULETEMPPROCDATA pData);//体温1
void GetTemp2(PMODULETEMPPROCDATA pData);//体温2
void GetWaterTemp(PMODULETEMPPROCDATA pData);//水温
void Calc_K_B_Value(PMODULETEMPPROCDATA pData);//计算k_b的值
//计算K值
FP32 calculateSlope(INT16U x_V[2], INT16U y_V[2]);
//计算常数b
FP32 calculateConstant(INT16U x_V[2], INT16U y_V[2]);


extern void SendUartData(uint16_t data);
static BOOLEAN CheckSum(INT16U* buf, INT8U len);
static void GetUartData(void* pArg);
static void Start(void* pArg);
static void Unpack(void* pArg, INT16U *pData, INT8U len);

//************************内部处理函数实现******************************//
#endif
