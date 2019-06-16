#include "lcd.h"
#include "delay.h"
#include "sys.h" 
#define BIAS   0x4A           //0b1000 0100 1010  1/3duty 3com
#define SYSDIS 0X00           //0b1000 0000 0000  ����ϵͳ������LCDƫѹ������
#define SYSEN  0X02           //0b1000 0000 0010 ��ϵͳ ����
#define LCDOFF 0X04           //0b1000 0000 0100  ��LCDƫѹ
#define LCDON  0X06           //0b1000 0000 0110  ��LCDƫ ѹ
#define XTAL   0x28           //0b1000 0010 1000 �ⲿ��ʱ��
#define RC256  0X30           //0b1000 0011 0000  �ڲ�ʱ��RC256K
#define TONEON  0X12          //0b1000 0001 0010  ������ ���
#define TONEOFF 0X10          //0b1000 0001 0000 �ر��������
#define WDTDIS  0X0A        //0b1000 0000 1010  ��ֹ���Ź�
#define TONE_4K 0x80        //4k�������Ƶ��
#define TONE_2K 0xC0    
//�������ƣ�void Init_Ht1621(void)
//��������: HT1621-IO�ڳ�ʼ��
void Init_HT1621(void){
        
        RCC->APB2ENR|=1<<2;    //ʹ��PORTAʱ��
                                                          //JTAG���Ѿ���beep�����н�ֹ����
        GPIOA->CRH&=0XF0000FFF; 
        GPIOA->CRH|=0X03333000;//PD.3 2�������
        
        GPIOA->ODR|=15<<11;          
}
//�������ƣ�void Ht1621_Init(void)
//��������: HT1621��ʼ��
//˵ ������ʼ����Һ���������ֶξ���ʾ
//-----------------------------------------------------------------------------------------
void HT1621_Init(void){
         LCD_CS=1;//HT1621_CS=1;
         LCD_WR=1;//HT1621_WR=1;
         LCD_DATA=1;//HT1621_DAT=1;
         delay_ms(20); //��ʱʹLCD������ѹ�ȶ�
         HT1621WrCmd(BIAS);         //1/3ƫѹ ��3com��
         HT1621WrCmd(RC256); //ʹ���ڲ�����
         HT1621WrCmd(SYSDIS); //����ϵͳ������LCDƫѹ������
         HT1621WrCmd(WDTDIS); //���Ź���ֹ
         HT1621WrCmd(SYSEN);  //��ϵͳ ����
         HT1621WrCmd(LCDON);  //��LCDƫ ѹ
         delay_ms(20); //��ʱһ��ʱ��
         HT1621WrAllData(0xff);        //0x00 ���� 0xff��ʾ�����ֶ�
         delay_ms(1000); //��ʱһ��ʱ��
         delay_ms(1000); //��ʱһ��ʱ��
         HT1621WrAllData(0x00);        
}
//�������ƣ�Ht1621Wr_Data()
//�� �ܣ�д���ݺ���,cntΪ��������λ��,���ݴ���Ϊ��λ��ǰ
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
//�������ƣ�void Ht1621WrOneData(uchar Addr,uchar Data)
//��������: HT1621��ָ����ַд�����ݺ���
//����˵����AddrΪд���ʼ��ַ��DataΪд������
//˵ ������ΪHT1621������λ4λ������ʵ��д������Ϊ�����ĺ�4λ
//-----------------------------------------------------------------------------------------
void HT1621WrOneData(uchar Addr,uchar Data){

                 LCD_CS=0; 
                 delay_ms(1);
                 HT1621Wr_Data(0xa0,3); //д�����ݱ�־101
                 HT1621Wr_Data(Addr<<2,6); //д���ַ����
                 HT1621Wr_Data(Data<<4,4); //д������
                 LCD_CS=1;//
                 delay_ms(5);

}
//�������ƣ�void Ht1621WrOneNum(uchar Addr,uchar Num)
//��������: HT1621��ָ����ַд��һ�����֣�0-9������
//����˵����AddrΪд���ʼ��ַ��NumΪд������
//˵ ������ΪHT1621������λ4λ������ʵ��д������Ϊ�����ĺ�4λ
//-----------------------------------------------------------------------------------------
void HT1621WrOneNum(uchar Addr,uchar num){

     LCD_CS=0;//HT1621_CS=0;
     HT1621Wr_Data(0xa0,3); //д�����ݱ�־101
     HT1621Wr_Data(Addr<<2,6); //д���ַ����
     HT1621Wr_Data(num,8);//дһ��������������������д��������
     LCD_CS=1;//
         delay_ms(5);
}
//�������ƣ�void Ht1621WrAllData()
//��������: HT1621����д�뷽ʽ����  0x00 ���� 0xff��ʾ�����ֶ�
//˵ ����HT1621������λ4λ���˴�ÿ������Ϊ8λ��д������������8λ����
//-----------------------------------------------------------------------------------------
void HT1621WrAllData(u8 num){

         uchar i;
         LCD_CS=0;//
         HT1621Wr_Data(0xa0,3); //д�����ݱ�־101
         HT1621Wr_Data(0x00<<2,6); //д���ַ����
         for (i=0;i<16;i++)
         {
          HT1621Wr_Data(num,8);//0x00,8); //д������
         }
         LCD_CS=1;//
         delay_ms(5);
}
//�������ƣ�void Ht1621WrCmd(uchar Cmd)
//��������: HT1621����д�뺯��
//����˵����CmdΪд����������
//˵ ����д�������ʶλ100
//-----------------------------------------------------------------------------------------
void HT1621WrCmd(uchar Cmd){

         LCD_CS=0;//HT1621_CS=0;
         delay_ms(1);
         HT1621Wr_Data(0x80,4); //д�������־100
         HT1621Wr_Data(Cmd,8); //д����������
         LCD_CS=1;//HT1621_CS=1;
         delay_ms(5);
}

��h�ļ�
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

�������ʼ����ʾ���еĶ���

void HT1621_Init(void){
         LCD_CS=1;//HT1621_CS=1;
         LCD_WR=1;//HT1621_WR=1;
         LCD_DATA=1;//HT1621_DAT=1;
         delay_ms(20); //��ʱʹLCD������ѹ�ȶ�
         HT1621WrCmd(BIAS);         //1/3ƫѹ ��3com��
         HT1621WrCmd(RC256); //ʹ���ڲ�����
         HT1621WrCmd(SYSDIS); //����ϵͳ������LCDƫѹ������
         HT1621WrCmd(WDTDIS); //���Ź���ֹ
         HT1621WrCmd(SYSEN);  //��ϵͳ ����
         HT1621WrCmd(LCDON);  //��LCDƫ ѹ
         delay_ms(20); //��ʱһ��ʱ��
         HT1621WrAllData(0xff);        //0x00 ���� 0xff��ʾ�����ֶ�
         delay_ms(1000); //��ʱһ��ʱ��
         delay_ms(1000); //��ʱһ��ʱ��
         HT1621WrAllData(0x00);        
}