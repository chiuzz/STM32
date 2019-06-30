#include"c8051f330.h"
#include"led.h"
#include"alarm_level.h"
#include"timer.h"
u16 LED_cnt=0;
//-------------------------------------------------
//����ָʾ��IO�ڳ�ʼ��
//-------------------------------------------------
void Led_Init(void)
{ 
   P0SKIP  |= Pin_4 + Pin_6 + Pin_7; //��Ӧ�ı����濪������
}
//-------------------------------------------------
//������ָʾ�ƿ���
//-------------------------------------------------
void No_Led(void)
{
	 LED=1;							//�ͼ�����ָʾ����
	 MLED=1;						//�м�����ָʾ����
	 HLED=1;						//�߼�����ָʾ����
}
//-------------------------------------------------
//�ͼ�����ָʾ�ƿ���
//-------------------------------------------------
void Low_Led(void)
{
	 LED=0;					       //�ͼ�����ָʾ�Ƴ���
	 MLED=1;
	 HLED=1;
}
//-------------------------------------------------
//�м�����ָʾ�ƿ���
//-------------------------------------------------
void Mid_Led(void)
{
	LED=1;
	HLED=1;
	LED_cnt++;
	if(LED_cnt==1000)             //�м�����ָʾ����˸Ƶ��0.5Hz��ռ�ձ�50%
	{
		MLED=~MLED;
		LED_cnt=0;
	}
}
//-------------------------------------------------
//�߼�����ָʾ�ƿ���
//-------------------------------------------------
void High_Led(void)
{
	LED=1;
	MLED=1;
	LED_cnt++;
	if(LED_cnt>250)				  //�м�����ָʾ����˸Ƶ��2Hz��ռ�ձ�50%
	{
	    HLED=~HLED;	
		LED_cnt=0;
	}
}