//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* 文 件 名 : ModuleHeaterCtrl.h
//*
//* 文件描述 : 主服务任务文件
//*
//* 作    者 : LGL
//* 版    本 :
//* 编 译 器 : IAR EWARM 5.20
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
typedef struct ModuleHeaterCtrlData //配置类数据结构
{
    P_MSGQUEUE m_pMsgQueue;  //消息队列
    INT16U m_Count; //计时器
    INT16U m_Count2; //计时器2
    BOOLEAN m_PressSta; //处理调用状态记录
//************************以下增加模块内部使用的变量或者其它元素******************************//
    PSYSPARAMDATA m_pSysData; //全局变量
    PSYSCONFIGDATA m_pCfgData; //全局变量
    PSYSCALCDATA m_pCalData; //全局变量
    PSYSADJDATA m_pAdjData;
    eHeaterSMachine m_HeaterSMachine;
    eHeaterAlmMachine m_HeaterAlmMac[HEATERALMNUM];
    INT16S m_ErrSum;
    INT16U m_ProcCount;
} MODULEHEATERCTRLDATA,*PMODULEHEATERCTRLDATA;

typedef struct ModuleHeaterCtrl //服务器类
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
} MODULEHEATERCTRL,*PMODULEHEATERCTRL;
//*
//********************************************************************************************************
//* 函 数 名 : void CreateModuleHeaterCtrl(void)
//**------------------------------------------------------------------------------------------------------
//* 描    述 : 创建模块
//**------------------------------------------------------------------------------------------------------
//* 输入参数 : PMODULEBASE. 空指针
//**------------------------------------------------------------------------------------------------------
//* 输出参数 : PMODULEBASE. 申请内存空间后返回基类指针
//**------------------------------------------------------------------------------------------------------
//* 返   回  : PMODULEHEATERCTRLDATA.申请内存空间后返回基类数据指针
//********************************************************************************************************
//*
extern PMODULEBASE CreateModuleHeaterCtrl(PMODULESERVERDATA pServerData);

//************************内部处理函数实现******************************//
static BOOLEAN ModuleHeaterCtrlInit(void* pArg);
static BOOLEAN ModuleHeaterCtrlReset(void* pArg);
static BOOLEAN ModuleHeaterCtrlStart(void* pArg);
static BOOLEAN ModuleHeaterCtrlStop(void* pArg);
static BOOLEAN ModuleHeaterCtrlRelease(void* pArg);
static void ModuleHeaterCtrl1sProcess(void* pArg);
static void ModuleHeaterCtrl50msProcess(void* pArg);
static void HeaterCtrlMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);

//************************模块功能实现函数******************************//
static void SetHeaterWORK(void* pArg, eStatus sta);
static void HeaterWorkMachineProc(void* pArg);
static void HeaterAlmMachineProc(void* pArg,INT16U index); //每1s运行
//************************内部处理函数实现******************************//
#endif
