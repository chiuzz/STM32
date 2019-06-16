#ifndef  __COMMON_H__
#define  __COMMON_H__
// #include "ucos_ii.h"
// #include "os_cpu.h"
#include "stm32f10x.h"
// #include "MsgQueue.h"
// #include "dllist.h"
#include "struct_def.h"
// #include "msg_def.h"
//#include "delay.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
/*****************************************/
/***********正常工作打开 开始*************/
/*****************************************/

#define VERSION 101 //下位机版本号 

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

#endif
