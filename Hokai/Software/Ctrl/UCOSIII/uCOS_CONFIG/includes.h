/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                             (c) Copyright 2013; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                           MASTER INCLUDES
*
*                                       IAR Development Kits
*                                              on the
*
*                                    STM32F429II-SK KICKSTART KIT
*
* Filename      : includes.h
* Version       : V1.00
* Programmer(s) : FT
*********************************************************************************************************
*/

#ifndef  INCLUDES_MODULES_PRESENT
#define  INCLUDES_MODULES_PRESENT


/*
*********************************************************************************************************
*                                         STANDARD LIBRARIES
*********************************************************************************************************
*/


#include  <stdio.h>
#include  <string.h>
#include  <ctype.h>
#include  <stdlib.h>
#include  <stdarg.h>
#include  <math.h>


/*
*********************************************************************************************************
*                                                 OS
*********************************************************************************************************
*/

#include  <os.h>


/*
*********************************************************************************************************
*                                              LIBRARIES
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <lib_def.h>
#include  <lib_ascii.h>
#include  <lib_math.h>
#include  <lib_mem.h>
#include  <lib_str.h>

/*
*********************************************************************************************************
*                                              APP / BSP
*********************************************************************************************************
*/

#include  <app_cfg.h>
#include  <bsp.h>
//#include  <bsp_int.h>


//*********************************************************************************************************
//*                                              DATA TYPES
//*                                         (Compiler Specific)
//*********************************************************************************************************
//*
typedef CPU_VOID VOID;
typedef CPU_CHAR CHAR; 
typedef CPU_BOOLEAN  BOOLEAN;
typedef CPU_INT08U  INT8U;                    /* Unsigned  8 bit quantity                           */
typedef CPU_INT08S  INT8S;                    /* Signed    8 bit quantity                           */
typedef CPU_INT16U INT16U;                   /* Unsigned 16 bit quantity                           */
typedef CPU_INT16S INT16S;                   /* Signed   16 bit quantity                           */
typedef CPU_INT32U   INT32U;                   /* Unsigned 32 bit quantity                           */
typedef CPU_INT32S   INT32S;                   /* Signed   32 bit quantity                           */
typedef CPU_FP32          FP32;                     /* Single precision floating point                    */
typedef CPU_FP64         FP64;                     /* Double precision floating point                    */
typedef void*         PVOID;

#define FALSE             0
#define TRUE              1

#endif//*
