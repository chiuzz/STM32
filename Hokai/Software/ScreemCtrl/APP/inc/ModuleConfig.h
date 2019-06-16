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
    E2PROM_SAVE,
    E2PROM_LOAD
} eConfigProc;

//***************************定义保存的地址****************************//
#define ADDRESS_BASE     0x0
#define DATASIZE sizeof(INT16U)
#define ADDRESS_VREF_START (ADDRESS_BASE)
#define ADDRESS_VREF_END (ADDRESS_VREF_START + DATASIZE)
#define ADDRESS_CALCNUM_START (ADDRESS_VREF_END)
#define ADDRESS_CALCNUM_END (ADDRESS_CALCNUM_START + DATASIZE)
#define ADDRESS_MODE_START (ADDRESS_CALCNUM_END)
#define ADDRESS_MODE_END (ADDRESS_MODE_START + DATASIZE)

#define LEN_CALCDATA DATASIZE*TEMPCALDATANUM
#define ADDRESS_CH0AD_START (ADDRESS_MODE_END)
#define ADDRESS_CH0AD_END (ADDRESS_CH0AD_START + LEN_CALCDATA)
#define ADDRESS_CH1AD_START (ADDRESS_CH0AD_END)
#define ADDRESS_CH1AD_END (ADDRESS_CH1AD_START + LEN_CALCDATA)
#define ADDRESS_CH2AD_START (ADDRESS_CH1AD_END)
#define ADDRESS_CH2AD_END (ADDRESS_CH2AD_START + LEN_CALCDATA)
#define ADDRESS_CH3AD_START (ADDRESS_CH2AD_END)
#define ADDRESS_CH3AD_END (ADDRESS_CH3AD_START + LEN_CALCDATA)
#define ADDRESS_CH4AD_START (ADDRESS_CH3AD_END)
#define ADDRESS_CH4AD_END (ADDRESS_CH4AD_START + LEN_CALCDATA)
#define ADDRESS_CH5AD_START (ADDRESS_CH4AD_END)
#define ADDRESS_CH5AD_END (ADDRESS_CH5AD_START + LEN_CALCDATA)
#define ADDRESS_CH6AD_START (ADDRESS_CH5AD_END)
#define ADDRESS_CH6AD_END (ADDRESS_CH6AD_START + LEN_CALCDATA)

#define ADDRESS_CH0TEMP_START (ADDRESS_CH6AD_END)
#define ADDRESS_CH0TEMP_END (ADDRESS_CH0TEMP_START + LEN_CALCDATA)
#define ADDRESS_CH1TEMP_START (ADDRESS_CH0TEMP_END)
#define ADDRESS_CH1TEMP_END (ADDRESS_CH1TEMP_START + LEN_CALCDATA)
#define ADDRESS_CH2TEMP_START (ADDRESS_CH1TEMP_END)
#define ADDRESS_CH2TEMP_END (ADDRESS_CH2TEMP_START + LEN_CALCDATA)
#define ADDRESS_CH3TEMP_START (ADDRESS_CH2TEMP_END)
#define ADDRESS_CH3TEMP_END (ADDRESS_CH3TEMP_START + LEN_CALCDATA)
#define ADDRESS_CH4TEMP_START (ADDRESS_CH3TEMP_END)
#define ADDRESS_CH4TEMP_END (ADDRESS_CH4TEMP_START + LEN_CALCDATA)
#define ADDRESS_CH5TEMP_START (ADDRESS_CH4TEMP_END)
#define ADDRESS_CH5TEMP_END (ADDRESS_CH5TEMP_START + LEN_CALCDATA)
#define ADDRESS_CH6TEMP_START (ADDRESS_CH5TEMP_END)
#define ADDRESS_CH6TEMP_END (ADDRESS_CH6TEMP_START + LEN_CALCDATA)

