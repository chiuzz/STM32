#ifndef __USART3_H
#define __USART3_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 

#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define USART_R_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
// extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
// extern u16 USART_RX_STA;         		//����״̬���	
//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart3_init(u32 bound);
void Usart3SendData(uint8_t *pdata, uint8_t len);
u16 GetSpeend(void);
extern u8 USART_RBUF[USART_R_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
extern u16 USART_RFlag;       //����״̬���	
#endif


