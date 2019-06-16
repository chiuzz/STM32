//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* 文 件 名 : ModuleConfig.h
//*
//* 文件描述 : 主服务任务文件
//*
//* 作    者 : LGL
//* 版    本 :
//* 编 译 器 : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MODULE_CONFIG_H__
#define  __MODULE_CONFIG_H__

#include "common.h"
#include "struct_def.h"

typedef enum
{
    CONFIG_STOP = 0,
		CONFIG_INIT,
		CONFIG_SAVE_START,
		CALC_SAVE_START,
		ADJ_SAVE_START,
		CONFIG_CFG_SAVE,
}	eConfigMachine;

typedef struct ModuleConfigData //配置类数据结构
{
    P_MSGQUEUE m_pMsgQueue;  //消息队列
    INT16U m_Count; //计时器
    BOOLEAN m_PressSta; //处理调用状态记录
//************************以下增加模块内部使用的变量或者其它元素******************************//
    PSYSPARAMDATA m_pSysData;
		PSYSCONFIGDATA m_pCfgData; //全局变量
		PSYSCALCDATA m_pCalData; //全局变量
		PSYSADJDATA m_pAdjData;
		INT16U m_Temp;
		eConfigMachine m_ConfigMac;
		BOOLEAN m_ConfigEffective;
		BOOLEAN m_ConfigSaveable;
} MODULECONFIGDATA,*PMODULECONFIGDATA;

typedef struct ModuleConfig //服务器类
{
    char m_ModName[16];
    BOOLEAN (*pModeleInit)(void* pArg); //初始化 输入m_pBaseData
    BOOLEAN (*pModeleReset)(void* pArg); //复位 输入m_pBaseData
    BOOLEAN (*pModeleStart)(void* pArg); //开始 输入m_pBaseData
    BOOLEAN (*pModeleStop)(void* pArg); //停止 输入m_pBaseData
    BOOLEAN (*pModeleRelease)(void* pArg); //释放 输入m_pBaseData
    void (*pMsgNotify)(PVOID pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf); //消息处理 主任务
    void (*pModele1msProcess)(void* pArg); //1ms调度任务
    void (*pModele10msProcess)(void* pArg); //10ms调度任务
    void (*pModele50msProcess)(void* pArg); //50ms调度任务
    void (*pModele1sProcess)(void* pArg);  //1s调度任务
    void (*pModeleUartProcess)(void* pArg);  //1s调度任务
    PVOID m_pBaseData;
} MODULECONFIG,*PMODULECONFIG;
//*
//********************************************************************************************************
//* 函 数 名 : void CreateModuleConfig(void)
//**------------------------------------------------------------------------------------------------------
//* 描    述 : 创建模块
//**------------------------------------------------------------------------------------------------------
//* 输入参数 : PMODULEBASE. 空指针
//**------------------------------------------------------------------------------------------------------
//* 输出参数 : PMODULEBASE. 申请内存空间后返回基类指针
//**------------------------------------------------------------------------------------------------------
//* 返   回  : PMODULECONFIGDATA.申请内存空间后返回基类数据指针
//********************************************************************************************************
//*
extern PMODULEBASE CreateModuleConfig(PMODULESERVERDATA pServerData);

//************************内部处理函数实现******************************//
static BOOLEAN ModuleConfigInit(void* pArg);
static BOOLEAN ModuleConfigReset(void* pArg);
static BOOLEAN ModuleConfigStart(void* pArg);
static BOOLEAN ModuleConfigStop(void* pArg);
static BOOLEAN ModuleConfigRelease(void* pArg);
static void ModuleConfig1sProcess(void* pArg);
static void ConfigMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);

