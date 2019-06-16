#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 

#define USART_R_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern u8 USART_RBUF[USART_R_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
extern u16 USART_RFlag;       //����״̬���	
void uart_init(u32 bound);
void Usart1SendData(uint8_t *pdata, uint8_t len);
#endif


