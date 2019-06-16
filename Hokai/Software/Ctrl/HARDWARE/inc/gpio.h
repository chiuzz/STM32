#ifndef __GPIO_H
#define __GPIO_H
#include "sys.h"
#include "common.h"
//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//LED驱动代码
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////

#define Read_CS              (GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_5 )==1)
#define Read_Din             (GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_7 )==1)

#define Dout_H       GPIO_SetBits  (GPIOC,GPIO_Pin_4);
#define Dout_L       GPIO_ResetBits(GPIOC,GPIO_Pin_4);


void Gpio_Init(void);//初始化
void SetCpuLed(BOOLEAN sta);
void SetBump1Work(BOOLEAN sta);
void SetBump2Work(BOOLEAN sta);
void SetCoolerWork(BOOLEAN sta);
void SetHeaterWork(BOOLEAN sta);
void WWDOG(BOOLEAN sta); //看门狗
//u8 GetButtomValue(void);
BOOLEAN GetHeatPower(void); //获取220V状态
BOOLEAN GetWaterSwitch1(void); //获取水流开关1状态
BOOLEAN GetWaterSwitch2(void); //获取水流开关2状态
BOOLEAN GetWaterLow(void);
BOOLEAN GetWaterFull(void);
#endif
