#ifndef __UART4_H
#define __UART4_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 

extern void uart4_init(u32 bound);
extern void Uart4SendData(uint8_t *pdata, uint8_t len);

#endif


