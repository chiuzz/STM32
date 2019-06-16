//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* �� �� �� : Task_includes.h
//*
//* �ļ����� : ���������ļ�
//*
//* ��    �� : 
//* ��    �� : 
//* �� �� �� : IAR EWARM 5.20
//*********************************************************************************************************
//*
#ifndef __CREATR_MULTI_TASK_123_
#define __CREATR_MULTI_TASK_123_

#include "common.h"

//*********************************************************************************************************
//*****************************************    �ź���    **************************************************
//*********************************************************************************************************
// ϵͳ��Դ - NAND FLASH
//OS_EXT OS_EVENT *Sem_NAND_Flash;
// ϵͳ��Դ - RTC
//OS_EXT OS_EVENT *Sem_RTC;
//
//*********************************************************************************************************
//** �� �� �� �� : void OSTaskStart(void *pdata)
//**
//** �� �� �� �� : ϵͳ��ʼ��һ�����е�����,��������...
//**
//**               �� ��ʼ��Ŀ��ϵͳ
//**               �� ͳ�������ʼ��
//**               �� ϵͳ�¼��Ľ���
//**               �� �û�����Ľ���
//**               �� �����ɾ������
//*********************************************************************************************************
//
//#define  APP_TASK_160_STK_SIZE            160                                         //��ջ�ܳߴ�
//#define  APP_TASK_100_STK_SIZE            400                                         //��ջ�ܳߴ�
//#define  APP_TASK_50_STK_SIZE            50                                         //��ջ�ܳߴ�


//#define  APP_TASK_START_PRIO                10                                           //�������ȼ�
//#define  APP_TASK_START_ID                  APP_TASK_START_PRIO                         //����ID
//#define	 APP_TASK_START_STK_SIZE		    APP_TASK_100_STK_SIZE
//OS_EXT   OS_STK                             APP_TaskStartStk[APP_TASK_100_STK_SIZE];  //�����ջ


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

//UCOSIII���������ȼ��û�������ʹ�ã�ALIENTEK
//����Щ���ȼ��������UCOSIII��5��ϵͳ�ڲ�����
//���ȼ�0���жϷ������������� OS_IntQTask()
//���ȼ�1��ʱ�ӽ������� OS_TickTask()
//���ȼ�2����ʱ���� OS_TmrTask()
//���ȼ�OS_CFG_PRIO_MAX-2��ͳ������ OS_StatTask()
//���ȼ�OS_CFG_PRIO_MAX-1���������� OS_IdleTask()

//�������ȼ�
#define START_2_UART_TASK_PRIO		8
#define TASK_SERVER_PRIO		7
#define TASK_US_PRIO		6
#define TASK_10MS_PRIO		5
#define TASK_50MS_PRIO		9
#define TASK_1S_PRIO		10
//�����ջ��С	
#define START_2_UART_STK_SIZE 		1024
#define TASK_SERVER_STK_SIZE 	256	
#define TASK_US_STK_SIZE 	    256	
#define TASK_10MS_STK_SIZE	    256	
#define TASK_50MS_STK_SIZE	    256 	
#define TASK_1S_STK_SIZE	    256	

//������
void start_2_uart_task(void *p_arg);
void server_task(void *p_arg);
void us_task(void *p_arg);
void task_10ms(void *p_arg);
void task_50ms(void *p_arg);
void task_1s(void *p_arg);

extern void CreateMultiTask(void);
extern void AppCycle(void);
#endif
