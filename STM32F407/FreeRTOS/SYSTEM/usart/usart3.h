#ifndef __USART3_H
#define __USART3_H
#include "stdio.h"
#include "stm32f4xx_conf.h"
#include "sys.h"

void uart3_init(u32 bound);
void uart3_send(u8 *ch);
#endif


