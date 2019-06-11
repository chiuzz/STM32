#ifndef __USART2_H
#define __USART2_H
#include "stdio.h"
#include "stm32f4xx_conf.h"
#include "sys.h"

#define USART_REC_LEN2  			20
#define EN_USART2_RX 			1

extern u8  USART_RX_BUF2[USART_REC_LEN2]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
extern u16 USART_RX_STA2;         		//接收状态标记
//如果想串口中断接收，请不要注释以下宏定义
void uart2_init(u32 bound);
#endif


