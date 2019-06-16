//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* 文 件 名 : ModuleServer.h
//*
//* 文件描述 : 主服务任务文件 实现调度，消息队列，模块容器
//*
//* 作    者 : LGL
//* 版    本 : 
//* 编 译 器 : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MODULE_SERVER_H__
#define  __MODULE_SERVER_H__

#include "common.h"

typedef struct SubModItem  //链表元素
{ 
    PMODULEBASE pObj;
    INT8U tags;
}SUBMODITEM,*PSUBMODITEM;

typedef struct ModuleServer //服务器类
{ 
    char m_ModName[16];  
    BOOLEAN (*pModeleInit)(void* pArg); //初始化 输入m_pBaseData
    BOOLEAN (*pModeleReset)(void* pArg); //复位 输入m_pBaseData
    BOOLEAN (*pModeleStart)(void* pArg); //开始 输入m_pBaseData
    BOOLEAN (*pModeleStop)(void* pArg); //停止 输入m_pBaseData
    BOOLEAN (*pModeleRelease)(void* pArg); //释放 输入m_pBaseData
    void (*pMsgNotify)(PVOID pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf); //消息处理 主任务
	  void (*pModele1msProcess)(void* pArg);  //1ms调度任务	
    void (*pModele10msProcess)(void* pArg); //10ms调度任务
    void (*pModele50msProcess)(void* pArg); //50ms调度任务    
		void (*pModele1sProcess)(void* pArg);  //1s调度任务
	  void (*pModeleUartProcess)(void* pArg); //UART调度任务
    PVOID m_pBaseData;
    void (*pMsgNotifyProcess)(PVOID pArg);
    void (*pSubModPushBack)(PVOID pArg, PSUBMODITEM pObj);
}MODULESERVER,*PMODULESERVER;

//*
//********************************************************************************************************
//* 函 数 名 : void CreateModuleConfig(void)
//**------------------------------------------------------------------------------------------------------
//* 描    述 : 创建配置管理模块
//**------------------------------------------------------------------------------------------------------
//* 输入参数 : PMODULEBASE. 空指针
//**------------------------------------------------------------------------------------------------------
//* 输出参数 : PMODULEBASE. 申请内存空间后返回基类指针
//**------------------------------------------------------------------------------------------------------
//* 返   回  : PMODULECONFIGDATA.申请内存空间后返回基类数据指针
//********************************************************************************************************
//*
extern PMODULEBASE CreateModuleServer(void);

//************************内部处理函数实现******************************//
static BOOLEAN ModuleServerInit(void* pArg);
static BOOLEAN ModuleServerReset(void* pArg);
static BOOLEAN ModuleServerStart(void* pArg);
static BOOLEAN ModuleServerStop(void* pArg);
static BOOLEAN ModuleServerRelease(void* pArg);
static void ModuleServer10msProcess(void* pArg);
static void ModuleServer50msProcess(void* pArg);
static void ModuleServer1sProcess(void* pArg);
static void ModuleServer1msProcess(void* pArg);
static void ModuleServerUartProcess(void* pArg);
static void ServerMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf); 
static void MsgNotifyProcess(PVOID pArg);

static void SubModPushBack(PVOID pArg, PSUBMODITEM pObj);
static int SubModReset(int Tag, void* Memory, void* Args);
static int SubModStart(int Tag, void* Memory, void* Args);
static int SubModStop(int Tag, void* Memory, void* Args);
static int SubModRelease(int Tag, void* Memory, void* Args);
static int SubMod10msProcess(int Tag, void* Memory, void* Args);
static int SubMod1msProcess(int Tag, void* Memory, void* Args);
static int SubMod50msProcess(int Tag, void* Memory, void* Args);
static int SubMod1sProcess(int Tag, void* Memory, void* Args);
static int SubModUartProcess(int Tag, void* Memory, void* Args);
static int SubModMsgNotify(int Tag, void* Memory, void* Args);
//************************模块功能实现函数******************************//
//static void ConfigSave();//置保存实现函数
//************************内部处理函数实现******************************//
#endif
