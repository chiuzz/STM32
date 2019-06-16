#include "gpio.h"
//LED IO初始化
void Gpio_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 	//使能时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ;              //PD9 行扫描输出
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;           //输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;          //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;            //接上拉
    GPIO_Init(GPIOD, &GPIO_InitStructure); 									//使能IO
    GPIO_ResetBits(GPIOD, GPIO_Pin_9);

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;						 //输入模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;        //PE2 系统闪烁LED
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;						 //输出模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;						 //接上拉
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    GPIO_SetBits(GPIOE, GPIO_Pin_2);
    GPIO_ResetBits(GPIOE, GPIO_Pin_9);
    GPIO_ResetBits(GPIOE, GPIO_Pin_10);
    GPIO_ResetBits(GPIOE, GPIO_Pin_11);
    GPIO_ResetBits(GPIOE, GPIO_Pin_12);

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8;               //PE2 系统闪烁LED
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;						 //输出模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;						 //输出模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /////开门狗
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;                //
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;						 //输出模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    GPIO_SetBits(GPIOE, GPIO_Pin_4);
    GPIO_ResetBits(GPIOE, GPIO_Pin_4);
}

void SetCpuLed ( BOOLEAN sta )
{
    if(sta)
        GPIO_ResetBits(GPIOE, GPIO_Pin_2);
    else
        GPIO_SetBits(GPIOE, GPIO_Pin_2);
}

void SetBump1Work(BOOLEAN sta)
{
    if(sta)
        GPIO_SetBits(GPIOE, GPIO_Pin_12);
    else
        GPIO_ResetBits(GPIOE, GPIO_Pin_12);
}
void SetBump2Work(BOOLEAN sta)
{
    if(sta)
        GPIO_SetBits(GPIOE, GPIO_Pin_11);
    else
        GPIO_ResetBits(GPIOE, GPIO_Pin_11);
}

void SetCoolerWork(BOOLEAN sta)
{
//	PD(sta);
    if(sta)
        GPIO_SetBits(GPIOE, GPIO_Pin_9);
    else
        GPIO_ResetBits(GPIOE, GPIO_Pin_9);
}
void SetHeaterWork(BOOLEAN sta)
{
    if(sta)
        GPIO_SetBits(GPIOE, GPIO_Pin_10);
    else
        GPIO_ResetBits(GPIOE, GPIO_Pin_10);
}

BOOLEAN GetHeatPower() //获取220V状态
{
    BOOLEAN ret = TRUE;
    //获取IO电平
//	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)==TRUE)
//		ret = TRUE;
    if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == FALSE)
        ret = FALSE;
    return ret;
}

BOOLEAN GetWaterLow() //获取低水位状态
{
    BOOLEAN ret = TRUE;
    //获取IO电平
    if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_7) == TRUE)
        ret = FALSE;
//	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==FALSE)
//	ret = FALSE;
    return ret;
}
BOOLEAN GetWaterFull() //获取满水位状态
{
    BOOLEAN ret = TRUE;
    //获取IO电平
    if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_8) == TRUE)
        ret = FALSE;
//	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==FALSE)
//	ret = FALSE;
    return ret;
}

void WWDOG(BOOLEAN sta)
{
    if(sta)
        GPIO_SetBits(GPIOE, GPIO_Pin_4);
    else
        GPIO_ResetBits(GPIOE, GPIO_Pin_4);
}

BOOLEAN GetWaterSwitch1() //获取水流开关1状态
{
    BOOLEAN ret = TRUE;
    //获取IO电平
    if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15) == TRUE)
        ret = FALSE;
    return ret;
}

BOOLEAN GetWaterSwitch2() //获取水流开关2状态
{
    BOOLEAN ret = TRUE;
    //获取IO电平
    if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_8)==TRUE)
        ret = FALSE;
    return ret;
}

