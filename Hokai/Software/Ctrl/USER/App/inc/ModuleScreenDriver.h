//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* 文 件 名 : ModuleScreenDriver.h
//*
//* 文件描述 : 主服务任务文件
//*
//* 作    者 : LGL
//* 版    本 : 
//* 编 译 器 : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __MODULE_SCREENDRIVER_H__
#define  __MODULE_SCREENDRIVER_H__

#include "common.h"
#include "struct_def.h"

#define SCREOM 0xFF	
#define SCRSOM 0xEF 
//#define DSOM 0 //包头
//#define CMD 1 //命令
//#define D1 2 	 //通道0高字节
//#define D2 3	 //通道0低字节
//#define D3 4	 //通道1高字节
//#define D4 5	 //通道1低字节
//#define D5 6   //通道2高字节
//#define DCC 7  //校验
//#define DEOM 8 //包尾
#define SCRBUFMAX 8 //数据包长度 
#define SCRDATABUF (SCRBUFMAX*2)

typedef struct UartSrcData 
{ 
   INT16U m_DataBuf[SCRDATABUF];
   INT16U m_index;
   INT16U m_MarkIndex;
   BOOLEAN m_MarkSta;
   INT16U m_buf[SCRBUFMAX];
   INT8U m_buflen;
   BOOLEAN m_Sta;
}UARTSRCDATA,*PUARTSRCDATA;	

typedef struct ModuleScreenDriverData //配置类数据结构
{ 
   P_MSGQUEUE m_pMsgQueue;  //消息队列 
   INT16U m_Count; //计时器
   BOOLEAN m_PressSta; //处理调用状态记录
 //************************以下增加模块内部使用的变量或者其它元素******************************//  
   PUARTSRCDATA m_pData;
	 PSYSPARAMDATA m_pSysData; //全局变量
	 PSYSCONFIGDATA m_pCfgData; //全局变量
		PSYSCALCDATA m_pCalData; //全局变量
		PSYSADJDATA m_pAdjData;
}MODULESCREENDRIVERDATA,*PMODULESCREENDRIVERDATA;

typedef struct ModuleScreenDriver //服务器类
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
}MODULESCREENDRIVER,*PMODULESCREENDRIVER;
//*
//********************************************************************************************************
//* 函 数 名 : void CreateModuleScreenDriver(void)
//**------------------------------------------------------------------------------------------------------
//* 描    述 : 创建模块
//**------------------------------------------------------------------------------------------------------
//* 输入参数 : PMODULEBASE. 空指针
//**------------------------------------------------------------------------------------------------------
//* 输出参数 : PMODULEBASE. 申请内存空间后返回基类指针
//**------------------------------------------------------------------------------------------------------
//* 返   回  : PMODULESCREENDRIVERDATA.申请内存空间后返回基类数据指针
//********************************************************************************************************
//*
extern PMODULEBASE CreateModuleScreenDriver(PMODULESERVERDATA pServerData);
extern void SendSrcUartData(uint16_t data); //由驱动调用，缓冲区压入数据及数据流分包
//************************内部处理函数实现******************************//
static BOOLEAN ModuleScreenDriverInit(void* pArg);
static BOOLEAN ModuleScreenDriverReset(void* pArg);
static BOOLEAN ModuleScreenDriverStart(void* pArg);
static BOOLEAN ModuleScreenDriverStop(void* pArg);
static BOOLEAN ModuleScreenDriverRelease(void* pArg);
static void ModuleScreenDriver50msProcess(void* pArg);
static void ScreenDriverMsgNotify(void* pArg, INT8U MsgId, INT16U lParam, INT16U wParam, void* pBuf);
static void ModeleScreenDriverUartProcess(void* pArg);
//************************模块功能实现函数******************************//

//************************内部处理函数实现******************************//
static BOOLEAN SrcCheckSum(INT16U* buf, INT8U len); //校验和执行函数
static void SrcUnpack(void* pArg, INT16U *pData, INT8U len); //输入数据包，执行协议解析
void UsartSendFullData_Screen(void* pArg);//发送串口消息到屏幕
#endif
