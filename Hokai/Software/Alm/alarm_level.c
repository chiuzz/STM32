#include"c8051f330.h"
#include"alarm_level.h"
#include"timer.h"
u8 level=3;	//�����������
u8 vol=2;	//������������
//-------------------------------------------------
//���������������������ź�����IO�ڳ�ʼ��
//-------------------------------------------------
void InputIO_Init(void)
{ 
   P1SKIP  |= Pin_0 + Pin_1 + Pin_2 + Pin_3 + Pin_4;          
   XBR1     = 0x40;  //���濪��ʹ�� 
}
//-------------------------------------------------
//���������ѯ
//-------------------------------------------------
void Warn_Check(void)
{
  
   if     (warn1==0 && warn2==0)
   	level=AlarmNomal;  //������
   else if(warn1==1 && warn2==0)
   	level=AlarmLLevel; //�ͼ�����
   else if(warn1==0 && warn2==1)
   	level=AlarmMLevel; //�м�����
   else                         
   	level=AlarmHLevel; //�߼�����
}
//-------------------------------------------------
//����������ѯ
//-------------------------------------------------
void Vol_Check(void)
{
   if(vol3)vol=Mute;                           //����
   else
   {
       if     (vol1==0 && vol2==0)
	   	vol=Volume0; //����Ϊ0
   	   else if(vol1==1 && vol2==0)
	   	vol=Volume1; //����
   	   else if(vol1==0 && vol2==1)
	   	vol=Volume2; //����
	   else 					  
	   	vol=Volume3; //����
   }
}