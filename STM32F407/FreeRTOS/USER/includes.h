#ifndef __INCLUDES_H_
#define __INCLUDES_H_

#include "stm32f4xx.h"

/*FreeRTOS 头文件*/
#include "FreeRTOS.h"
#include "task.h"

/*模块头文件*/
#include "usart.h"
#include "delay.h"
#include "sys.h"
#include "..\HARDWARE\led\led.h"
#include "..\HARDWARE\beep\beep.h"
#include "..\HARDWARE\key\key.h"
#include "..\HARDWARE\lcd\lcd.h"

#define TRUE  1
#define FALSE 0

#endif

