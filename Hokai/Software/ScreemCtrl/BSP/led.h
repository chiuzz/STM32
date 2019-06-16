#ifndef __LED_H
#define	__LED_H

#include "stm32f10x.h"

/* the macro definition to trigger the led on or off 
 * 1 - off
 - 0 - on
 */
#define ON  0
#define OFF 1

#define LED(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_13);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_13)

// #define LED2(a)	if (a)	\
// 					GPIO_SetBits(GPIOC,GPIO_Pin_4);\
// 					else		\
// 					GPIO_ResetBits(GPIOC,GPIO_Pin_4)

// #define LED3(a)	if (a)	\
// 					GPIO_SetBits(GPIOC,GPIO_Pin_5);\
// 					else		\
// 					GPIO_ResetBits(GPIOC,GPIO_Pin_5)

#define Buzze(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_8);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_8);						
					
	
bool GetKey0Sta();
bool GetKey1Sta();
bool GetKey2Sta();
bool GetKey3Sta();
bool GetKey4Sta();
bool GetKey5Sta();
bool GetKey6Sta();
bool GetKey7Sta();				
void LED_GPIO_Config(void);
u8 GetButtomValue();
void SetAlarmLevel(u8 index);
void SetAlarmVolum(u8 index);
					//下面是根据我的测试板情况定义的，用户可以需要修改 
//主要就是使用了显示屏的三个功能引脚

#define LCDCS1_LOW     {GPIO_ResetBits(GPIOB,GPIO_Pin_15);} 
#define LCDCS1_HIGH    {GPIO_SetBits(GPIOB,GPIO_Pin_15);}

#define LCDCS2_LOW     {GPIO_ResetBits(GPIOB,GPIO_Pin_14);} 
#define LCDCS2_HIGH    {GPIO_SetBits(GPIOB,GPIO_Pin_14);}

#define LCDWR_LOW      {GPIO_ResetBits(GPIOB,GPIO_Pin_12);}  		
#define LCDWR_HIGH     {GPIO_SetBits(GPIOB,GPIO_Pin_12);}  

#define LCDDATA_LOW    {GPIO_ResetBits(GPIOB,GPIO_Pin_13);} 	      
#define LCDDATA_HIGH   {GPIO_SetBits(GPIOB,GPIO_Pin_13); }
#define IC1_PIN   1          //显示屏的pin1
#define IC2_PIN   2         //显示屏的pin2

void HT1621WrCmd(u8 Cmd ,u8 WhichCS);
void HT1621Wr_Data(u8 dat ,u8 dat_lengh);
void HT1621WrOneData(u8 Addr,u8 Data ,u8 WhichIC);
void LCD_IO_Init(void);

void HT1621B_Init(void); 

void BuzzeOn();
void BuzzeOff();

void disp_all();
void disp_clear();
void HT1621B_InitiIC1(void);
void delay_us(u32 i);	
void delay_ms(u32 i);
void delay_1us(void);
					
					
#endif /* __LED_H */
