//*
//*********************************************************************************************************
//*
//*                                                 LOGO
//*
//*
//* �� �� �� : common.h
//*
//* �ļ����� : һ�㶨���ļ�
//*
//* ��    �� : 
//* ��    �� : 
//* �� �� �� : IAR EWARM 5.20
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
/***********���������� ��ʼ*************/
/*****************************************/

#define VERSION 101 //��λ���汾�� 

#define VALVE_CLOSE_COUNT 500 //�ط�ԣ��
#define SIGHNUM 50  //̾Ϣ����
#define SENSITIVITY_TIME 2 //X10ms 20ms�Ĵ���ѹ����ʱ
#define RESP_TIME 100 //Ӳ����ʱ�� PSV SIMV�õ� ��λ10ms
#define TIMEOUTSEC 100  //1Sec
#define TIMEOUTPRE 20    //20%
#define FINDMAXFLOWCOUNT 3 //��������ٵݼ��������

#define DMAUART //////////////////DMA��������///////////////////
#define PRESS_10MS_FILTER //////////////////����ѹ��10msƽ���˲�����///////////////////
// #define FLOW_CALIBRATION //////////////////����У������///////////////////
#define USED_RELATIVEPRESS //////////////////����ʹ�����ѹ��///////////////////
//#define LOST_VT_PROC //////////////////���ܳ������������� (δ����)//////////
/*****************************************/
/***********���������� ����*************/
/*****************************************/

/*****************************************/
/*************����ʱ�� ��ʼ*************/
/*****************************************/
// #define DAC_OUT //////////////////DAC���������ݶ���///////////////////
// #define TEST_SYSTEM //////////////////����ģʽ���ݶ���///////////////////

#define SRC_PEEP //��ѹPEEP��, ����ԭ��PEEP��

// #define IIC_TEST  //////////////////����������������ʾ��Ϣ///////////////////
 #define VALVE_CONFIG_PRINTF //////////////////���������ô�ӡ//////////
 #define MODE_CONFIG_PRINTF //////////////////����ģʽ���ô�ӡ//////////
// #define VALVE_MOVE_PRINTF //////////////////���������ʹ�ӡ//////////
// #define SYSTEM_CONFIG //////////////////����������������ʾ��Ϣ///////////////////
// #define STOP_MODE_TRIGER //////////////////����ֹͣģʽ����///////////////////
// #define STOP_PEAK_LIMIT //////////////////����ֹͣ��ѹ����///////////////////
// #define OFF_UART ///////////////////�Ͽ���������//////////////////
#ifdef OFF_UART
#define CAL_TYPE CAL_PRESS
// #define CAL_TYPE CAL_O2_VALVE
// #define CAL_TYPE CAL_AIR_VALVE
// #define CAL_TYPE CAL_PEEP_VALVE
// #define CAL_TYPE CAL_O2
#endif
/*****************************************/
/*************����ʱ�� ����*************/
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
#define DSOM 0 //��ͷ
#define DSEQ 1 //����
#define D1 2 	 //ͨ��0���ֽ�
#define D2 3	 //ͨ��0���ֽ�
#define D3 4	 //ͨ��1���ֽ�
#define D4 5	 //ͨ��1���ֽ�
#define D5 6   //ͨ��2���ֽ�
#define D6 7	 //ͨ��2���ֽ�
#define D7 8   //ͨ��3���ֽ�
#define D8 9	 //ͨ��3���ֽ�
#define D9 10  //ͨ��4���ֽ�
#define D10 11  //ͨ��4���ֽ�
#define D11 12  //ͨ��5���ֽ�
#define D12 13	//ͨ��5���ֽ�
#define D13 14  //ͨ��6���ֽ�
#define D14 15	//ͨ��6���ֽ�
#define D15 16	//����λУ׼ģʽ,����λУ׼����
#define D16 17  //VREF
#define DCC 18  //У��
#define DEOM 19 //��β
#endif
