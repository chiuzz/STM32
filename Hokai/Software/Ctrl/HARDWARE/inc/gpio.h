#ifndef __GPIO_H
#define __GPIO_H
#include "sys.h"
#include "common.h"
//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//LED��������
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////

#define Read_CS              (GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_5 )==1)
#define Read_Din             (GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_7 )==1)

#define Dout_H       GPIO_SetBits  (GPIOC,GPIO_Pin_4);
#define Dout_L       GPIO_ResetBits(GPIOC,GPIO_Pin_4);


void Gpio_Init(void);//��ʼ��
void SetCpuLed(BOOLEAN sta);
void SetBump1Work(BOOLEAN sta);
void SetBump2Work(BOOLEAN sta);
void SetCoolerWork(BOOLEAN sta);
void SetHeaterWork(BOOLEAN sta);
void WWDOG(BOOLEAN sta); //���Ź�
//u8 GetButtomValue(void);
BOOLEAN GetHeatPower(void); //��ȡ220V״̬
BOOLEAN GetWaterSwitch1(void); //��ȡˮ������1״̬
BOOLEAN GetWaterSwitch2(void); //��ȡˮ������2״̬
BOOLEAN GetWaterLow(void);
BOOLEAN GetWaterFull(void);
#endif
