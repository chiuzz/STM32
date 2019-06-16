#include "lcd.h"
#include "delay.h"
#include "sys.h" 
#define BIAS   0x4A           //0b1000 0100 1010  1/3duty 3com
#define SYSDIS 0X00           //0b1000 0000 0000  关振系统荡器和LCD偏压发生器
#define SYSEN  0X02           //0b1000 0000 0010 打开系统 振荡器
#define LCDOFF 0X04           //0b1000 0000 0100  关LCD偏压
#define LCDON  0X06           //0b1000 0000 0110  打开LCD偏 压
#define XTAL   0x28           //0b1000 0010 1000 外部接时钟
#define RC256  0X30           //0b1000 0011 0000  内部时钟RC256K
#define TONEON  0X12          //0b1000 0001 0010  打开声音 输出
#define TONEOFF 0X10          //0b1000 0001 0000 关闭声音输出
#define WDTDIS  0X0A        //0b1000 0000 1010  禁止看门狗
#define TONE_4K 0x80        //4k声音输出频率
#define TONE_2K 0xC0    
//函数名称：void Init_Ht1621(void)
//功能描述: HT1621-IO口初始化
void Init_HT1621(void){
        
        RCC->APB2ENR|=1<<2;    //使能PORTA时钟
                                                          //JTAG口已经在beep配置中禁止掉了
        GPIOA->CRH&=0XF0000FFF; 
        GPIOA->CRH|=0X03333000;//PD.3 2推挽输出
        
        GPIOA->ODR|=15<<11;          
}
//函数名称：void Ht1621_Init(void)
//功能描述: HT1621初始化
//说 明：初始化后，液晶屏所有字段均显示
//-----------------------------------------------------------------------------------------
void HT1621_Init(void){
         LCD_CS=1;//HT1621_CS=1;
         LCD_WR=1;//HT1621_WR=1;
         LCD_DATA=1;//HT1621_DAT=1;
         delay_ms(20); //延时使LCD工作电压稳定
         HT1621WrCmd(BIAS);         //1/3偏压 开3com口
         HT1621WrCmd(RC256); //使用内部振荡器
         HT1621WrCmd(SYSDIS); //关振系统荡器和LCD偏压发生器
         HT1621WrCmd(WDTDIS); //看门狗禁止
         HT1621WrCmd(SYSEN);  //打开系统 振荡器
         HT1621WrCmd(LCDON);  //打开LCD偏 压
         delay_ms(20); //延时一段时间
         HT1621WrAllData(0xff);        //0x00 清屏 0xff显示所有字段
         delay_ms(1000); //延时一段时间
         delay_ms(1000); //延时一段时间
         HT1621WrAllData(0x00);        
}
//函数名称：Ht1621Wr_Data()
//功 能：写数据函数,cnt为传送数据位数,数据传送为低位在前
void HT1621Wr_Data(uchar dat ,uchar dat1) {
           uchar i; 
           for(i =0; i <dat1; i ++)
           {
                     if((dat&0x80)==0)
                           LCD_DATA=0;
                         else 
                         LCD_DATA=1;
        
                         LCD_WR=0;
                         delay_ms(1);
                         LCD_WR=1;
                         dat<<=1;
           }
           delay_ms(5);
          
}
//函数名称：void Ht1621WrOneData(uchar Addr,uchar Data)
//功能描述: HT1621在指定地址写入数据函数
//参数说明：Addr为写入初始地址，Data为写入数据
//说 明：因为HT1621的数据位4位，所以实际写入数据为参数的后4位
//-----------------------------------------------------------------------------------------
void HT1621WrOneData(uchar Addr,uchar Data){

                 LCD_CS=0; 
                 delay_ms(1);
                 HT1621Wr_Data(0xa0,3); //写入数据标志101
                 HT1621Wr_Data(Addr<<2,6); //写入地址数据
                 HT1621Wr_Data(Data<<4,4); //写入数据
                 LCD_CS=1;//
                 delay_ms(5);

}
//函数名称：void Ht1621WrOneNum(uchar Addr,uchar Num)
//功能描述: HT1621在指定地址写入一个数字（0-9）函数
//参数说明：Addr为写入初始地址，Num为写入数据
//说 明：因为HT1621的数据位4位，所以实际写入数据为参数的后4位
//-----------------------------------------------------------------------------------------
void HT1621WrOneNum(uchar Addr,uchar num){

     LCD_CS=0;//HT1621_CS=0;
     HT1621Wr_Data(0xa0,3); //写入数据标志101
     HT1621Wr_Data(Addr<<2,6); //写入地址数据
     HT1621Wr_Data(num,8);//写一个完整的数。就是连续写两个数。
     LCD_CS=1;//
         delay_ms(5);
}
//函数名称：void Ht1621WrAllData()
//功能描述: HT1621连续写入方式函数  0x00 清屏 0xff显示所有字段
//说 明：HT1621的数据位4位，此处每次数据为8位，写入数据总数按8位计算
//-----------------------------------------------------------------------------------------
void HT1621WrAllData(u8 num){

         uchar i;
         LCD_CS=0;//
         HT1621Wr_Data(0xa0,3); //写入数据标志101
         HT1621Wr_Data(0x00<<2,6); //写入地址数据
         for (i=0;i<16;i++)
         {
          HT1621Wr_Data(num,8);//0x00,8); //写入数据
         }
         LCD_CS=1;//
         delay_ms(5);
}
//函数名称：void Ht1621WrCmd(uchar Cmd)
//功能描述: HT1621命令写入函数
//参数说明：Cmd为写入命令数据
//说 明：写入命令标识位100
//-----------------------------------------------------------------------------------------
void HT1621WrCmd(uchar Cmd){

         LCD_CS=0;//HT1621_CS=0;
         delay_ms(1);
         HT1621Wr_Data(0x80,4); //写入命令标志100
         HT1621Wr_Data(Cmd,8); //写入命令数据
         LCD_CS=1;//HT1621_CS=1;
         delay_ms(5);
}

。h文件
#ifndef __LCD_H
#define __LCD_H        
#include "sys.h"
#define uint       unsigned int
#define uchar      unsigned char

#define LCD_CS    PAout(11)  
#define LCD_RD    PAout(12)        
#define LCD_WR    PAout(13)        
#define LCD_DATA  PAout(14)  
void Init_HT1621(void);
void HT1621_Init(void);
void HT1621Wr_Data(uchar dat ,uchar dat1) ;
void HT1621WrOneData(uchar Addr,uchar Data);
void HT1621WrOneNum(uchar Addr,uchar num);
void HT1621WrAllData(u8 num);
void HT1621WrCmd(uchar Cmd);
#endif

主程序初始化显示所有的段码

void HT1621_Init(void){
         LCD_CS=1;//HT1621_CS=1;
         LCD_WR=1;//HT1621_WR=1;
         LCD_DATA=1;//HT1621_DAT=1;
         delay_ms(20); //延时使LCD工作电压稳定
         HT1621WrCmd(BIAS);         //1/3偏压 开3com口
         HT1621WrCmd(RC256); //使用内部振荡器
         HT1621WrCmd(SYSDIS); //关振系统荡器和LCD偏压发生器
         HT1621WrCmd(WDTDIS); //看门狗禁止
         HT1621WrCmd(SYSEN);  //打开系统 振荡器
         HT1621WrCmd(LCDON);  //打开LCD偏 压
         delay_ms(20); //延时一段时间
         HT1621WrAllData(0xff);        //0x00 清屏 0xff显示所有字段
         delay_ms(1000); //延时一段时间
         delay_ms(1000); //延时一段时间
         HT1621WrAllData(0x00);        
}