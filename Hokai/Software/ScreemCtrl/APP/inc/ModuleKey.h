//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* 文 件 名 : ModuleKey.h
//*
//* 文件描述 : 主服务任务文件
//*
//* 作    者 : LGL
//* 版    本 :
//* 编 译 器 : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MODULE_KEY_H__
#define  __MODULE_KEY_H__

#include "common.h"
#include "struct_def.h"

typedef enum
{
    KEY_STOP = 0,
    KEY_INIT,
    KEY_WORK,
}	eKeyWorkStatus;

typedef enum //校正模式
{
    KEY_OFF = 1,
    KEY_ON,
    KEY_TRI,
    KEY_TRI_MIT,
    KEY_TRI_CAL1,
    KEY_TRI_CAL2,
} eKeyScanMachine;


typedef enum //
{
    BEEP_STOP = 1,
    BEEP_ON,
    BEEP_ON_HOLD,
} eBeepMachine;
#define KEYNUM 11
typedef struct ModuleKeyData //配置类数据结构
{
    P_MSGQUEUE m_pMsgQueue;  //消息队列
    INT16U m_Count; //计时器
    BOOLEAN m_PressSta; //处理调用状态记录
    PCONFIGDATA m_pSysData;     //系统数据
//************************以下增加模块内部使用的变量或者其它元素******************************//
    eKeyWorkStatus m_KeyWorkSta;
    eAlmType m_AlmType;
    BOOLEAN m_AlmStatus;

    INT16U m_BeepCount;
    eBeepMachine m_BeepMac;
    eKeyScanMachine m_KeyScanMachine[KEYNUM];
    INT16U m_KeyMark[KEYNUM];
    INT16U m_KeyCount[KEYNUM];
    INT16U m_KeyLast[KEYNUM];

} MODULEKEYDATA, *PMODULEKEYDATA;

typedef struct ModuleKey //服务器类
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
    void (*pModele1msProcess)(void* pArg);  //1s调度任务
    PVOID m_pBaseData;
} MODULEKEY, *PMODULEKEY;
//*
//********************************************************************************************************
//* 函 数 名 : void CreateModuleKey(void)
//**------------------------------------------------------------------------------------------------------
//* 描    述 : 创建模块
//**------------------------------------------------------------------------------------------------------
//* 输入参数 : PMODULEBASE. 空指针
//**------------------------------------------------------------------------------------------------------
//* 输出参数 : PMODULEBASE. 申请内存空间后返回基类指针
//**------------------------------------------------------------------------------------------------------
//* 返   回  : PMODULEKEYDATA.申请内存空间后返回基类数据指针
//********************************************************************************************************
//*
extern PMODULEBASE CreateModuleKey(PMODULESERVERDATA pServerData);

//************************内部处理函数实现******************************//
static BOOLEAN ModuleKeyInit(void* pArg);
static BOOLEAN ModuleKeyReset(void* pArg);
static BOOLEAN ModuleKeyStart(void* pArg);
static BOOLEAN ModuleKeyStop(void* pArg);
static BOOLEAN ModuleKeyRelease(void* pArg);
static void ModuleKey1sProcess(void* pArg);
static void ModuleKey50msProcess(void* pArg);
static void ModuleKey10msProcess(void* pArg);
static void KeyMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);

//************************模块功能实现函数******************************//
static void GetButtonKey(void* pArg);//获取按键
static void BeepTriger(void* pArg);
static void KeyProcess(void* pArg, INT8U val, INT8U index);

static void PrintfKeyNum(INT16U index);
//************************内部处理函数实现******************************//
#endif
