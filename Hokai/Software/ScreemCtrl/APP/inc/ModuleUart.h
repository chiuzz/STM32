//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* 文 件 名 : ModuleUart.h
//*
//* 文件描述 : 主服务任务文件
//*
//* 作    者 : LGL
//* 版    本 :
//* 编 译 器 : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MODULE_UART_H__
#define  __MODULE_UART_H__

#include "common.h"
#include "usart3.h"
#include "struct_def.h"
#define BUFMAX 24
#define DATABUF (BUFMAX*2)

typedef enum
{
    UART_STOP = 0,
    UART_INIT,
    UART_WORK,
}	eUartWorkStatus;


typedef struct UartData
{
    INT16U m_DataBuf[DATABUF];
    INT16U m_index;
    INT16U m_MarkIndex;
    BOOLEAN m_MarkSta;
    INT16U m_buf[BUFMAX];
    INT8U m_buflen;
    BOOLEAN m_Sta;
} UARTDATA,*PUARTDATA;



typedef struct ModuleUartData //配置类数据结构
{
    P_MSGQUEUE m_pMsgQueue;  //消息队列
    INT16U m_Count; //计时器
    INT16U m_InitCount; //计时器
    INT16U m_Led_Count;
    BOOLEAN m_PressSta; //处理调用状态记录
    PCONFIGDATA m_pSysData;     //系统数据
//************************以下增加模块内部使用的变量或者其它元素******************************//
    PUARTDATA m_pData;
    INT16U *m_pAdArr;

    // HTB_RAM HTBRam;
    eUartWorkStatus m_UartWorkSta;


    INT16U m_50msCount; //50ms计时器

    BOOLEAN TemperatureBool;

    INT16U key_Temp;  //按键码
    BOOLEAN Temp1SetBOOL;
    BOOLEAN Temp2SetBOOL;
    BOOLEAN WaterSetBOOL;
    BOOLEAN WaterHotBOOL; //水温过高
    BOOLEAN SystemAlmBOOL;
    INT16U UsartSendFlag;//发送串口消息的标记位

} MODULEUARTDATA,*PMODULEUARTDATA;

typedef struct ModuleUart //服务器类
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
    void (*pStart)(void* pArg);
} MODULEUART,*PMODULEUART;
//*
//********************************************************************************************************
//* 函 数 名 : void CreateModuleUart(void)
//**------------------------------------------------------------------------------------------------------
//* 描    述 : 创建模块
//**------------------------------------------------------------------------------------------------------
//* 输入参数 : PMODULEBASE. 空指针
//**------------------------------------------------------------------------------------------------------
//* 输出参数 : PMODULEBASE. 申请内存空间后返回基类指针
//**------------------------------------------------------------------------------------------------------
//* 返   回  : PMODULEUARTDATA.申请内存空间后返回基类数据指针
//********************************************************************************************************
//*
extern PMODULEBASE CreateModuleUart(PMODULESERVERDATA pServerData);

//************************内部处理函数实现******************************//
static BOOLEAN ModuleUartInit(void* pArg);
static BOOLEAN ModuleUartReset(void* pArg);
static BOOLEAN ModuleUartStart(void* pArg);
static BOOLEAN ModuleUartStop(void* pArg);
static BOOLEAN ModuleUartRelease(void* pArg);
static void ModuleUart1sProcess(void* pArg);
static void UartMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);

//************************模块功能实现函数******************************//
extern void SendUartData(uint16_t data);
//************************内部处理函数实现******************************//
static void UartWorkStatusProc(void* pArg);
static void Start(void* pArg);
static void GetUartData(void* pArg);
static void Unpack(void* pArg, INT16U *pData, INT8U len);
static BOOLEAN CheckSum(INT16U* buf, INT8U len);

static void ModuleUart50msProcess(void* pArg);
static void ModuleUart10msProcess(void* pArg);


//-----------------------------tommy


//u8 GetButtomValue();//硬件获取按键
void Usart3SendDataToMaster(void* pArg,uint8_t keyNumber);//发送串口消息到主控板



#endif
