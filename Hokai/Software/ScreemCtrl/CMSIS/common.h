//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* 文 件 名 : common.h
//*
//* 文件描述 : 一般定义文件
//*
//* 作    者 : 
//* 版    本 : 
//* 编 译 器 : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef  __COMMON_H__
#define  __COMMON_H__
#include "ucos_ii.h"
#include "stm32f10x.h"
#include "MsgQueue.h"
// #include "msg_def.h"
#include "dllist.h"
//#include "delay.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
/*****************************************/
/***********正常工作打开 开始*************/
/*****************************************/

#define VERSION 101 //下位机版本号 

#define VALVE_CLOSE_COUNT 500 //关阀裕量
#define SIGHNUM 50  //叹息个数
#define SENSITIVITY_TIME 2 //X10ms 20ms的触发压力计时
#define RESP_TIME 100 //硬呼气时间 PSV SIMV用到 单位10ms
#define TIMEOUTSEC 100  //1Sec
#define TIMEOUTPRE 20    //20%
#define FINDMAXFLOWCOUNT 3 //找最大流速递减计算个数

#define DMAUART //////////////////DMA发数定义///////////////////
#define PRESS_10MS_FILTER //////////////////定义压力10ms平均滤波处理///////////////////
// #define FLOW_CALIBRATION //////////////////定义校正处理///////////////////
#define USED_RELATIVEPRESS //////////////////定义使用相对压力///////////////////
//#define LOST_VT_PROC //////////////////长管潮气量补偿处理 (未测试)//////////
/*****************************************/
/***********正常工作打开 结束*************/
/*****************************************/

/*****************************************/
/*************调试时打开 开始*************/
/*****************************************/
// #define DAC_OUT //////////////////DAC发流量数据定义///////////////////
// #define TEST_SYSTEM //////////////////测试模式数据定义///////////////////

#define SRC_PEEP //备压PEEP阀, 否则原有PEEP阀

// #define IIC_TEST  //////////////////定义启动阀配置显示信息///////////////////
 #define VALVE_CONFIG_PRINTF //////////////////阀动作配置打印//////////
 #define MODE_CONFIG_PRINTF //////////////////呼吸模式配置打印//////////
// #define VALVE_MOVE_PRINTF //////////////////阀动作类型打印//////////
// #define SYSTEM_CONFIG //////////////////定义启动阀配置显示信息///////////////////
// #define STOP_MODE_TRIGER //////////////////定义停止模式触发///////////////////
// #define STOP_PEAK_LIMIT //////////////////定义停止峰压限制///////////////////
// #define OFF_UART ///////////////////断开串口数据//////////////////
#ifdef OFF_UART
#define CAL_TYPE CAL_PRESS
// #define CAL_TYPE CAL_O2_VALVE
// #define CAL_TYPE CAL_AIR_VALVE
// #define CAL_TYPE CAL_PEEP_VALVE
// #define CAL_TYPE CAL_O2
#endif
/*****************************************/
/*************调试时打开 结束*************/
/*****************************************/


typedef void*         PVOID;
//#define null          ((void*)0)

//#define ASSERT(XX) {printf(" Assert (#XX) False !!!\n");}
#define ASSERT(XX) {assert(XX);}
#define INVALID_32U_VALUE 0xefef
#define INVALID_16U_VALUE 0xef
#define INVALID_8U_VALUE 0xe

#define PR {printf("\n");}
#define PP {printf("%-15s()",__func__);printf(" %-10s:%-5d",__FILE__,__LINE__);}

#define PD(X) {printf(#X" = %-5d ",(X));PP;PR;}
#define PS(X) {printf("Str is < ");printf(X);printf(" > ");PP;PR;}

#define LOWORD(l)           ((INT32U)(l))
#define HIWORD(l)           ((INT32U)(((INT32U)(l) >> 16) & 0xFFFF))
#define LOBYTE(w)           ((INT8U)(w))
#define HIBYTE(w)           ((INT8U)(((INT32U)(w) >> 8) & 0xFF))

#define BIT0 0x0001
#define BIT1 0x0002
#define BIT2 0x0004
#define BIT3 0x0008
#define BIT4 0x0010
#define BIT5 0x0020
#define BIT6 0x0040
#define BIT7 0x0080
#define BIT8 0x0100
#define BIT9 0x0200
#define BIT10 0x0400
#define BIT11 0x0800
#define BIT12 0x1000
#define BIT13 0x2000
#define BIT14 0x4000
#define BIT15 0x8000

//#define SETBIT(X) {}
#define EOM 0xFF	
#define SOM 0xEF 
#define DSOM 0 //包头
#define DSEQ 1 //包号
#define D1 2 	 //通道0高字节
#define D2 3	 //通道0低字节
#define D3 4	 //通道1高字节
#define D4 5	 //通道1低字节
#define D5 6   //通道2高字节
#define D6 7	 //通道2低字节
#define D7 8   //通道3高字节
#define D8 9	 //通道3低字节
#define D9 10  //通道4高字节
#define D10 11  //通道4低字节
#define D11 12  //通道5高字节
#define D12 13	//通道5低字节
#define D13 14  //通道6高字节
#define D14 15	//通道6低字节
#define D15 16	//高两位校准模式,低两位校准点数
#define D16 17  //VREF
#define DCC 18  //校验
#define DEOM 19 //包尾
#endif
