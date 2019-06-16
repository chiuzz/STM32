#ifndef _LCD_H

#define _LCD_H	
#include "sys.h" 

#define IC1_PIN   1          //��ʾ����pin1
#define IC2_PIN   2         //��ʾ����pin2
#define BIAS   0x52           //0b1000 0101 0010  1/3duty 4com
#define SYSDIS 0X00           //0b1000 0000 0000  �ر�ϵͳ������LCDƫѹ������
#define SYSEN  0X02           //0b1000 0000 0010 ��ϵͳ����
#define LCDOFF 0X04           //0b1000 0000 0100  ?LCD??
#define LCDON  0X06           //0b1000 0000 0110  ??LCD? ?
#define XTAL   0x28           //0b1000 0010 1000 ?????
#define RC256  0X30           //0b1000 0011 0000  �ڲ�ʱ��RC256K
#define TONEON  0X12          //0b1000 0001 0010  ������
#define TONEOFF 0X10          //0b1000 0001 0000 �ر�����
#define WDTDIS  0X0A        //0b1000 0000 1010  ��ֹ���Ź�
#define TONE_4K 0x80        //4k??????
#define TONE_2K 0xC0 



//�����Ǹ����ҵĲ��԰��������ģ��û�������Ҫ�޸� 
//��Ҫ����ʹ������ʾ����������������

#define LCDCS1_LOW     {GPIO_ResetBits(GPIOD,GPIO_Pin_14);} 
#define LCDCS1_HIGH    {GPIO_SetBits(GPIOD,GPIO_Pin_14);}

#define LCDCS2_LOW     {GPIO_ResetBits(GPIOD,GPIO_Pin_15);} 
#define LCDCS2_HIGH    {GPIO_SetBits(GPIOD,GPIO_Pin_15);}

#define LCDWR_LOW      {GPIO_ResetBits(GPIOD,GPIO_Pin_13);}  		
#define LCDWR_HIGH     {GPIO_SetBits(GPIOD,GPIO_Pin_13);}  

#define LCDDATA_LOW    {GPIO_ResetBits(GPIOD,GPIO_Pin_12);} 	      
#define LCDDATA_HIGH   {GPIO_SetBits(GPIOD,GPIO_Pin_12); }


void HT1621WrCmd(u8 Cmd ,u8 WhichCS);
void HT1621Wr_Data(u8 dat ,u8 dat_lengh);
void HT1621WrOneData(u8 Addr,u8 Data ,u8 WhichIC);
void LCD_IO_Init(void);

void HT1621B_Init(void); 

void BuzzeOn(void);
void BuzzeOff(void);

void disp_all(void);
void disp_clear(void);
void HT1621B_InitiIC1(void);
#endif
