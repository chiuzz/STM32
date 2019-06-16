//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* 文 件 名 : ModuleXxx.h
//*
//* 文件描述 : 主服务任务文件
//*
//* 作    者 : LGL
//* 版    本 : 
//* 编 译 器 : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MODULE_XXX_H__
#define  __MODULE_XXX_H__

#include "common.h"
#include "struct_def.h"

typedef struct ModuleXxxData //配置类数据结构
{ 
   P_MSGQUEUE m_pMsgQueue;  //消息队列 
   INT16U m_Count; //计时器
   BOOLEAN m_PressSta; //处理调用状态记录
 //************************以下增加模块内部使用的变量或者其它元素******************************//  
   
}MODULEXXXDATA,*PMODULEXXXDATA;

typedef struct ModuleXxx //服务器类
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
    PVOID m_pBaseData;
}MODULEXXX,*PMODULEXXX;
//*
//********************************************************************************************************
//* 函 数 名 : void CreateModuleXxx(void)
//**------------------------------------------------------------------------------------------------------
//* 描    述 : 创建模块
//**------------------------------------------------------------------------------------------------------
//* 输入参数 : PMODULEBASE. 空指针
//**------------------------------------------------------------------------------------------------------
//* 输出参数 : PMODULEBASE. 申请内存空间后返回基类指针
//**------------------------------------------------------------------------------------------------------
//* 返   回  : PMODULEXXXDATA.申请内存空间后返回基类数据指针
//********************************************************************************************************
//*
extern PMODULEBASE CreateModuleXxx(PMODULESERVERDATA pServerData)；

//************************内部处理函数实现******************************//
static BOOLEAN ModuleXxxInit(void* pArg);
static BOOLEAN ModuleXxxReset(void* pArg);
static BOOLEAN ModuleXxxStart(void* pArg);
static BOOLEAN ModuleXxxStop(void* pArg);
static BOOLEAN ModuleXxxRelease(void* pArg);
static void ModuleXxx1sProcess(void* pArg);
static void XxxMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);

//************************模块功能实现函数******************************//

//************************内部处理函数实现******************************//
#endif
