//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* 文 件 名 : ModuleSystemProc.h
//*
//* 文件描述 : 主服务任务文件
//*
//* 作    者 : LGL
//* 版    本 :
//* 编 译 器 : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MODULE_SYSTEMPROC_H__
#define  __MODULE_SYSTEMPROC_H__

#define SINGLEMODE 1
#include "common.h"
#include "struct_def.h"

typedef enum
{
    SYSTEM_CHECK = 0,
    SYSTEM_CHEKC_E2PROM,
    SYSTEM_CHEKC_E2PROM_HOLD,
    SYSTEM_MONITOR,
}	eSystemMachine;

typedef enum
{
    SYSTEM_STOP = 0,
    SYSTEM_STOP_HOLD,
    SYSTEM_COOLER,
    SYSTEM_COOLER_HOLD,
    SYSTEM_HEATER,
    SYSTEM_HEATER_HOLD,
    SYSTEM_INVALID = 255,
}	eSystemWorkStatus;

typedef enum
{
    BUMP_STOP = 0,
    BUMP_STOP_HOLD,
    BUMP_START,
    BUMP_START_HOLD,
    BUMP_INVALID = 255,
}	eBumpWorkStatus;

typedef struct ModuleSystemProcData //配置类数据结构
{
    P_MSGQUEUE m_pMsgQueue;  //消息队列
    INT16U m_Count; //计时器
    BOOLEAN m_PressSta; //处理调用状态记录
//************************以下增加模块内部使用的变量或者其它元素******************************//
    INT16U m_Float1Count; //计时器
    INT16U m_Float2Count; //计时器
    PSYSPARAMDATA m_pSysData; //全局变量
    PSYSCONFIGDATA m_pCfgData; //全局变量
    PSYSCALCDATA m_pCalData; //全局变量
    PSYSADJDATA m_pAdjData;
    eSystemMachine m_SystemMAC;
    eSystemWorkStatus m_SystemWorkSta;
    eBumpWorkStatus m_Bump1Sta;
    eBumpWorkStatus m_Bump2Sta;
    BOOLEAN m_WorkModePressKey; //按键状态
    BOOLEAN m_Bump1PressKey; //按键状态
    BOOLEAN m_Bump2PressKey; //按键状态
    BOOLEAN m_E2PROMERROR;

} MODULESYSTEMPROCDATA, *PMODULESYSTEMPROCDATA;

typedef struct ModuleSystemProc //服务器类
{
    char m_ModName[16];
    BOOLEAN (*pModeleInit)(void* pArg); //初始化 输入m_pBaseData
    BOOLEAN (*pModeleReset)(void* pArg); //复位 输入m_pBaseData
    BOOLEAN (*pModeleStart)(void* pArg); //开始 输入m_pBaseData
    BOOLEAN (*pModeleStop)(void* pArg); //停止 输入m_pBaseData
    BOOLEAN (*pModeleRelease)(void* pArg); //释放 输入m_pBaseData
    void (*pMsgNotify)(PVOID pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf); //消息处理 主任务
    void (*pModele1msProcess)(void* pArg); //10ms调度任?
    void (*pModele10msProcess)(void* pArg); //10ms调度任务
    void (*pModele50msProcess)(void* pArg); //50ms调度任务
    void (*pModele1sProcess)(void* pArg);  //1s调度任务
    void (*pModeleUartProcess)(void* pArg);  //1s调度任务
    PVOID m_pBaseData;
} MODULESYSTEMPROC, *PMODULESYSTEMPROC;

//*
//********************************************************************************************************
//* 函 数 名 : void CreateModuleSystemProc(void)
//**------------------------------------------------------------------------------------------------------
//* 描    述 : 创建模块
//**------------------------------------------------------------------------------------------------------
//* 输入参数 : PMODULEBASE. 空指针
//**------------------------------------------------------------------------------------------------------
//* 输出参数 : PMODULEBASE. 申请内存空间后返回基类指针
//**------------------------------------------------------------------------------------------------------
//* 返   回  : PMODULESYSTEMPROCDATA.申请内存空间后返回基类数据指针
//********************************************************************************************************
//*
extern PMODULEBASE CreateModuleSystemProc(PMODULESERVERDATA pServerData);

//************************内部处理函数实现******************************//
static BOOLEAN ModuleSystemProcInit(void* pArg);
static BOOLEAN ModuleSystemProcReset(void* pArg);
static BOOLEAN ModuleSystemProcStart(void* pArg);
static BOOLEAN ModuleSystemProcStop(void* pArg);
static BOOLEAN ModuleSystemProcRelease(void* pArg);
static void ModuleSystemProc1sProcess(void* pArg);
static void SystemProcMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);

//************************模块功能实现函数******************************//
void SetSysAlm(PMODULESYSTEMPROCDATA pData);

//************************内部处理函数实现******************************//

static void SystemMachineProc(void* pArg);
static void SystemWorkStatusProc(void* pArg);
static void Bump1WorkStatusProc(void* pArg);
static void Bump2WorkStatusProc(void* pArg);
static void SystemMonitor(void* pArg);
static void GetWaterStatus(void* pArg);

static void TrigerAddSet(PMODULESYSTEMPROCDATA pData);//按键加
static void TrigerDecSet(PMODULESYSTEMPROCDATA pData);//按键减
static void TrigerTemp1Set(PMODULESYSTEMPROCDATA pData);
static void TrigerTemp2Set(PMODULESYSTEMPROCDATA pData);
static void TrigerTempWaterSet(PMODULESYSTEMPROCDATA pData);
static BOOLEAN SetFocusStatus(PMODULESYSTEMPROCDATA pData, eFocusStatus Focus);
static void TrigerAlmvolSet(PMODULESYSTEMPROCDATA pData);
static void TrigerCal1Set(PMODULESYSTEMPROCDATA pData);
static void TrigerCal2Set(PMODULESYSTEMPROCDATA pData);
#endif
