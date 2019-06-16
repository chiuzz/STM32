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

#include "common.h"

#define INVALID_8BIT_VOL 0xff
#define INVALID_16BIT_VOL 0xffff

//typedef struct Struct
//{}STRUCT,*PSTRUCT;
//typedef enum {FALSE = 0, TRUE = !FALSE} bool;

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
    NoFocus = 0,
    Temp1Focus,//体温设置1
    Temp2Focus,//水温设置
    TempWFocus,//体温设置2
    AlmVolFocus,//报警音量设置
    Cal1Focus,//体温校准设置1
    Cal2Focus,//体温校准设置2
}	eFocusStatus;

#define ADCALCDATANUM 2
#define SENCALCDATANUM 5
//*********************************************************************************************************
typedef struct SysParamData
{
    //状态信息
    eStatus m_Float1Status;	//水路水流开关1状态
    eStatus m_Float2Status;	//水路水流开关2状态
    eNoStatus m_WaterStatus; //水位I,II,III
    eStatus m_Bump1Status; //水泵1状态
    eStatus m_Bump2Status; //水泵2状态
    eStatus m_Cooler; //制冷状态
    eStatus m_Heater; //制热状态
    eFocusStatus m_FocusStatus; //焦点状态  0-无焦点 1-6焦点

    //报警信息
    eStatus m_Sensor1OFF; //传感器脱落 Status_On-脱落
    eStatus m_Sensor2OFF; //传感器脱落 Status_On-脱落
    eStatus m_HeaterPOWER; //加热器异常 Status_On-触发
    eStatus m_WaterHIGH; //水温超高温状态 Status_On-触发
    eStatus m_WaterTLow; //水温超低温状态 Status_On-触发
    eStatus m_E2PROMERR;//e2prom错误 Status_On-触发
    eStatus m_WaterLow;//水位低状态 Status_On-触发
    eStatus m_HeaterModeWT1Low; //加热模式下，设定水温低于体温 Status_On-触发
    eStatus m_HeaterModeWT2Low; //加热模式下，设定水温低于体温 Status_On-触发
    eStatus m_HeaterModeT1ALM; //加热模式下，体温1超限报警
    eStatus m_HeaterModeT2ALM; //加热模式下，体温2超限报警
    eStatus	m_Cycle1Alm; //液路1故障
    eStatus	m_Cycle2Alm;//液路2故障
    //数据信息
    INT16U m_Temp1;	//体温1 温度x1000 35551=35.551度
    INT16U m_Temp2;	//体温2 温度x1000 35551=35.551度
    INT16U m_WaterTemp; //水温 温度x100 3555=35.55度
    //设定数据信息
    INT16U m_Temp1Set;	  //体温1设置值 温度X10 步进0.5度 35.5度=355
    INT16U m_Temp2Set;	  //体温2设置值 温度X10 步进0.5度 35.5度=355
    INT16U m_WaterTempSet; //水温设置值 温度 步进1度 35度=35
    INT16U m_AlmVolSet; 	//音量设置值 步进1
    INT8S	 m_Cal1Set;			//水温1校准值
    INT8S	 m_Cal2Set;			//水温2校准值

//	INT16U m_SystemAlm; //系统报警状态

    /////////////////硬件校准计算值，开机从配置数据计算后获取/////////////////////
    FP32 m_AD1CalcK; //AD1校准值
    FP32 m_AD1CalcB; //AD1校准值
    FP32 m_AD2CalcK; //AD1校准值
    FP32 m_AD2CalcB; //AD1校准值
    FP32 m_AD3CalcK; //AD1校准值
    FP32 m_AD3CalcB; //AD1校准值

    //////保存1单毯模式,还是双毯模式0,

} SYSPARAMDATA,*PSYSPARAMDATA;

#define ALM_LEVEL_LOW 1
#define ALM_LEVEL_MID 2
#define ALM_LEVEL_HIG 3
#define TEMPCALMAX		10			//体温校准最大值
#define TEMPCALMIN		-10			//体温校准最小值

