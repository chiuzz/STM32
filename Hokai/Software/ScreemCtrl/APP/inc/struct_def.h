//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* 文 件 名 : struct_def.h
//*
//* 文件描述 : 系统结构定义文件
//*
//* 作    者 : LGL
//* 版    本 :
//* 编 译 器 : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __STRUCT_DEF_H__
#define  __STRUCT_DEF_H__

#include "MsgQueue.h"
#include "dllist.h"
#include "os_cpu.h"
#include "common.h"
// #include "os_cpu.h"
//typedef struct Struct
//{}STRUCT,*PSTRUCT;
//typedef enum {FALSE = 0, TRUE = !FALSE} bool;
typedef void*         PVOID;

//*********************************************************************************************************

typedef struct MsgItem  //消息链表元素
{
//    PVOID pArg;
    INT8U MsgId;
    INT16U lParam;
    INT16U wParam;
    void* pBuf;
} MSGITEM, *PMSGITEM;

//*********************************************************************************************************
//*****************************************    系统数据     *******************************************
//*********************************************************************************************************
typedef enum
{
    CalcMode = 1,
    StartMode,
}	eWorkMode;

//*********************************************************************************************************
//*****************************************    系统状态数据     *******************************************
//*********************************************************************************************************
#define MAXCHLNUM 7
typedef struct SysStatusData
{
    INT16U m_AdcError; //氧气源压力 单位pa
    INT16U m_SensorOff[7];
    INT16U m_AdArr[MAXCHLNUM];
} SYSSTATUSDATA, *PSYSSTATUSDATA;
//*********************************************************************************************************


//*********************************************************************************************************
//*****************************************    系统参数数据     *******************************************
//*********************************************************************************************************
// typedef struct SysParamData
// {
//   INT32S m_Vt; //总潮气量
// }SYSPARAMDATA,*PSYSPARAMDATA;
//*********************************************************************************************************

//*********************************************************************************************************
//*****************************************    系统数据     *******************************************
//*********************************************************************************************************

typedef enum
{
    check = 0,
    Stop,
    Cooler,
    Heater,
}	eSystemStatus;

typedef enum
{
    Status_Off = 0, //2017-5-22tommy 修正，原来是On = 1，Off=2,现在修正on=1，off=0；
    Status_On = 1,
}	eStatus;

typedef enum
{
    Status_I = 0,
    Status_II,
    Status_III,
}	eNoStatus;


typedef enum
{
    NoAlm = BIT1,
    Temp1Alm = BIT2,
    Temp2Alm = BIT3,
    WaterTemp = BIT4,
    WaterStatus = BIT5,
    ConfigErr = BIT6,
}	eSystemAlm;

typedef enum
{
    NoFocus = 0,
    Temp1Focus,
    Temp2Focus,
    TempWFocus,
    AlmVolumFocus,
    Cal1Focus,
    Cal2Focus,
}	eFocusStatus;

typedef enum
{
    NoBeep = 0,
    BeepON,
    AlmBeep1,
    AlmBeep2,
}	eAlmType;

#define ALM_LEVEL_LOW 1
#define ALM_LEVEL_MID 2
#define ALM_LEVEL_HIG 3

typedef struct ConfigData
{
    PSYSSTATUSDATA pStatus;
    ///////////////////////系统状态数据，开机初始化即可/////////////////////////
    eFocusStatus m_FocusStatus; //焦点状态  0-无焦点 1-6焦点
    eStatus m_SingleMode;
    eStatus m_Bump1Status; //水泵1状态
    eStatus m_Bump2Status; //水泵2状态
    INT16U m_Temp1;	//体温1 温度x1000 35551=35.551度
    INT16U m_Temp2;	//体温2 温度x1000 35551=35.551度
    INT16U m_WaterTemp; //水温 温度x100 3555=35.55度
    eNoStatus m_WaterStatus; //水位I,II,III
    eStatus m_Cooler; //制冷状态
    eStatus m_Heater; //制热状态
    eSystemAlm m_SystemAlm; //系统报警状态
    eSystemStatus m_SystemSta;//系统工作状态
    eStatus m_Cycle1Set;	//水路1状态
    eStatus m_Cycle2Set;	//水路2状态
    INT16U m_AlmVolSet; 	//报警音量显示值

    ///////////////////////系统配置数据，开机从E2PROM读取即可/////////////////////////
    INT16U m_Temp1Set;	  //体温1设置值 温度X10 步进0.5度 35.5度=355
    INT16U m_Temp2Set;	  //体温2设置值 温度X10 步进0.5度 35.5度=355
    INT16U m_WaterTempSet; //水温设置值 温度 步进1度 35度=35
    INT16U m_AlmVolum;		//报警音量设置值
    INT8S m_Cal1Set;	  //体温1校准值 步进0.1度
    INT8S m_Cal2Set;	  //体温2校准值 步进0.1度

    //报警信息
    eStatus m_Sensor1OFF; //传感器脱落 Status_On-脱落
    eStatus m_Sensor2OFF; //传感器脱落 Status_On-脱落
    eStatus m_HeaterPOWER; //加热器异常 Status_On-触发
    eStatus m_WaterHIGH; //水温超高温状态 Status_On-触发
    eStatus m_WaterTLow; //水温超低温状态 Status_On-触发
    eStatus m_E2PROMERR;//e2prom错误 Status_On-触发
    eStatus m_WaterLow;//水位低状态 Status_On-触发
    eStatus m_HeaterModeWT1Low; //加热模式下，设定水温低于体温1 Status_On-触发
    eStatus m_HeaterModeWT2Low; //加热模式下，设定水温低于体温2 Status_On-触发
    eStatus m_HeaterModeT1ALM; //加热模式下，体温1超限报警
    eStatus m_HeaterModeT2ALM; //加热模式下，体温2超限报警
    eStatus	m_Cycle1Alm; //液路1故障
    eStatus	m_Cycle2Alm;//液路2故障
} CONFIGDATA, *PCONFIGDATA;
//*********************************************************************************************************


