#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"

/*FreeRTOS 头文件*/
#include "FreeRTOS.h"
#include "task.h"


/*
**************************** 任务句柄 *********************************
* 任务句柄是一个指针，用于指向一个任务，当任务创建好之后，它就具有了一个任务句柄
* 以后我们要想操作这个任务都需要通过这个任务句柄，如果是自身的任务操作自己，那么
* 这个句柄可以为 NULL。
***********************************************************************
*/
/* 创建任务句柄 */
static TaskHandle_t AppTaskCreate_Handle;
/* LED 任务句柄 */
static TaskHandle_t LED_Task_Handle;

/*
***************************** 内核对象句柄 ******************************
* 信号量，消息队列，事件标志组，软件定时器这些都属于内核的对象，要想使用这些内核
* 对象，必须先创建，创建成功之后会返回一个相应的句柄。实际上就是一个指针，后续我
* 们就可以通过这个句柄操作这些内核对象。
*
* 内核对象说白了就是一种全局的数据结构，通过这些数据结构我们可以实现任务间的通信，
* 任务间的事件同步等各种功能。至于这些功能的实现我们是通过调用这些内核对象的函数
* 来完成的
**************************************************************************
*/



/*
************************** 全局变量声明 **********************************
* 当我们在写应用程序的时候，可能需要用到一些全局变量。
**************************************************************************
*/

/*
*************************************************************************
* 函数声明
*************************************************************************
*/
static void AppTaskCreate(void);				/* 用于创建任务 */
static void LED_Task(void* pvParameters);		/* LED_Task 任务实现 */
void led_init(void);							/* LED 初始化 */

/**
* 使用了静态分配内存，以下这两个函数是由用户实现，函数在 task.c 文件中有引用
* 当且仅当 configSUPPORT_STATIC_ALLOCATION 这个宏定义为 1 的时候才有效
*/
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
									StackType_t **ppxIdleTaskStackBuffer,
									uint32_t *pulIdleTaskStackSize);

void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer,
									StackType_t **ppxTimerTaskStackBuffer,
									uint32_t *pulTimerTaskStackSize);


/*
*************************************************************************
* 堆栈与任务控制块
*************************************************************************
*/
/* 空闲任务任务堆栈 */
static StackType_t Idle_Task_Stack[configMINIMAL_STACK_SIZE];
/* 空闲任务控制块 */
static StaticTask_t Idle_Task_TCB;

/* 定时器任务堆栈 */
static StackType_t Timer_Task_Stack[configTIMER_TASK_STACK_DEPTH];
/* 定时器任务控制块 */
static StaticTask_t Timer_Task_TCB;

/* AppTaskCreate 任务堆栈 */
static StackType_t AppTaskCreate_Stack[128];
/* AppTaskCreate 任务控制块 */
static StaticTask_t AppTaskCreate_TCB;

/* LED 任务堆栈 */
static StackType_t LED_Task_Stack[128];
/* LED 任务控制块 */
static StaticTask_t LED_Task_TCB;


/**
*******************************************************************
* @brief 获取空闲任务的任务堆栈和任务控制块内存
* ppxTimerTaskTCBBuffer : 任务控制块内存
* ppxTimerTaskStackBuffer : 任务堆栈内存
* pulTimerTaskStackSize : 任务堆栈大小
* @author fire
* @version V1.0
* @date 2018-xx-xx
**********************************************************************
*/
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
									StackType_t **ppxIdleTaskStackBuffer,
									uint32_t *pulIdleTaskStackSize)
{
	*ppxIdleTaskTCBBuffer=&Idle_Task_TCB;
	*ppxIdleTaskStackBuffer=Idle_Task_Stack;
	*pulIdleTaskStackSize=configMINIMAL_STACK_SIZE;
}

/**
*********************************************************************
* @brief 获取定时器任务的任务堆栈和任务控制块内存
* ppxTimerTaskTCBBuffer : 任务控制块内存
* ppxTimerTaskStackBuffer : 任务堆栈内存
* pulTimerTaskStackSize : 任务堆栈大小
* @author fire
* @version V1.0
* @date 2018-xx-xx
**********************************************************************
*/
void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer,
									StackType_t **ppxTimerTaskStackBuffer,
									uint32_t *pulTimerTaskStackSize)
{
	*ppxTimerTaskTCBBuffer=&Timer_Task_TCB;
	*ppxTimerTaskStackBuffer=Timer_Task_Stack;
	*pulTimerTaskStackSize=configTIMER_TASK_STACK_DEPTH;
}

void led_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
}

/*****************************************************************
* @brief 主函数
* @param 无
* @retval 无
* @note 第一步：开发板硬件初始化
* 第二步：创建 APP 应用任务
* 第三步：启动 FreeRTOS，开始多任务调度
*****************************************************************/
int main(void)
{
	/*
	* STM32 中断优先级分组为 4，即 4bit 都用来表示抢占优先级，范围为： 0~15
	* 优先级分组只需要分组一次即可，以后如果有其他的任务需要用到中断，
	* 都统一用这个优先级分组，千万不要再分组，切忌。
	*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	led_init();
    uart_init(115200);
    delay_init(168);

	AppTaskCreate_Handle = xTaskCreateStatic((TaskFunction_t )AppTaskCreate,	//任务函数入口
											(const char* )"AppTaskCreate",		//任务名称
											(uint32_t )128,						//任务堆栈大小
											(void* )NULL,						//传递给任务函数的参数
											(UBaseType_t )3,					//任务优先级
											(StackType_t* )AppTaskCreate_Stack,		//任务堆栈
											(StaticTask_t* )&AppTaskCreate_TCB);	//任务控制块
	
	if (NULL != AppTaskCreate_Handle)	/* 创建成功 */
		vTaskStartScheduler();			/* 启动任务，开启调度 */
	while(1);
}

static void LED_Task (void* parameter)
{
	while(1)
	{
		GPIO_SetBits(GPIOF,GPIO_Pin_9|GPIO_Pin_10);
		printf("LED off!\r\n");
		vTaskDelay(500);
		GPIO_ResetBits(GPIOF,GPIO_Pin_9|GPIO_Pin_10);
		printf("LED on!\r\n");
		vTaskDelay(500);
	}
}


static void AppTaskCreate(void)
{
	taskENTER_CRITICAL();				//进入临界区
	
	/* 创建 LED_Task 任务 */
	LED_Task_Handle = xTaskCreateStatic((TaskFunction_t )LED_Task,
										(const char*)"LED_Task",
										(uint32_t)128,
										(void* )NULL,
										(UBaseType_t)4,
										(StackType_t*)LED_Task_Stack,
										(StaticTask_t*)&LED_Task_TCB);
	
	if (NULL != LED_Task_Handle)
		printf("LED_Task create success!\r\n");
	else
		printf("LED_Task create fail!\r\n");

	vTaskDelete(AppTaskCreate_Handle);	//删除 AppTaskCreate 任务
	taskEXIT_CRITICAL();				//退出临界区
}



