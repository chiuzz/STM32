#ifndef __USART2_H
#define __USART2_H
#include "stdio.h"
#include "stm32f4xx_conf.h"
#include "sys.h"

#define USART_REC_LEN2  			20
#define EN_USART2_RX 			1

extern u8  USART_RX_BUF2[USART_REC_LEN2]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з�
extern u16 USART_RX_STA2;         		//����״̬���
//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart2_init(u32 bound);
#endif


