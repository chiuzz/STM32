#ifndef _TIMER_H
#define _TIMER_H

typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long int u32;

//-----------------------------------------------------------------------------
// 定时器16位特殊功能寄存器
//-----------------------------------------------------------------------------
sfr16 TMR2RL   = 0xca;                  // 定时器2数据寄存器地址
sfr16 TMR3RL   = 0x92;                  // 定时器3数据寄存器地址
sfr16 TMR2     = 0xcc;                 //  定时器2计数寄存器
sfr16 TMR3     = 0x94;                 //  定时器3计数寄存器
sfr16 DAC0     = 0x96;                 // 10位DAC寄存器地址
 
//-----------------------------------------------------------------------------
//常量赋值
//-----------------------------------------------------------------------------
#define SYSCLK       3062500//24500000 / 8         //  系统工作频率
#define SAMPLE_RATE  10000                //   3.9=<SAMPLE_RATE<=SYSCLK/12=255208，此时定时0.1ms中断一次
  
//------------------------------------------------------------------------------------
// 定义函数
//------------------------------------------------------------------------------------
//void Timer0_Init (int counts);
//void Timer1_Init (int counts);
void Timer2_Init (int counts);
void Timer3_Init (int counts);
//void Timer0_ISR (void);
//void Timer1_ISR (void);
//void Timer2_ISR (void);
//void Timer3_ISR (void);
void Low_alarm(void);   //低级报警
void Middle_alarm(void);//中级报警
void High_alarm(void);  //高级报警
void CAFAF(void);
void Up_Ctrl(void);	
void Level_Ctrl(void);
void Down_Ctrl(void);
#endif