//#define LEN_CALCDATA_T DATASIZE*TEMPCALDATANUM_TWO
//#define ADDRESS_CH0AD_T_START (ADDRESS_CH6TEMP_END)
//#define ADDRESS_CH0AD_T_END (ADDRESS_CH0AD_T_START + LEN_CALCDATA_T)
//#define ADDRESS_CH1AD_T_START (ADDRESS_CH0AD_T_END)
//#define ADDRESS_CH1AD_T_END (ADDRESS_CH1AD_T_START + LEN_CALCDATA_T)
//#define ADDRESS_CH2AD_T_START (ADDRESS_CH1AD_T_END)
//#define ADDRESS_CH2AD_T_END (ADDRESS_CH2AD_T_START + LEN_CALCDATA_T)
//#define ADDRESS_CH3AD_T_START (ADDRESS_CH2AD_T_END)
//#define ADDRESS_CH3AD_T_END (ADDRESS_CH3AD_T_START + LEN_CALCDATA_T)
//#define ADDRESS_CH4AD_T_START (ADDRESS_CH3AD_T_END)
//#define ADDRESS_CH4AD_T_END (ADDRESS_CH4AD_T_START + LEN_CALCDATA_T)
//#define ADDRESS_CH5AD_T_START (ADDRESS_CH4AD_T_END)
//#define ADDRESS_CH5AD_T_END (ADDRESS_CH5AD_T_START + LEN_CALCDATA_T)
//#define ADDRESS_CH6AD_T_START (ADDRESS_CH5AD_T_END)
//#define ADDRESS_CH6AD_T_END (ADDRESS_CH6AD_T_START + LEN_CALCDATA_T)

//#define ADDRESS_CH0TEMP_T_START (ADDRESS_CH6AD_T_END)
//#define ADDRESS_CH0TEMP_T_END (ADDRESS_CH0TEMP_T_START + LEN_CALCDATA_T)
//#define ADDRESS_CH1TEMP_T_START (ADDRESS_CH0TEMP_T_END)
//#define ADDRESS_CH1TEMP_T_END (ADDRESS_CH1TEMP_T_START + LEN_CALCDATA_T)
//#define ADDRESS_CH2TEMP_T_START (ADDRESS_CH1TEMP_T_END)
//#define ADDRESS_CH2TEMP_T_END (ADDRESS_CH2TEMP_T_START + LEN_CALCDATA_T)
//#define ADDRESS_CH3TEMP_T_START (ADDRESS_CH2TEMP_T_END)
//#define ADDRESS_CH3TEMP_T_END (ADDRESS_CH3TEMP_T_START + LEN_CALCDATA_T)
//#define ADDRESS_CH4TEMP_T_START (ADDRESS_CH3TEMP_T_END)
//#define ADDRESS_CH4TEMP_T_END (ADDRESS_CH4TEMP_T_START + LEN_CALCDATA_T)
//#define ADDRESS_CH5TEMP_T_START (ADDRESS_CH4TEMP_T_END)
//#define ADDRESS_CH5TEMP_T_END (ADDRESS_CH5TEMP_T_START + LEN_CALCDATA_T)
//#define ADDRESS_CH6TEMP_T_START (ADDRESS_CH5TEMP_T_END)
//#define ADDRESS_CH6TEMP_T_END (ADDRESS_CH6TEMP_T_START + LEN_CALCDATA_T)

#define LEN_CALCDATA_E DATASIZE*TEMPCALDATANUM_THE
#define ADDRESS_CH0AD_E_START (ADDRESS_CH6TEMP_END)
#define ADDRESS_CH0AD_E_END (ADDRESS_CH0AD_E_START + LEN_CALCDATA_E)
#define ADDRESS_CH1AD_E_START (ADDRESS_CH0AD_E_END)
#define ADDRESS_CH1AD_E_END (ADDRESS_CH1AD_E_START + LEN_CALCDATA_E)
#define ADDRESS_CH2AD_E_START (ADDRESS_CH1AD_E_END)
#define ADDRESS_CH2AD_E_END (ADDRESS_CH2AD_E_START + LEN_CALCDATA_E)
#define ADDRESS_CH3AD_E_START (ADDRESS_CH2AD_E_END)
#define ADDRESS_CH3AD_E_END (ADDRESS_CH3AD_E_START + LEN_CALCDATA_E)
#define ADDRESS_CH4AD_E_START (ADDRESS_CH3AD_E_END)
#define ADDRESS_CH4AD_E_END (ADDRESS_CH4AD_E_START + LEN_CALCDATA_E)
#define ADDRESS_CH5AD_E_START (ADDRESS_CH4AD_E_END)
#define ADDRESS_CH5AD_E_END (ADDRESS_CH5AD_E_START + LEN_CALCDATA_E)
#define ADDRESS_CH6AD_E_START (ADDRESS_CH5AD_E_END)
#define ADDRESS_CH6AD_E_END (ADDRESS_CH6AD_E_START + LEN_CALCDATA_E)

