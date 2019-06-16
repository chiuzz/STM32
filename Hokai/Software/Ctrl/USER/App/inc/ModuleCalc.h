//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* 文 件 名 : ModuleCalc.h
//*
//* 文件描述 : 主服务任务文件
//*
//* 作    者 : LGL
//* 版    本 : 
//* 编 译 器 : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MODULE_CALC_H__
#define  __MODULE_CALC_H__

#include "common.h"
#include "struct_def.h"
#include "EEPROM.h"

#define EOM 0xFF	//包尾
#define SOM 0xEF //包头
//#define DSOM 0 //包头
//#define CMD 1 //命令
//#define D1 2 	 //通道0高字节
//#define D2 3	 //通道0低字节
//#define D3 4	 //通道1高字节
//#define D4 5	 //通道1低字节
//#define D5 6   //通道2高字节
//#define DCC 7  //校验
//#define DEOM 8 //包尾
#define CALCBUFMAX 8 //数据包长度 
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

#define  ADC_Convert_tims_Calc   20     //累计转换次数


typedef struct ModuleCalcData //配置类数据结构
{ 
   P_MSGQUEUE m_pMsgQueue;  //消息队列 
   INT16U m_Count; //计时器
   BOOLEAN m_PressSta; //处理调用状态记录
	INT32U Temp1AD_Calc;
	INT32U Temp2AD_Calc;
	INT32U Temp3AD_Calc;
	INT16U ConverTimes_Calc; 
	INT32U AD1Value_Calc;
	INT32U AD2Value_Calc;
	INT32U AD3Value_Calc;
	INT32U UsartSendFlag;
	INT16U m_AD_RFlag;       //接收状态标记
	INT16U m_CheckCH;    //校准通道
	INT16U m_CheckMod;    //校准模式
 //************************以下增加模块内部使用的变量或者其它元素******************************//  
   PSYSPARAMDATA m_pSysData; //全局变量
	 PSYSCONFIGDATA m_pCfgData; //全局变量
		PSYSCALCDATA m_pCalData; //全局变量
		PSYSADJDATA m_pAdjData;
	 PUARTCALCDATA m_pData;
	 
}MODULECALCDATA,*PMODULECALCDATA;

typedef struct ModuleCalc //服务器类
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
}MODULECALC,*PMODULECALC;
//*
//********************************************************************************************************
//* 函 数 名 : void CreateModuleCalc(void)
//**------------------------------------------------------------------------------------------------------
//* 描    述 : 创建模块
//**------------------------------------------------------------------------------------------------------
//* 输入参数 : PMODULEBASE. 空指针
//**------------------------------------------------------------------------------------------------------
//* 输出参数 : PMODULEBASE. 申请内存空间后返回基类指针
//**------------------------------------------------------------------------------------------------------
//* 返   回  : PMODULECALCDATA.申请内存空间后返回基类数据指针
//********************************************************************************************************
//*
extern PMODULEBASE CreateModuleCalc(PMODULESERVERDATA pServerData);

//************************内部处理函数实现******************************//
static BOOLEAN ModuleCalcInit(void* pArg);
static BOOLEAN ModuleCalcReset(void* pArg);
static BOOLEAN ModuleCalcStart(void* pArg);
static BOOLEAN ModuleCalcStop(void* pArg);
static BOOLEAN ModuleCalcRelease(void* pArg);
static void ModuleCalc1sProcess(void* pArg);
static void ModuleCalc10msProcess(void* pArg);
static void ModeleCalcUartProcess(void* pArg);
static void CalcMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);

//************************模块功能实现函数******************************//
extern void SendUartData(uint16_t data); //由驱动调用，缓冲区压入数据及数据流分包
//************************内部处理函数实现******************************//
static void Unpack(void* pArg, INT16U *pData, INT8U len); //输入数据包，执行协议解析
static BOOLEAN CheckSum(INT16U* buf, INT8U len); //校验和执行函数
static void GetUartData(void* pArg); //程序功能模块解包驱动函数
void SensorCheck(void* pArg); //传感器校准
void  HardwareCheck(void* pArg);  //硬件校准

#endif