//************************模块功能实现函数******************************//
void  ReadMemConfig(PMODULECONFIGDATA pData);   //读取数据
void  ReadMemCalc(PMODULECONFIGDATA pData);   //读取数据
void  ReadMemAdj(PMODULECONFIGDATA pData);   //读取数据
void  WriteMemConfig(PMODULECONFIGDATA pData); //写入数据
void  WriteMemCalc(PMODULECONFIGDATA pData); //写入数据
void  WriteMemAdj(PMODULECONFIGDATA pData); //写入数据
//************************内部处理函数实现******************************//
static void I2CMemSave(INT16U Addres, PVOID pObj, INT16U len);
static void I2CMemLoad(INT16U Addres, PVOID pObj, INT16U len);

static BOOLEAN TestE2PROM(INT16U D);
static BOOLEAN ChackCalcData(PMODULECONFIGDATA pData);
static BOOLEAN ChackConfigData(PMODULECONFIGDATA pData);
static BOOLEAN ChackAdjData(PMODULECONFIGDATA pData);
static void CalceDataInit(PMODULECONFIGDATA pData);
static void ConfigDataInit(PMODULECONFIGDATA pData);
static void AdjDataInit(PMODULECONFIGDATA pData);
static void ConfigMachineProc(void* pArg);
//***************************???????****************************//
#define ADDRESS_BASE     0x0
#define DATASIZE sizeof(INT16U)
///////////////体温1配置地址///////////////////
#define ADDRESS_TEMP1SET_START (ADDRESS_BASE)
#define ADDRESS_TEMP1SET_END (ADDRESS_TEMP1SET_START + DATASIZE)
///////////////体温2配置地址///////////////////
#define ADDRESS_TEMP2SET_START (ADDRESS_TEMP1SET_END)
#define ADDRESS_TEMP2SET_END (ADDRESS_TEMP2SET_START + DATASIZE)
///////////////水温2配置地址///////////////////
#define ADDRESS_TEMPWATERSET_START (ADDRESS_TEMP2SET_END)
#define ADDRESS_TEMPWATERSET_END (ADDRESS_TEMPWATERSET_START + DATASIZE)
///////////////CH1AD校准配置地址///////////////////
#define ADDRESS_CH1ADARR_START (ADDRESS_TEMPWATERSET_END)
#define ADDRESS_CH1ADARR_END (ADDRESS_CH1ADARR_START + DATASIZE*ADCALCDATANUM)
#define ADDRESS_CH1TEMPARR_START (ADDRESS_CH1ADARR_END)
#define ADDRESS_CH1TEMPARR_END (ADDRESS_CH1TEMPARR_START + DATASIZE*ADCALCDATANUM)
///////////////CH2AD校准配置地址///////////////////
#define ADDRESS_CH2ADARR_START (ADDRESS_CH1TEMPARR_END)
#define ADDRESS_CH2ADARR_END (ADDRESS_CH2ADARR_START + DATASIZE*ADCALCDATANUM)
#define ADDRESS_CH2TEMPARR_START (ADDRESS_CH2ADARR_END)
#define ADDRESS_CH2TEMPARR_END (ADDRESS_CH2TEMPARR_START + DATASIZE*ADCALCDATANUM)
///////////////CH3AD校准配置地址///////////////////
#define ADDRESS_CH3ADARR_START (ADDRESS_CH2TEMPARR_END)
#define ADDRESS_CH3ADARR_END (ADDRESS_CH3ADARR_START + DATASIZE*ADCALCDATANUM)
#define ADDRESS_CH3TEMPARR_START (ADDRESS_CH3ADARR_END)
#define ADDRESS_CH3TEMPARR_END (ADDRESS_CH3TEMPARR_START + DATASIZE*ADCALCDATANUM)
///////////////sen1AD校准配置地址///////////////////
#define ADDRESS_SEN1ADARR_START (ADDRESS_CH3TEMPARR_END)
#define ADDRESS_SEN1ADARR_END (ADDRESS_SEN1ADARR_START + DATASIZE*SENCALCDATANUM)
#define ADDRESS_SEN1TEMPARR_START (ADDRESS_SEN1ADARR_END)
#define ADDRESS_SEN1TEMPARR_END (ADDRESS_SEN1TEMPARR_START + DATASIZE*SENCALCDATANUM)
///////////////sen2AD校准配置地址///////////////////
#define ADDRESS_SEN2ADARR_START (ADDRESS_SEN1TEMPARR_END)
#define ADDRESS_SEN2ADARR_END (ADDRESS_SEN2ADARR_START + DATASIZE*SENCALCDATANUM)
#define ADDRESS_SEN2TEMPARR_START (ADDRESS_SEN2ADARR_END)
#define ADDRESS_SEN2TEMPARR_END (ADDRESS_SEN2TEMPARR_START + DATASIZE*SENCALCDATANUM)
///制热模式下的体温设置,水温设置
///////////////体温1配置地址///////////////////
#define ADDRESS_HOT_TEMP1SET_START (ADDRESS_SEN2TEMPARR_END)
#define ADDRESS_HOT_TEMP1SET_END (ADDRESS_HOT_TEMP1SET_START + DATASIZE)
///////////////体温2配置地址///////////////////
#define ADDRESS_HOT_TEMP2SET_START (ADDRESS_HOT_TEMP1SET_END)
#define ADDRESS_HOT_TEMP2SET_END (ADDRESS_HOT_TEMP2SET_START + DATASIZE)
///////////////水温2配置地址///////////////////
#define ADDRESS_HOT_TEMPWATERSET_START (ADDRESS_HOT_TEMP2SET_END)
#define ADDRESS_HOT_TEMPWATERSET_END (ADDRESS_HOT_TEMPWATERSET_START + DATASIZE)

