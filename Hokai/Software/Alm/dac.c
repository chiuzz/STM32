#include"c8051f330.h"

//------------------------------------------------------------------------------------
// �˿ڳ�ʼ��
//------------------------------------------------------------------------------------

void DAC_PORT_Init (void)
{
   P0SKIP  |= 0x41;    //��Ӧ��P0.0/P0.6�����濪������    
   P0MDIN  &= ~0x01;   //P0.0Ӧ������Ϊģ�����벢�����ֽ��濪������       
   XBR1     = 0x40;    //���濪��ʹ��             
}

//-----------------------------------------------------------------------------
// ��ģת����ʼ��
//-----------------------------------------------------------------------------
void DAC0_Init (void)
{
   DAC_PORT_Init();     //IDAC��IO�ڳ�ʼ��
   IDA0CN = 0xb2;       //����Ϊ0x82,0x92,0xa2,0xb2ʱ�ֱ����ö�ʱ��0��1��2��3�������ΪIDAC�ĸ������           
   REF0CN = 0x03;       //�ο���ѹѡ��           
}

//-----------------------------------------------------------------------------
// �ⲿ����ת������
//-----------------------------------------------------------------------------
/*
void DAC0_CNVS_DAC0h(void)
{
    IDA0H=i;
   i=i+16;
   if(i==0xffff)
   {
   i=0;}
} */