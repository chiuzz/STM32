/**
  ******************************************************************************
  * @file
  * @author
  * @version
  * @date
  * @brief
  ******************************************************************************
  * @attention
  *
  *
  *
  *
  ******************************************************************************
  */
#ifndef __USART_H
#define	__USART_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>
#include "common.h"
#include "ModuleUart.h"


#define SENDBUFF_SIZE 20

void uart3_init(u32 bound);
void USART3_Config(void);
void DMA_UART_Config(int len);
static void NVIC_Config(void);


extern void USART3_INIT(void);
void Usart3SendData(uint8_t *pdata, uint8_t len);




#endif