///制冷模式下
///////////////体温1配置地址///////////////////
#define ADDRESS_COOL_TEMP1SET_START (ADDRESS_HOT_TEMPWATERSET_END)
#define ADDRESS_COOL_TEMP1SET_END (ADDRESS_COOL_TEMP1SET_START + DATASIZE)
///////////////体温2配置地址///////////////////
#define ADDRESS_COOL_TEMP2SET_START (ADDRESS_COOL_TEMP1SET_END)
#define ADDRESS_COOL_TEMP2SET_END (ADDRESS_COOL_TEMP2SET_START + DATASIZE)
///////////////水温2配置地址///////////////////
#define ADDRESS_COOL_TEMPWATERSET_START (ADDRESS_COOL_TEMP2SET_END)
#define ADDRESS_COOL_TEMPWATERSET_END (ADDRESS_COOL_TEMPWATERSET_START + DATASIZE)
//记录是单毯模式,还是双毯模式singleMode
#define ADDRESS_SINGLEMODE_START (ADDRESS_COOL_TEMPWATERSET_END)
#define ADDRESS_SINGLEMODE_END (ADDRESS_SINGLEMODE_START + DATASIZE)

#define ADDRESS_SYSWORKMODE_START (ADDRESS_SINGLEMODE_END)
#define ADDRESS_SYSWORKMODE_END (ADDRESS_SYSWORKMODE_START + DATASIZE)

#define ADDRESS_CYCLE1SET_START (ADDRESS_SYSWORKMODE_END)
#define ADDRESS_CYCLE1SET_END (ADDRESS_CYCLE1SET_START + DATASIZE)

#define ADDRESS_CYCLE2SET_START (ADDRESS_CYCLE1SET_END)
#define ADDRESS_CYCLE2SET_END (ADDRESS_CYCLE2SET_START + DATASIZE)

#define ADDRESS_ALMVOL_START (ADDRESS_CYCLE2SET_END)
#define ADDRESS_ALMVOL_END (ADDRESS_ALMVOL_START + DATASIZE)
///////////////体温1校准配置地址////////////////
#define ADDRESS_CAL1SET_START (ADDRESS_ALMVOL_END)
#define ADDRESS_CAL1SET_END (ADDRESS_CAL1SET_START + DATASIZE)
///////////////体温2校准配置地址////////////////
#define ADDRESS_CAL2SET_START (ADDRESS_CAL1SET_END)
#define ADDRESS_CAL2SET_END (ADDRESS_CAL2SET_START + DATASIZE)

#define ADDRESS_END     ADDRESS_CAL2SET_END
#endif
