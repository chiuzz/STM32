#ifndef _TIMER_H
#define _TIMER_H

typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long int u32;

//-----------------------------------------------------------------------------
// ��ʱ��16λ���⹦�ܼĴ���
//-----------------------------------------------------------------------------
sfr16 TMR2RL   = 0xca;                  // ��ʱ��2���ݼĴ�����ַ
sfr16 TMR3RL   = 0x92;                  // ��ʱ��3���ݼĴ�����ַ
sfr16 TMR2     = 0xcc;                 //  ��ʱ��2�����Ĵ���
sfr16 TMR3     = 0x94;                 //  ��ʱ��3�����Ĵ���
sfr16 DAC0     = 0x96;                 // 10λDAC�Ĵ�����ַ
 
//-----------------------------------------------------------------------------
//������ֵ
//-----------------------------------------------------------------------------
#define SYSCLK       3062500//24500000 / 8         //  ϵͳ����Ƶ��
#define SAMPLE_RATE  10000                //   3.9=<SAMPLE_RATE<=SYSCLK/12=255208����ʱ��ʱ0.1ms�ж�һ��
  
//------------------------------------------------------------------------------------
// ���庯��
//------------------------------------------------------------------------------------
//void Timer0_Init (int counts);
//void Timer1_Init (int counts);
void Timer2_Init (int counts);
void Timer3_Init (int counts);
//void Timer0_ISR (void);
//void Timer1_ISR (void);
//void Timer2_ISR (void);
//void Timer3_ISR (void);
void Low_alarm(void);   //�ͼ�����
void Middle_alarm(void);//�м�����
void High_alarm(void);  //�߼�����
void CAFAF(void);
void Up_Ctrl(void);	
void Level_Ctrl(void);
void Down_Ctrl(void);
#endif
