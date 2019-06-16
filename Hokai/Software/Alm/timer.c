#include <stdio.h>
#include"c8051f330.h"
#include"timer.h"
#include"alarm_level.h"
#include"led.h"
extern u8 level;    //�����������
extern u8 vol;	    //������������
extern u16 LED_cnt;	//��������������LED��˸Ƶ��
//-----------------------------------------------------------------------------
//  ��ʱ��2��ʼ��
//-----------------------------------------------------------------------------
void Timer2_Init (int counts)
{
    TMR2CN = 0x00;//��ʱ��2������16λ�Զ���װ�ط�ʽ                                                                                           
    CKCON |= 0x30; //��ʱ��2������ϵͳʱ��                  
    TMR2RL  = -counts;                  
    TMR2    = TMR2RL;                  
    ET2= 1;                         
    TR2=1;                     

}

//-----------------------------------------------------------------------------
//  ��ʱ��3��ʼ��
//-----------------------------------------------------------------------------
void Timer3_Init (int counts)
{
   TMR3CN = 0x00; //��ʱ��3������16λ�Զ���װ�ط�ʽ                                  
   CKCON |= 0xc0;  //��ʱ��3������ϵͳʱ��             
   TMR3RL  = -counts;               
   TMR3    = TMR3RL;                  
   EIE1 |= 0x80;    //�ж�����                  
   TMR3CN |= 0x04; //���־λ������TMR3               

}

//-----------------------------------------------------------------------------
//  ��ʱ��2�жϷ�������������������LED��˸
//-----------------------------------------------------------------------------
void Timer2_ISR (void) interrupt 5
{
   TMR2CN &= ~0x80;                             
   switch(level)                     //�жϱ�������
   {  
       case AlarmLLevel:			 //�ͼ�����
	          Low_Led();
	          break;
       case AlarmMLevel:			 //�м�����
	          Mid_Led();
			  break;
       case AlarmHLevel:			 //�߼�����
	          High_Led();
			  break;
	   case AlarmNomal:			     //������
	          No_Led();
			  break;
	   default:
	          break;
   }
}

//-----------------------------------------------------------------------------
//  ��ʱ��3�ж�
//-----------------------------------------------------------------------------
//��������
#define C_Freq 19  //C��Ƶ�ʿ��Ƴ��� f0=1/(19*2*100us)=263Hz
#define D_Freq 17  //D��Ƶ�ʿ��Ƴ���
#define E_Freq 15  //E��Ƶ�ʿ��Ƴ���
#define F_Freq 14  //F��Ƶ�ʿ��Ƴ���
#define G_Freq 13  //G��Ƶ�ʿ��Ƴ���
#define A_Freq 11  //A��Ƶ�ʿ��Ƴ���
#define B_Freq 10  //B��Ƶ�ʿ��Ƴ���
//
//sbit LED =P0^6;
//
u8 T0Count=0,T1Count=0,T2Count=0;//����Ƶ��f0���Ʊ���
u16 DAC_VALUE_MAX=388<<6;        //DACת�����ֵΪDAC_VALUE_MAX
u16 DAC_Min=130<<6;				 //С�����������DACֵ
u16 DAC_Mid=220<<6;				 //�������������DACֵ
u16 DAC_Max=388<<6;				 //�������������DACֵ
u16 CNT=0;                       //�߼���������cafafʱ����Ʊ���
u32 Tcount=0;                    //ȫ��ʱ����Ʊ���
//
u8 up_flag=1;                    //�л�����DACת����־����
u8 i=0;							 //��ѯup_down[]�������
u8 _i=0;						 //����i��С����
u8 __i=0;                        //����i��С����
u16 code up_down[40]={
0,0,0,0,0,0,0,0,0,0,												 //����Ϊ0
13<<6,26<<6,39<<6,52<<6,65<<6,78<<6,91<<6,104<<6,117<<6,130<<6,	     //С����
22<<6,44<<6,66<<6,88<<6,110<<6,132<<6,154<<6,176<<6,198<<6,220<<6,   //������
40<<6,80<<6,120<<6,160<<6,200<<6,240<<6,280<<6,320<<6,360<<6,388<<6  //������
};//�����أ��½���DACת��ֵ,code��������Ĵ洢λ���ǳ���洢����ֻ����

