#include "includes.h"

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
/* 10ms调度 任务句柄 */
static TaskHandle_t Delay10ms_Task_Handle;
/* 100ms调度 任务句柄 */
static TaskHandle_t Delay100ms_Task_Handle;

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
static void AppTaskCreate(void);					/* 用于创建任务 */
static void LED_Task(void* pvParameters);			/* LED_Task 任务实现 */
static void Delay10ms_Task(void* pvParameters);		/* 10ms调度_Task 任务实现 */
static void Delay100ms_Task (void* parameter);		/* 100ms调度 任务实现 */

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
    BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为 pdPASS */
    /*
    * STM32 中断优先级分组为 4，即 4bit 都用来表示抢占优先级，范围为： 0~15
    * 优先级分组只需要分组一次即可，以后如果有其他的任务需要用到中断，
    * 都统一用这个优先级分组，千万不要再分组，切忌。
    */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    led_init();
    beep_init();
    key_init();
    uart2_init(115200);
    uart3_init(115200);
    delay_init(168);
    LCD_Init();
    usmart_init(168);
    xReturn = xTaskCreate((TaskFunction_t )AppTaskCreate, 			/* 任务入口函数 */
                          (const char* )"AppTaskCreate",			/* 任务名字 */
                          (uint16_t )512, 						/* 任务栈大小 */
                          (void* )NULL,							/* 任务入口函数参数 */
                          (UBaseType_t )1, 						/* 任务的优先级 */
                          (TaskHandle_t* )&AppTaskCreate_Handle);	/* 任务控制块指针 */
    /* 启动任务调度 */
    if (pdPASS == xReturn)
        vTaskStartScheduler(); /* 启动任务，开启调度 */
    else
        return -1;
    while (1); /* 正常不会执行到这里 */
}

static void LED_Task (void* parameter)
{
    while(1)
    {
        if(NetWorkData.CmdStu.cmd==LED_RED_OFF)
            LED_RED_OFF();
        else if(NetWorkData.CmdStu.cmd==LED_RED_ON)
            LED_RED_ON();
        else if(NetWorkData.CmdStu.cmd==LED_GREEN_OFF)
            LED_GREEN_OFF();
        else if(NetWorkData.CmdStu.cmd==LED_GREEN_ON)
            LED_GREEN_ON();
        else if(NetWorkData.CmdStu.cmd==LED_RED_BREATH)
            led_breath(RED_LED);
        else if(NetWorkData.CmdStu.cmd==LED_GREEN_BREATH)
            led_breath(GREEN_LED);

        beep_deal();
        key_scan();
        if(read_OK)
        {
            read_OK=0;
            if(key_stu[KEY_UP_ID].value==SINGLE) {
                key_stu[KEY_UP_ID].value=NONE;
                AT_Cmd_Send((void *)"AT+CIPSTART=\"TCP\",\"192.168.43.177\",8888");
            }
            if(key_stu[KEY_LEFT_ID].value==SINGLE) {
                key_stu[KEY_LEFT_ID].value=NONE;
                AT_Cmd_Send((void *)"AT+CWJAP_CUR=\"Chiuzz_MI\",\"19931008\"");
            }
            if(key_stu[KEY_MID_ID].value==SINGLE) {
                key_stu[KEY_MID_ID].value=NONE;
                AT_Cmd_Send((void *)"AT+CWMODE_CUR=1");
            }
            if(key_stu[KEY_RIGHT_ID].value==SINGLE) {
                key_stu[KEY_RIGHT_ID].value=NONE;
                AT_Cmd_Send((void *)"AT+CIPMUX?");
                AT_Cmd_Send((void *)"AT+CIPMUX=0");
            }

        }
        vTaskDelay(1);
    }
}

static void Delay10ms_Task (void* parameter)
{
    while(1)
    {
//		if(uart3_sta){
//			uart3_sta=0;
//			AT_Test((u8 *)"OK");
//		}
        vTaskDelay(10);
    }
}

static void Delay100ms_Task (void* parameter)
{
    while(1)
    {
        usmart_scan();
        NetWorkDeal();
        vTaskDelay(100);
    }
}

static void AppTaskCreate(void)
{
    BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为 pdPASS */
    AT_Cmd_Send((void *)"AT+RST");
    taskENTER_CRITICAL(); //进入临界区

    /* 创建 LED_Task 任务 */
    xReturn = xTaskCreate((TaskFunction_t )LED_Task, 				/* 任务入口函数 */
                          (const char* )"LED_Task",					/* 任务名字 */
                          (uint16_t )512, 							/* 任务栈大小 */
                          (void* )NULL, 							/* 任务入口函数参数 */
                          (UBaseType_t )10, 						/* 任务的优先级 */
                          (TaskHandle_t* )&LED_Task_Handle);		/* 任务控制块指针 */
    if (pdPASS == xReturn)
        printf("create LED_Task success!\r\n");

    /* 创建 Delay10ms_Task 任务 */
    xReturn = xTaskCreate((TaskFunction_t )Delay10ms_Task, 			/* 任务入口函数 */
                          (const char* )"Delay10ms_Task",			/* 任务名字 */
                          (uint16_t )1024, 							/* 任务栈大小 */
                          (void* )NULL, 							/* 任务入口函数参数 */
                          (UBaseType_t )2, 							/* 任务的优先级 */
                          (TaskHandle_t* )&Delay10ms_Task_Handle);	/* 任务控制块指针 */
    if (pdPASS == xReturn)
        printf("create Delay10ms_Task success!\r\n");

    /* 创建 Delay100ms_Task 任务 */
    xReturn = xTaskCreate((TaskFunction_t )Delay100ms_Task, 		/* 任务入口函数 */
                          (const char* )"Delay100ms_Task",			/* 任务名字 */
                          (uint16_t )512, 							/* 任务栈大小 */
                          (void* )NULL, 							/* 任务入口函数参数 */
                          (UBaseType_t )5, 							/* 任务的优先级 */
                          (TaskHandle_t* )&Delay100ms_Task_Handle);	/* 任务控制块指针 */
    if (pdPASS == xReturn)
        printf("create Delay100ms_Task success!\r\n");

    vTaskDelete(AppTaskCreate_Handle); //删除 AppTaskCreate 任务

    taskEXIT_CRITICAL(); //退出临界区
}


