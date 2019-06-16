#ifndef __USART5_H
#define __USART5_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 

//如果想串口中断接收，请不要注释以下宏定义


#define pagedataLen_TX 8
#define pagedataLen_RX 10
#define MSG_DataLen_RX 15

extern 	u8 USART5_TxBuffer[pagedataLen_TX];	
extern 	u8 USART5_RxBuffer[pagedataLen_RX];	
extern 	u8 MSG_RxBuffer[MSG_DataLen_RX];		


extern 	u8 MSG_RX_START_FLAG;	
extern 	u8 MSG_RX_END_FLAG;		
extern 	u8 MSG_Rx_CNT;			 
extern 	u8 USART5_Rx;			  	
extern 	u8 USART5_RX_Flag;	 
extern 	u8 USART5_TX_Flag;	  

void uart5_init(u32 bound);
void Uart5SendData(uint8_t *pdata, uint8_t len);

#endif


