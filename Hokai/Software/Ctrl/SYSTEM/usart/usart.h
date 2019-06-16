#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 

#define USART_R_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
	  	
extern u8 USART_RBUF[USART_R_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
extern u16 USART_RFlag;       //接收状态标记	
void uart_init(u32 bound);
void Usart1SendData(uint8_t *pdata, uint8_t len);
#endif