typedef struct SysConfigData
{
    ///////////////////////系统状态数据，开机初始化即可/////////////////////////
    eSystemStatus m_SystemSta;//系统工作状态
    eStatus m_Cycle1Set;	//水路1状态
    eStatus m_Cycle2Set;	//水路2状态
    ///////////////////////系统配置数据，开机从E2PROM读取/////////////////////////
    INT16U m_Temp1Set_Hot;	  //体温1设置值 温度X10 步进0.5度 35.5度=355
    INT16U m_Temp2Set_Hot;	  //体温2设置值 温度X10 步进0.5度 35.5度=355
    INT16U m_WaterTempSet_Hot; //水温设置值 温度 步进1度 35度=35
    INT16U m_Temp1Set_Cool;	  //体温1设置值 温度X10 步进0.5度 35.5度=355
    INT16U m_Temp2Set_Cool;	  //体温2设置值 温度X10 步进0.5度 35.5度=355
    INT16U m_WaterTempSet_Cool; //水温设置值 温度 步进1度 35度=35
    INT16U m_AlmVolum;
} SYSCONFIGDATA,*PSYSCONFIGDATA;

typedef struct SysCalcData
{
    /////////////////硬件校准值，开机从E2PROM读取/////////////////////
    INT16U m_CH1ADArr[ADCALCDATANUM];
    INT16U m_CH1TEMPArr[ADCALCDATANUM];
    INT16U m_CH2ADArr[ADCALCDATANUM];
    INT16U m_CH2TEMPArr[ADCALCDATANUM];
    INT16U m_CH3ADArr[ADCALCDATANUM];
    INT16U m_CH3TEMPArr[ADCALCDATANUM];
    eStatus m_SingleMode; //TRUE-触发单毯模式
} SYSCALCDATA,*PSYSCALCDATA;

typedef struct SysAdjData
{
    /////////////////软件校准值，开机从E2PROM读取/////////////////////
    INT8S m_Cal1Set;	//体温1校准值
    INT8S m_Cal2Set;	//体温2校准值
} SYSADJDATA,*PSYSADJDATA;

typedef struct MsgItem  //消息链表元素
{
//    PVOID pArg;
    INT8U MsgId;
    INT16U lParam;
    INT16U wParam;
    void* pBuf;
} MSGITEM,*PMSGITEM;


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
    //1ms调度任务
    void (*pModele1msProcess)(void* pArg);
    //10ms调度任务
    void (*pModele10msProcess)(void* pArg);
    //50ms调度任务
    void (*pModele50msProcess)(void* pArg);
    //1s调度任务
    void (*pModele1sProcess)(void* pArg);
    //UART调度任务
    void (*pModeleUartProcess)(void* pArg);
    //模块数据指针
    PVOID m_pBaseData;
} MODULEBASE,*PMODULEBASE;

//*********************************************************************************************************
//*****************************************    全局数据     *******************************************
//*********************************************************************************************************
typedef struct GlobalData
{
    PMODULEBASE pServer;
    //P_MSGQUEUE g_pMsgQueue;
} GLOBALDATA,*PGLOBALDATA;
//*********************************************************************************************************

typedef struct ModuleServerData //主服务器数据结构
{
    PSYSPARAMDATA m_pSysData; //系统数据
    PSYSCONFIGDATA m_pCfgData; //系统数据
    PSYSCALCDATA m_pCalData; //系统数据
    PSYSADJDATA	m_pAdjData;
    P_MSGQUEUE m_pMsgQueue;  //消息队列
    DLLIST* m_pSubMouleList; //子模块链表
    BOOLEAN m_PressSta; //处理调用状态记录
} MODULESERVERDATA,*PMODULESERVERDATA;

typedef enum
{
    MacStart=1,
    SendStep1,
    ChkStep1,
    SendStep2,
    ChkStep2,
    SendStep3,
    ChkStep3,
    SendStep4,
    ChkStep4,
    SendStep5,
    ChkStep5,
    MacStop,
} eMachineSta;

#define USART_MSG 1
#define USART_STA 2
#define USART_NUL 0
#define _DIFFERENCE_WATER     1  //水温的精度 
#define _DIFFERENCE_BODY     10   //设置体温与实际体温的差异
#define TEMP_ALARM  2800   //报警体温
#define TEMP_ALARMHIGH 4300
#define ADDR_AD1CalcK    10//ad1的k值 地址
#define ADDR_AD1CalcB    20//ad1的b值地址
#define ADDR_AD2CalcK    30 //ad2 的k值地址
#define ADDR_AD2CalcB    40  //ad2的b值地址
#define ADDR_Temp1Set    50	 //设置体温1的地址
#define ADDR_Temp2Set    60	//设置体温2的地址
#define ADDR_WaterTempSet  70 //水温设置的地址
#endif
