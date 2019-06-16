/**
 * @file Target_Init.c
 * @brief
 * @author LGL
 * 0.010.1
 * @date 2015-05-04
 */

#include "Target_Init.h"
#include "malloc.h"
#include "exti.h"
#include "time.h"
//#include "LCD.h"
#include "adc.h"
#include "AT24C128.h"
void Target_Init(void)
{

    Gpio_Init();         //LED初始化
    //I2C_EE_Init();
    /* TIM3_PWM_Init(500-1, 48-1); */


    AT24CXX_Init();

//		TIM2Init();
//		EXTIX_Init();
    //lcd_init();
    Adc_Init();
//		LCD_IO_Init();
    my_mem_init(SRAMIN);
    //Dac_Init();
}