//�жϷ�����
void Timer3_ISR (void) interrupt 14
{    
   Warn_Check();                      //��ѯ�������� 
   Vol_Check();						  //��ѯ��������
   switch(vol)						  //�ж���������
   {
       case 0:						          //����Ϊ0 �� ����
	          DAC_VALUE_MAX=0;
	          break;
	   case Volume1:						  //С����
	          DAC_VALUE_MAX=DAC_Min;
	          break;
       case Volume2:						  //������
	          DAC_VALUE_MAX=DAC_Mid;
			  break;
       case Volume3:						  //������
	          DAC_VALUE_MAX=DAC_Max;
			  break;
	   default:
	          break;
   }
   _i=vol*10;                        //����õ�_i ��ѯup_down[40]����ļ��㹫ʽ
   __i=_i+9;                         //����õ�__i
   switch(level)					 //�жϱ�������
   {  
       case AlarmLLevel:						 //�ͼ�����
	          Low_alarm();
	          break;
       case AlarmMLevel:						 //�м�����
	          Middle_alarm();
			  break;
       case AlarmHLevel:						 //�߼�����
	          High_alarm();
			  break;
	   case AlarmNomal:
	          DAC0=0;                //������
	          Tcount=1;
	          T0Count=0;
	          T1Count=0;
	          T2Count=0;
			  break;
	   default:
	          break;
   }
//   LED =~LED; //������Զ�ʱ����ʱ�Ƿ�׼ȷ
   TMR3CN &= ~0x80;//����жϱ�־
}
//============================================================================================
//�ͼ�����
//============================================================================================
void Low_alarm(void)
{
	Tcount++;
	if(Tcount>=156401)//�ͼ���������Ϊ15.64s
	{
		Tcount=1;
		T0Count=0;
		T1Count=0;
		T2Count=0;
		i=_i;
	}
	
	if(Tcount<=200)//E��������20ms
	{
		T0Count++;
		if(T0Count==E_Freq)
		{
		    T0Count=0;
			Up_Ctrl();
		} 
	}
	else if(Tcount<=2200)//tdʱ���
	{  
		T1Count++;
		if(T1Count==E_Freq)
		{
		    T1Count=0;
			Level_Ctrl();
		} 
		i=__i;  
	}
	if(2200<Tcount && Tcount<=2400)//E���½���
	{
		T2Count++;
		if(T2Count==E_Freq)
		{
		    T2Count=0;
			Down_Ctrl();
		}
	}
	if(2401==Tcount)//E����C����Ъʱ���200ms
	{
		DAC0=0;
		T0Count=0;
		T1Count=0;
		T2Count=0;
		i=_i;
	}
	if(4000<Tcount && Tcount<=4200)//C��������
	{
		T0Count++;
		if(T0Count==C_Freq)
		{
		    T0Count=0;
			Up_Ctrl();
		}
	}
	if(4200<Tcount && Tcount<=6200)//tdʱ���
	{  
		T1Count++;
		if(T1Count==C_Freq)
		{
		    T1Count=0;
			Level_Ctrl();
		} 
		i=__i;  
	}
	if(6200<Tcount && Tcount<=6400)//�½���
	{
		T2Count++;
		if(T2Count==C_Freq)
		{
		    T2Count=0;
			Down_Ctrl();
		}
	}
	if(6401==Tcount)//tb=15s
	{
		DAC0=0;
	}
   	
}
//============================================================================================
//�м�����
//============================================================================================
void Middle_alarm(void)
{
	Tcount++;
	if(Tcount>=60401)//�м���������Ϊ6.04s
	{
		Tcount=1;
		T0Count=0;
		T1Count=0;
		T2Count=0;
		i=_i;
	}
	
	if(Tcount<=200)//C��������20ms
	{
		T0Count++;
		if(T0Count==C_Freq)
		{
		    T0Count=0;
			Up_Ctrl();
		} 
	}
	if(200<Tcount && Tcount<=2200)//tdʱ���
	{  
		T1Count++;
		if(T1Count==C_Freq)
		{
		    T1Count=0;
			Level_Ctrl();
		} 
		i=__i;  
	}
	if(2200<Tcount && Tcount<=2400)//C���½���
	{
		T2Count++;
		if(T2Count==C_Freq)
		{
		    T2Count=0;
			Down_Ctrl();
		}
	}
	if(2401==Tcount)//C����A����Ъʱ���200ms
	{
		DAC0=0;
		T0Count=0;
		T1Count=0;
		T2Count=0;
		i=_i;
	}
	if(4000<Tcount && Tcount<=4200)//A��������
	{
		T0Count++;
		if(T0Count==A_Freq)
		{
		    T0Count=0;
		    Up_Ctrl();	 
		}
	}
	if(4200<Tcount && Tcount<=6200)//tdʱ���
	{  
		T1Count++;
		if(T1Count==A_Freq)
		{
		    T1Count=0;
			Level_Ctrl();
		} 
		i=__i;  
	}
	if(6200<Tcount && Tcount<=6400)//�½���
	{
		T2Count++;
		if(T2Count==A_Freq)
		{
		    T2Count=0;
			Down_Ctrl();
		}
	}
	if(6401==Tcount)//A����F����Ъʱ���200ms
	{
		DAC0=0;
		T0Count=0;
		T1Count=0;
		T2Count=0;
		i=_i;
	}
	if(8000<Tcount && Tcount<=8200)//F��������
	{
		T0Count++;
		if(T0Count==F_Freq)
		{
		    T0Count=0;
			Up_Ctrl();
		}
	}
	if(8200<Tcount && Tcount<=10200)//tdʱ���
	{  
		T1Count++;
		if(T1Count==F_Freq)
		{
		    T1Count=0;
			Level_Ctrl();
		}  
		i=__i; 
	}
	if(10200<Tcount && Tcount<=10400)//�½���
	{
		T2Count++;
		if(T2Count==F_Freq)
		{
		    T2Count=0;
			Down_Ctrl();
		}
	}
	if(10401==Tcount)//tb=5s
	{
		DAC0=0;
	}
}
//============================================================================================
//�߼�����
//============================================================================================
//
void High_alarm(void)
{	
	Tcount++;
	if(Tcount>=66801)//�м���������Ϊ6.68s
	{
		Tcount=1;
		T0Count=0;
		T1Count=0;
		T2Count=0;
		CNT=0;
		i=_i;
	}
	if(0<Tcount && Tcount<=14400)
	{
	    CAFAF();

	}
	if(14401==Tcount)
	{
		DAC0=0;
		T0Count=0;
		T1Count=0;
		T2Count=0;
		CNT=0;
		i=_i;
	}
	if(22400<Tcount && Tcount<=36800)
	{
	    CAFAF();

	} 
	if(36801==Tcount)
	{
		 DAC0=0;
	}  
}
//-------------------------------------------------------------------------
//���� c a f a f ���ƺ��� 
//-------------------------------------------------------------------------
//
void CAFAF(void)
{
	CNT++;	
	//C	
	if(CNT<=200)//C��������20ms
	{
		T0Count++;
		if(T0Count==C_Freq)
		{
		    T0Count=0;
			Up_Ctrl();
		} 
	} 
	if(200<CNT && CNT<=1700)//tdʱ���
	{  
		T1Count++;
		if(T1Count==C_Freq)
		{
		    T1Count=0;
			Level_Ctrl();  
		}  
		i=__i;
	}
	if(1700<CNT && CNT<=1900)//C���½���
	{
		T2Count++;
		if(T2Count==C_Freq)
		{
		    T2Count=0;
			Down_Ctrl(); 
		}
	} 
	if(1901==CNT)//C����A����Ъʱ���200ms
	{
		DAC0=0;
		T0Count=0;
		T1Count=0;
		T2Count=0;
		i=_i;
	} 
	//A	
	if(2500<CNT && CNT<=2700)//A��������
	{
		T0Count++;
		if(T0Count==A_Freq)
		{
		    T0Count=0;
			Up_Ctrl();
		}
	}
	if(2700<CNT && CNT<=4200)//tdʱ���
	{  
		T1Count++;
		if(T1Count==A_Freq)
		{
		    T1Count=0;
			Level_Ctrl();
		} 
		i=__i; 
	}
	if(4200<CNT && CNT<=4400)//�½���
	{
		T2Count++;
		if(T2Count==A_Freq)
		{
		    T2Count=0;
			Down_Ctrl();
		}
	}
	if(4401==CNT)//A����F����Ъʱ���200ms
	{
		DAC0=0;
		T0Count=0;
		T1Count=0;
		T2Count=0;
		i=_i; 
	}
	//F
	if(5000<CNT && CNT<=5200)//F��������
	{
		T0Count++;
		if(T0Count==F_Freq)
		{
		    T0Count=0;
			Up_Ctrl();
		}
	}
	if(5200<CNT && CNT<=6700)//tdʱ���
	{  
		T1Count++;
		if(T1Count==F_Freq)
		{
		    T1Count=0;
            Level_Ctrl();
		} 
		i=__i;  
	}
	if(6700<CNT && CNT<=6900)//�½���
	{
		T2Count++;
		if(T2Count==F_Freq)
		{
		    T2Count=0;
			Down_Ctrl();
		}
	}
	if(6901==CNT)//F����A����Ъʱ���200ms
	{
		DAC0=0;
		T0Count=0;
		T1Count=0;
		T2Count=0;
		i=_i; 
	}
	//A
	if(10000<CNT && CNT<=10200)//A��������
	{
		T0Count++;
		if(T0Count==A_Freq)
		{
		    T0Count=0;
			Up_Ctrl();
		}
	}
	if(10200<CNT && CNT<=11700)//tdʱ���
	{  
		T1Count++;
		if(T1Count==A_Freq)
		{
		    T1Count=0;
			Level_Ctrl();
		} 
		i=__i;  
	}
	if(11700<CNT && CNT<=11900)//�½���
	{
		T2Count++;
		if(T2Count==A_Freq)
		{
		    T2Count=0;
			Down_Ctrl();
		}
	}
	if(11901==CNT)//A����F����Ъʱ���200ms
	{
		DAC0=0;
		T0Count=0;
		T1Count=0;
		T2Count=0;
		i=_i; 
	} 
	//F
	if(12500<CNT && CNT<=12700)//F��������
	{
		T0Count++;
		if(T0Count==F_Freq)
		{
		    T0Count=0;
			Up_Ctrl(); 
		}
	}
	if(12700<CNT && CNT<=14200)//tdʱ���
	{  
		T1Count++;
		if(T1Count==F_Freq)
		{
		    T1Count=0;
			Level_Ctrl();
		} 
		i=__i; 
	} 
	if(14200<CNT && CNT<=14400)//�½���
	{
		T2Count++;
		if(T2Count==F_Freq)
		{
		    T2Count=0;
			Down_Ctrl();
		}
	} 
}
//---------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------
//�����ؿ���
void Up_Ctrl(void)
{
	if(up_flag==0){
		up_flag=1;
	    DAC0=up_down[i++];
	}
	else
	{
		up_flag=0;
		DAC0=0;
	}
}
//ά�����ֵ����
void Level_Ctrl(void)
{
    if(up_flag==0){
		up_flag=1;
		DAC0=DAC_VALUE_MAX;
	}
	else
	{
		up_flag=0;
		DAC0=0;
	}
}
//�½��ؿ���
void Down_Ctrl(void)
{
    if(up_flag==0){
		up_flag=1;
		DAC0=up_down[--i];
	}
	else
	{
		up_flag=0;
		DAC0=0;
	}
}
