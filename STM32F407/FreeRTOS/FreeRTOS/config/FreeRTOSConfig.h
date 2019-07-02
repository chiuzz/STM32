/*
 * FreeRTOS Kernel V10.2.1
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H
#include "stm32f4xx.h"
#include "usart.h"
/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/

/* Ensure stdint is only used by the compiler, and not the assembler. */
#ifdef __ICCARM__
	#include <stdint.h>
	extern uint32_t SystemCoreClock;
#endif

//FreeRTOS.h:
//#ifndef configSUPPORT_STATIC_ALLOCATION
//	/* Defaults to 0 for backward compatibility. */
//	#define configSUPPORT_STATIC_ALLOCATION 0
//#endif

//#ifndef configSUPPORT_DYNAMIC_ALLOCATION
//	/* Defaults to 1 for backward compatibility. */
//	#define configSUPPORT_DYNAMIC_ALLOCATION 1
//#endif

//支持静态内存
//#define configSUPPORT_STATIC_ALLOCATION 1

/************************************************************************
* FreeRTOS 基础配置配置选项
*********************************************************************/
/* 置 1： RTOS 使用抢占式调度器；置 0： RTOS 使用协作式调度器（时间片）
*
* 注：在多任务管理机制上，操作系统可以分为抢占式和协作式两种。
* 协作式操作系统是任务主动释放 CPU 后，切换到下一个任务。
* 任务切换的时机完全取决于正在运行的任务。
*/
#define configUSE_PREEMPTION			1
/*
* 写入实际的 CPU 内核时钟频率，也就是 CPU 指令执行频率，通常称为 Fclk
* Fclk 为供给 CPU 内核的时钟信号，我们所说的 cpu 主频为 XX MHz，
* 就是指的这个时钟信号，相应的， 1/Fclk 即为 cpu 时钟周期；
*/
#define configCPU_CLOCK_HZ				( SystemCoreClock )
//RTOS 系统节拍中断的频率。即一秒中断的次数，每次中断 RTOS 都会进行任务调度
#define configTICK_RATE_HZ				( ( TickType_t ) 1000 )
//可使用的最大优先级
#define configMAX_PRIORITIES			( 5 )
//空闲任务使用的堆栈大小
#define configMINIMAL_STACK_SIZE		( ( unsigned short ) 130 )
//系统所有总的堆大小
#define configTOTAL_HEAP_SIZE			( ( size_t ) ( 75 * 1024 ) )
//任务名字字符串长度
#define configMAX_TASK_NAME_LEN			( 10 )
//启用可视化跟踪调试
#define configUSE_TRACE_FACILITY		1
//系统节拍计数器变量数据类型， 1 表示为 16 位无符号整形， 0 表示为 32 位无符号整形
#define configUSE_16_BIT_TICKS			0
//空闲任务放弃 CPU 使用权给其他同优先级的用户任务
#define configIDLE_SHOULD_YIELD			1
//使用互斥信号量
#define configUSE_MUTEXES				1
 /* 设置可以注册的信号量和消息队列个数 */
#define configQUEUE_REGISTRY_SIZE		8
//使用递归互斥信号量
#define configUSE_RECURSIVE_MUTEXES		1

#define configUSE_APPLICATION_TASK_TAG	0
//为 1 时使用计数信号量
#define configUSE_COUNTING_SEMAPHORES	1
//启用运行时间统计功能
#define configGENERATE_RUN_TIME_STATS	0

/***************************************************************
FreeRTOS 与钩子函数有关的配置选项
**************************************************************/
/* 置 1：使用空闲钩子（Idle Hook 类似于回调函数）；置 0：忽略空闲钩子
*
* 空闲任务钩子是一个函数，这个函数由用户来实现，
* FreeRTOS 规定了函数的名字和参数： void vApplicationIdleHook(void )，
* 这个函数在每个空闲任务周期都会被调用
* 对于已经删除的 RTOS 任务，空闲任务可以释放分配给它们的堆栈内存。
* 因此必须保证空闲任务可以被 CPU 执行
* 使用空闲钩子函数设置 CPU 进入省电模式是很常见的
* 不可以调用会引起空闲任务阻塞的 API 函数
*/
#define configUSE_IDLE_HOOK				0
/* 置 1：使用时间片钩子（Tick Hook） ；置 0：忽略时间片钩子
*
*
* 时间片钩子是一个函数，这个函数由用户来实现，
* FreeRTOS 规定了函数的名字和参数： void vApplicationTickHook(void )
* 时间片中断可以周期性的调用
* 函数必须非常短小，不能大量使用堆栈，
* 不能调用以”FromISR" 或 "FROM_ISR”结尾的 API 函数
*/
#define configUSE_TICK_HOOK				0
//使用内存申请失败钩子函数
#define configUSE_MALLOC_FAILED_HOOK	0
/*
* 大于 0 时启用堆栈溢出检测功能，如果使用此功能
* 用户必须提供一个栈溢出钩子函数，如果使用的话
* 此值可以为 1 或者 2，因为有两种栈溢出检测方法
*/
#define configCHECK_FOR_STACK_OVERFLOW	0


/* Co-routine definitions. */
//启用协程，启用协程以后必须添加文件 croutine.c
#define configUSE_CO_ROUTINES 		0
//协程的有效优先级数目
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )

/***********************************************************************
FreeRTOS 与软件定时器有关的配置选项
**********************************************************************/
//启用软件定时器
#define configUSE_TIMERS				1
//软件定时器优先级
#define configTIMER_TASK_PRIORITY		( 2 )
//软件定时器队列长度
#define configTIMER_QUEUE_LENGTH		10
//软件定时器任务堆栈大小
#define configTIMER_TASK_STACK_DEPTH	( configMINIMAL_STACK_SIZE * 2 )

/************************************************************
FreeRTOS 可选函数配置选项
************************************************************/
#define INCLUDE_vTaskPrioritySet		1
#define INCLUDE_uxTaskPriorityGet		1
#define INCLUDE_vTaskDelete				1
#define INCLUDE_vTaskCleanUpResources	1
#define INCLUDE_vTaskSuspend			1
#define INCLUDE_vTaskDelayUntil			1
#define INCLUDE_vTaskDelay				1

/******************************************************************
FreeRTOS 与中断有关的配置选项
******************************************************************/
/* Cortex-M specific definitions. */
#ifdef __NVIC_PRIO_BITS
	/* __BVIC_PRIO_BITS will be specified when CMSIS is being used. */
	#define configPRIO_BITS       		__NVIC_PRIO_BITS
#else
	#define configPRIO_BITS       		4        /* 15 priority levels */
#endif

//中断最低优先级
/* The lowest interrupt priority that can be used in a call to a "set priority"
function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			0xf

//系统可管理的最高中断优先级
/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	5

/* Interrupt priorities used by the kernel port layer itself.  These are generic
to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY 		( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
	
/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
#define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }	
	
/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names. */
#define vPortSVCHandler SVC_Handler
#define xPortPendSVHandler PendSV_Handler
#define xPortSysTickHandler SysTick_Handler

#endif /* FREERTOS_CONFIG_H */