typedef struct ModuleBase //基类接口 //改返回接口
{
    //功能模块名
    char m_ModName[16];
    //初始化 输入m_pBaseData
    BOOLEAN (*pModeleInit)(void* pArg);
    //复位 输入m_pBaseData
    BOOLEAN (*pModeleReset)(void* pArg);
    //开始 输入m_pBaseData
    BOOLEAN (*pModeleStart)(void* pArg);
    //停止 输入m_pBaseData
    BOOLEAN (*pModeleStop)(void* pArg);
    //释放 输入m_pBaseData
    BOOLEAN (*pModeleRelease)(void* pArg);
    //消息处理 主任务
    void (*pMsgNotify)(PVOID pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);
    //10ms调度任务
    void (*pModele10msProcess)(void* pArg);
    //50ms调度任务
    void (*pModele50msProcess)(void* pArg);
    //1s调度任务
    void (*pModele1sProcess)(void* pArg);
    //1ms调度任务
    void (*pModele1msProcess)(void* pArg);
    //模块数据指针
    PVOID m_pBaseData;
} MODULEBASE, *PMODULEBASE;

//*********************************************************************************************************
//*****************************************   工作模块     *******************************************
//*********************************************************************************************************
typedef struct ModeObjData //配置类数据结构
{
    P_MSGQUEUE m_pMsgQueue;  //消息队列
    PCONFIGDATA m_pSysData;
    eWorkMode m_Id;
    BOOLEAN m_PressSta; //处理调用状态记录
    INT16U m_Count; //计时器 单位10ms
//    ePhaseStatus m_Phase;
    BOOLEAN m_ConfigFlag;
//************************以下增加模块内部使用的变量或者其它元素******************************//
} MODEOBJDATA, *PMODEOBJDATA;

typedef struct ModeObj //基类接口 //改返回接口
{
    BOOLEAN (*pModeInit)(PVOID Self);
    BOOLEAN (*pModeStart)(PVOID Self);
    BOOLEAN (*pModeReset)(PVOID Self);
    BOOLEAN (*pModeStop)(PVOID Self);
    BOOLEAN (*pModeRelease)(PVOID Self);
    void (*pMsgNotify)(PVOID Self, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);
    void (*pMode10msProcess)(PVOID Self);
    void (*pMode50msProcess)(PVOID Self);
    void (*pMode1sProcess)(PVOID Self);
    PVOID m_pBaseData;
    /******************各模式具体实现*************************/
} MODEOBJ, *PMODEOBJ;

//*********************************************************************************************************
//*****************************************    全局数据     *******************************************
//*********************************************************************************************************
typedef struct GlobalData
{
    PMODULEBASE pServer;
//    P_MSGQUEUE g_pMsgQueue;
} GLOBALDATA, *PGLOBALDATA;
//*********************************************************************************************************

typedef struct ModuleServerData //主服务器数据结构
{
    PCONFIGDATA m_pSysData;     //系统数据
    P_MSGQUEUE m_pMsgQueue;  //消息队列
    DLLIST* m_pSubMouleList; //子模块链表
    BOOLEAN m_PressSta; //处理调用状态记录
} MODULESERVERDATA, *PMODULESERVERDATA;

#endif
