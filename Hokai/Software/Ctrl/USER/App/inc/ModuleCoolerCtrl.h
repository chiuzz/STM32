//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* 文 件 名 : ModuleCoolerCtrl.h
//*
//* 文件描述 : 主服务任务文件
//*
//* 作    者 : LGL
//* 版    本 :
//* 编 译 器 : IAR EWARM 5.20
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
typedef struct ModuleCoolerCtrlData //配置类数据结构
{
    P_MSGQUEUE m_pMsgQueue;  //消息队列
    INT16U m_Count; //计时器
    BOOLEAN m_PressSta; //处理调用状态记录
//************************以下增加模块内部使用的变量或者其它元素******************************//
    PSYSPARAMDATA m_pSysData; //全局变量
		PSYSCONFIGDATA m_pCfgData; //全局变量
		PSYSCALCDATA m_pCalData; //全局变量
		PSYSADJDATA m_pAdjData;
    eCoolerSMachine m_CoolerSMachine;
    INT16U m_CoolCount;
} MODULECOOLERCTRLDATA,*PMODULECOOLERCTRLDATA;

typedef struct ModuleCoolerCtrl //服务器类
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
} MODULECOOLERCTRL,*PMODULECOOLERCTRL;
//*
//********************************************************************************************************
//* 函 数 名 : void CreateModuleCoolerCtrl(void)
//**------------------------------------------------------------------------------------------------------
//* 描    述 : 创建模块
//**------------------------------------------------------------------------------------------------------
//* 输入参数 : PMODULEBASE. 空指针
//**------------------------------------------------------------------------------------------------------
//* 输出参数 : PMODULEBASE. 申请内存空间后返回基类指针
//**------------------------------------------------------------------------------------------------------
//* 返   回  : PMODULECOOLERCTRLDATA.申请内存空间后返回基类数据指针
//********************************************************************************************************
//*
extern PMODULEBASE CreateModuleCoolerCtrl(PMODULESERVERDATA pServerData);

//************************内部处理函数实现******************************//
static BOOLEAN ModuleCoolerCtrlInit(void* pArg);
static BOOLEAN ModuleCoolerCtrlReset(void* pArg);
static BOOLEAN ModuleCoolerCtrlStart(void* pArg);
static BOOLEAN ModuleCoolerCtrlStop(void* pArg);
static BOOLEAN ModuleCoolerCtrlRelease(void* pArg);
static void ModuleCoolerCtrl1sProcess(void* pArg);
static void ModuleCoolerCtrl50msProcess(void* pArg);
static void CoolerCtrlMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);

//************************模块功能实现函数******************************//
static void SetCoolerWORK(void* pArg, eStatus sta);
static void CoolerWorkMachineProc(void* pArg);
static INT16U CalcCoolerTempDip(INT16U Temp, INT16U dsp);
//************************内部处理函数实现******************************//
#endif
