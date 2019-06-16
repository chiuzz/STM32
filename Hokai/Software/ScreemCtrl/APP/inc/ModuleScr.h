//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* 文 件 名 : ModuleScr.h
//*
//* 文件描述 : 主服务任务文件
//*
//* 作    者 : LGL
//* 版    本 :
//* 编 译 器 : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MODULE_SCR_H__
#define  __MODULE_SCR_H__

#include "common.h"
#include "struct_def.h"

#define Temp1_ADDRESS 4
#define WaterTemp_ADDRESS 5
#define Temp2_ADDRESS 6
#define Temp1Set_ADDRESS    1	 //设置体温1的地址
#define Temp2Set_ADDRESS     3	//设置体温2的地址
#define WaterTempSet_ADDRESS   2 //水温设置的地址
#define IC_PIN 23    //显示屏的通道数量

#define TempSet1CH_PIN_ADDR 0 // 体温1设置
#define WaterSetCH_PIN_ADDR 6 // 水温设置温度显示区域
#define TempSet2CH_PIN_ADDR 10 // 体温2设置
#define Temp1CH2_PIN_ADDR 0 // 体温1温度显示区域
#define TWaterCH2_PIN_ADDR 6 // 水温
#define Temp2CH2_PIN_ADDR 12 // 体温2

#define IC1_PIN   1          //显示屏的pin1
#define IC2_PIN   2         //显示屏的pin2
#define Screen_1_S0 	0
#define Screen_1_S1		1
#define Screen_1_S2		2
#define Screen_1_S3		3
#define Screen_1_S4		4
#define Screen_1_S5		5
#define Screen_1_S6		6
#define Screen_1_S7		7
#define Screen_1_S8		8
#define Screen_1_S9		9
#define Screen_1_S10		10
#define Screen_1_S11		11
#define Screen_1_S12		12
#define Screen_1_S13		13
#define Screen_1_S14		14
#define Screen_1_S15		15
#define Screen_1_S16		16
#define Screen_1_S17		17
#define Screen_1_S18		18
#define Screen_1_S19		19
#define Screen_1_S20		20
#define Screen_1_S21		21
#define Screen_1_S22		22
#define Screen_1_S23		23
#define Screen_1_S24		24
#define Screen_1_S25		25
#define Screen_1_S26		26
#define Screen_1_S27		27
#define Screen_1_S28		28
#define Screen_1_S29		29
#define Screen_1_S30		30
#define Screen_1_S31		31
#define Screen_1_S32		32
#define Screen_1_S33		33
#define Screen_1_S34		34
#define Screen_1_S35		35
#define MINUS						10
typedef struct
{
    INT8U COM1 : 1;         //
    INT8U COM2 : 1;         //
    INT8U COM3 : 1;         //
    INT8U COM4 : 1;         //
    INT8U P_WhichIC : 2;
    INT8U P_Addr  : 8;
} HTB_ICN; //定义其他

typedef enum
{
    SCR_STOP = 0,
    SCR_INIT,
    SCR_WORK,
}	eScrWorkStatus;

typedef enum
{
    Show = 0,
    Hide,
    Invalid,
    Flash,
}	eItemStatus;

typedef struct ModuleScrData //配置类数据结构
{
    P_MSGQUEUE m_pMsgQueue;  //消息队列
    INT16U m_Count; //计时器
    INT16U m_FlashCount;
    INT16U m_50msCount;

    BOOLEAN m_PressSta; //处理调用状态记录
    PCONFIGDATA m_pSysData;     //系统数据
//************************以下增加模块内部使用的变量或者其它元素******************************//
    eScrWorkStatus m_ScrWorkSta;
    HTB_ICN  IC1_S[IC_PIN]; //通道1
    HTB_ICN  IC2_S[IC_PIN];//通道2
    INT16U m_Temp1SetMark;
    INT16U m_Temp2SetMark;
    INT16U m_WaterTempSetMark;
    INT16S m_Cal1SetMark;
    INT16S m_Cal2SetMark;

} MODULESCRDATA, *PMODULESCRDATA;

