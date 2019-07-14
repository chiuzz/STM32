#ifndef __INCLUDES_H_
#define __INCLUDES_H_

#include "stm32f4xx.h"

typedef u8 BOOL;
#define TRUE  1
#define FALSE 0

/*FreeRTOS ͷ�ļ�*/
#include "FreeRTOS.h"
#include "task.h"

/*ģ��ͷ�ļ�*/
#include "usart2.h"
#include "usart3.h"
#include "delay.h"
#include "sys.h"
#include "..\USMART\usmart.h"
#include "..\ESP8266\common.h"
#include "..\Application\ModuleNetWork.h"

#include "..\HARDWARE\led\led.h"
#include "..\HARDWARE\beep\beep.h"
#include "..\HARDWARE\key\key.h"
#include "..\HARDWARE\lcd\lcd.h"

#include "string.h"

#endif

