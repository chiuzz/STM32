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
/* LCD 任务句柄 */
static TaskHandle_t LCD_Task_Handle;

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
static void LCD_Task(void* pvParameters);		/* LCD_Task 任务实现 */


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
    uart_init(115200);
    delay_init(168);
    LCD_Init();
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
    u8 i;
    while(1)
    {
        led_breath();
        beep_deal();
        key_scan();
        if(read_OK)
        {
            read_OK=0;
            for(i=0; i<KEY_NUM; i++)
                printf("key:%d value:%d\r\n",key_stu[i].id,key_stu[i].value);
        }
        vTaskDelay(1);
    }
}

static void LCD_Task (void* parameter)
{
    u8 x=0;
    u8 lcd_id[12];
    POINT_COLOR=RED;
    sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);
    while(1)
    {
        switch(x)
        {
        case 0:
            LCD_Clear(WHITE);
            break;
        case 1:
            LCD_Clear(BLACK);
            break;
        case 2:
            LCD_Clear(BLUE);
            break;
        case 3:
            LCD_Clear(RED);
            break;
        case 4:
            LCD_Clear(MAGENTA);
            break;
        case 5:
            LCD_Clear(GREEN);
            break;
        case 6:
            LCD_Clear(CYAN);
            break;
        case 7:
            LCD_Clear(YELLOW);
            break;
        case 8:
            LCD_Clear(BRRED);
            break;
        case 9:
            LCD_Clear(GRAY);
            break;
        case 10:
            LCD_Clear(LGRAY);
            break;
        case 11:
            LCD_Clear(BROWN);
            break;
        }
        POINT_COLOR=RED;
        LCD_ShowString(30,40,210,24,24,(void*)"Explorer STM32F4");
        LCD_ShowString(30,70,200,16,16,(void*)"TFTLCD TEST");
        LCD_ShowString(30,90,200,16,16,(void*)"ATOM@ALIENTEK");
        LCD_ShowString(30,110,200,16,16,lcd_id);
        LCD_ShowString(30,130,200,12,12,(void*)"2014/5/4");
        x++;
        if(x==12)x=0;

        vTaskDelay(1000);
    }
}


static void AppTaskCreate(void)
{
    BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为 pdPASS */

    taskENTER_CRITICAL(); //进入临界区

    /* 创建 LED_Task 任务 */
    xReturn = xTaskCreate((TaskFunction_t )LED_Task, 			/* 任务入口函数 */
                          (const char* )"LED_Task",			/* 任务名字 */
                          (uint16_t )512, 					/* 任务栈大小 */
                          (void* )NULL, 						/* 任务入口函数参数 */
                          (UBaseType_t )2, 					/* 任务的优先级 */
                          (TaskHandle_t* )&LED_Task_Handle);	/* 任务控制块指针 */
    if (pdPASS == xReturn)
        printf("create LED_Task success!\r\n");

    /* 创建 LCD_Task 任务 */
    xReturn = xTaskCreate((TaskFunction_t )LCD_Task, 			/* 任务入口函数 */
                          (const char* )"LCD_Task",			/* 任务名字 */
                          (uint16_t )512, 					/* 任务栈大小 */
                          (void* )NULL, 						/* 任务入口函数参数 */
                          (UBaseType_t )2, 					/* 任务的优先级 */
                          (TaskHandle_t* )&LCD_Task_Handle);	/* 任务控制块指针 */
    if (pdPASS == xReturn)
        printf("create LCD_Task success!\r\n");

    vTaskDelete(AppTaskCreate_Handle); //删除 AppTaskCreate 任务

    taskEXIT_CRITICAL(); //退出临界区
}

