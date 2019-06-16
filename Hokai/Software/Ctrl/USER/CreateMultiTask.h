//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* 文 件 名 : Task_includes.h
//*
//* 文件描述 : 任务配置文件
//*
//* 作    者 : 
//* 版    本 : 
//* 编 译 器 : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef __CREATR_MULTI_TASK_123_
#define __CREATR_MULTI_TASK_123_

#include "common.h"

//*********************************************************************************************************
//*****************************************    信号量    **************************************************
//*********************************************************************************************************
// 系统资源 - NAND FLASH
//OS_EXT OS_EVENT *Sem_NAND_Flash;
// 系统资源 - RTC
//OS_EXT OS_EVENT *Sem_RTC;
//
//*********************************************************************************************************
//** 任 务 名 称 : void OSTaskStart(void *pdata)
//**
//** 任 务 描 述 : 系统开始第一个运行的任务,功能如下...
//**
//**               ① 初始化目标系统
//**               ② 统计任务初始化
//**               ③ 系统事件的建立
//**               ④ 用户任务的建立
//**               ⑤ 挂起或删除自身
//*********************************************************************************************************
//
//#define  APP_TASK_160_STK_SIZE            160                                         //堆栈总尺寸
//#define  APP_TASK_100_STK_SIZE            400                                         //堆栈总尺寸
//#define  APP_TASK_50_STK_SIZE            50                                         //堆栈总尺寸


//#define  APP_TASK_START_PRIO                10                                           //任务优先级
//#define  APP_TASK_START_ID                  APP_TASK_START_PRIO                         //任务ID
//#define	 APP_TASK_START_STK_SIZE		    APP_TASK_100_STK_SIZE
//OS_EXT   OS_STK                             APP_TaskStartStk[APP_TASK_100_STK_SIZE];  //任务堆栈


//#define			Task_Test_Stk_Size		APP_TASK_50_STK_SIZE
//#define			Task_Server_Stk_Size	APP_TASK_100_STK_SIZE
//#define			Task_1s_Prs_Stk_Size	APP_TASK_100_STK_SIZE
//#define			Task_10ms_Prs_Stk_Size	APP_TASK_100_STK_SIZE
//#define			Task_50ms_Prs_Stk_Size	APP_TASK_100_STK_SIZE
//#define			Task_1ms_Prs_Stk_Size	APP_TASK_50_STK_SIZE

//#define			Task_Test_Prio			APP_TASK_START_PRIO+5

//#define			Task_Server_Prio	    7
//#define			Task_1s_Prs_Prio		9
//#define			Task_10ms_Prs_Prio		5
//#define			Task_50ms_Prs_Prio		8
//#define			Task_1ms_Prs_Prio		6

//UCOSIII中以下优先级用户程序不能使用，ALIENTEK
//将这些优先级分配给了UCOSIII的5个系统内部任务
//优先级0：中断服务服务管理任务 OS_IntQTask()
//优先级1：时钟节拍任务 OS_TickTask()
//优先级2：定时任务 OS_TmrTask()
//优先级OS_CFG_PRIO_MAX-2：统计任务 OS_StatTask()
//优先级OS_CFG_PRIO_MAX-1：空闲任务 OS_IdleTask()

//任务优先级
#define START_2_UART_TASK_PRIO		8
#define TASK_SERVER_PRIO		7
#define TASK_US_PRIO		6
#define TASK_10MS_PRIO		5
#define TASK_50MS_PRIO		9
#define TASK_1S_PRIO		10
//任务堆栈大小	
#define START_2_UART_STK_SIZE 		1024
#define TASK_SERVER_STK_SIZE 	256	
#define TASK_US_STK_SIZE 	    256	
#define TASK_10MS_STK_SIZE	    256	
#define TASK_50MS_STK_SIZE	    256 	
#define TASK_1S_STK_SIZE	    256	

//任务函数
void start_2_uart_task(void *p_arg);
void server_task(void *p_arg);
void us_task(void *p_arg);
void task_10ms(void *p_arg);
void task_50ms(void *p_arg);
void task_1s(void *p_arg);

extern void CreateMultiTask(void);
extern void AppCycle(void);
#endif