#define ADDRESS_CH0TEMP_E_START (ADDRESS_CH6AD_E_END)
#define ADDRESS_CH0TEMP_E_END (ADDRESS_CH0TEMP_E_START + LEN_CALCDATA_E)
#define ADDRESS_CH1TEMP_E_START (ADDRESS_CH0TEMP_E_END)
#define ADDRESS_CH1TEMP_E_END (ADDRESS_CH1TEMP_E_START + LEN_CALCDATA_E)
#define ADDRESS_CH2TEMP_E_START (ADDRESS_CH1TEMP_E_END)
#define ADDRESS_CH2TEMP_E_END (ADDRESS_CH2TEMP_E_START + LEN_CALCDATA_E)
#define ADDRESS_CH3TEMP_E_START (ADDRESS_CH2TEMP_E_END)
#define ADDRESS_CH3TEMP_E_END (ADDRESS_CH3TEMP_E_START + LEN_CALCDATA_E)
#define ADDRESS_CH4TEMP_E_START (ADDRESS_CH3TEMP_E_END)
#define ADDRESS_CH4TEMP_E_END (ADDRESS_CH4TEMP_E_START + LEN_CALCDATA_E)
#define ADDRESS_CH5TEMP_E_START (ADDRESS_CH4TEMP_E_END)
#define ADDRESS_CH5TEMP_E_END (ADDRESS_CH5TEMP_E_START + LEN_CALCDATA_E)
#define ADDRESS_CH6TEMP_E_START (ADDRESS_CH5TEMP_E_END)
#define ADDRESS_CH6TEMP_E_END (ADDRESS_CH6TEMP_E_START + LEN_CALCDATA_E)
//*********************************************************************//

#define SAVECOUNT 5

typedef struct ModuleConfigData //配置类数据结构
{ 
   P_MSGQUEUE m_pMsgQueue;  //消息队列 
   PCONFIGDATA m_pSysData;     //系统数据
   BOOLEAN m_PressSta; //处理调用状态记录
	 INT8U m_Count;
   
   INT8U m_SaveCount;
   BOOLEAN m_SaveStatus;
   INT8U m_SaveStep;
}MODULECONFIGDATA,*PMODULECONFIGDATA;

typedef struct ModuleConfig //服务器类
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
    void (*pModele1msProcess)(void* pArg);  //1ms调度任务
    PVOID m_pBaseData;
}MODULECONFIG,*PMODULECONFIG;
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
static void ConfigSave(void* pArg);

static void ConfigSaveProc(void* pArg);//保存数据

static void ConfigSave(void* pArg);//置保存实现函数
static void ConfigLoad(void* pArg);//读取数据实现函数
static void Config_T_Save(void* pArg);//置保存实现函数
static void Config_T_Load(void* pArg);//读取数据实现函数
static void Config_E_Save(void* pArg);//置保存实现函数
static void Config_E_Load(void* pArg);//读取数据实现函数
static void ConfigSave_Base(void* pArg);//置保存实现函数
static void ConfigLoad_Base(void* pArg);

static void MallocSysData(PMODULECONFIGDATA pData);
//************************内部处理函数实现******************************//
static void I2CMemSave(INT16U Addres, PVOID pObj, INT16U len);
static void I2CMemLoad(INT16U Addres, PVOID pObj, INT16U len);
static void ModuleConfigPrintInfo(PMODULECONFIGDATA pData);
static void ModuleConfigPrint(INT16U *pData, INT16U len);
#endif