typedef struct ModuleScr //服务器类
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
} MODULESCR, *PMODULESCR;
//*
//********************************************************************************************************
//* 函 数 名 : void CreateModuleScr(void)
//**------------------------------------------------------------------------------------------------------
//* 描    述 : 创建模块
//**------------------------------------------------------------------------------------------------------
//* 输入参数 : PMODULEBASE. 空指针
//**------------------------------------------------------------------------------------------------------
//* 输出参数 : PMODULEBASE. 申请内存空间后返回基类指针
//**------------------------------------------------------------------------------------------------------
//* 返   回  : PMODULESCRDATA.申请内存空间后返回基类数据指针
//********************************************************************************************************
//*
extern PMODULEBASE CreateModuleScr(PMODULESERVERDATA pServerData);

//************************内部处理函数实现******************************//
static BOOLEAN ModuleScrInit(void* pArg);
static BOOLEAN ModuleScrReset(void* pArg);
static BOOLEAN ModuleScrStart(void* pArg);
static BOOLEAN ModuleScrStop(void* pArg);
static BOOLEAN ModuleScrRelease(void* pArg);
static void ModuleScr50msProcess(void* pArg);
static void ScrMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);

//************************模块功能实现函数******************************//
void HTBICNSVal(HTB_ICN HTBRam); //显示屏区域
void HTBSegVal(HTB_ICN* H_Ram, HTB_ICN* L_Ram, INT16U SegData); //显示数
void ShowHT1621Temperature(INT16U TempCH, void* pArg); //显示体温信息为--
void WriteHT1621OneData(INT16U Addr, INT16U Data, INT16U WhichIC); //把数据送给驱动LCD.H
void ShowMinus(INT16U TempCH, void* pArg);
void SystemStaStop(void* pArg);//系统在停止状态下,显示屏信息
void DisplayTemp(void* pArg, INT16U Temp1, INT16U Temp2, INT16U WaterTemp );//显示温度设置的信息
void DisplayRefresh(void* pArg);//刷新区域
void HtbRamInit(void* pArg); //显示屏区域初始化
void TempShow(void* pArg, INT16U Temp1, INT16U Temp2, INT16U WaterTemp );//温度显示

void WaterStatusAlm(void* pArg);//水位报警
void WaterTempSetAlm(void* pArg);//水位报警


//************************内部处理函数实现******************************//
static void DisplayWorkMode(void* pArg,eSystemStatus Sta);
static void DisplayCoolerStatus(void* pArg, eStatus Cooler); //系统的工作模式
static void DisplayHeaterStatus(void* pArg, eItemStatus Item); //系统的工作模式
static void DisplayCycle1Mode(void* pArg, eStatus Cycle1); //系统在停止状态下,显示屏信息
static void DisplayCycle2Mode(void* pArg, eStatus Cycle2); //系统在停止状态下,显示屏信息
static void DisplayBump1Mode(void* pArg, eItemStatus Item); //系统在停止状态下,显示屏信息
static void DisplayBump2Mode(void* pArg, eItemStatus Item);//系统在停止状态下,显示屏信息
static void DisplayWaterStatusI(void* pArg);//水位状态
static void DisplayWaterStatusII(void* pArg);//水位状态
static void DisplayWaterStatusIII(void* pArg);//水位状态
static void DisplayCal1Set(void* pArg, eItemStatus Item, INT16S Cal1Set);
static void DisplayCal2Set(void* pArg, eItemStatus Item, INT16S Cal2Set);
static void DisplayTemp1Set(void* pArg, eItemStatus Item, INT16U Temp1Set); //温度设置
static void DisplayTemp2Set(void* pArg, eItemStatus Item, INT16U Temp2Set); //温度设置
static void DisplayWaterTempSet(void* pArg, eItemStatus Item, INT16U WaterTempSet); //温度设置
static void DisplayTemp1Val(void* pArg, eItemStatus Item, INT16U Temp);
static void DisplayTemp2Val(void* pArg, eItemStatus Item, INT16U Temp);
static void DisplayWaterTempVal(void* pArg, eItemStatus Item, INT16U Temp);
#endif
