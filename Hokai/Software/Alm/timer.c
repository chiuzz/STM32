#include <stdio.h>
#include"c8051f330.h"
#include"timer.h"
#include"alarm_level.h"
#include"led.h"
extern u8 level;    //报警级别变量
extern u8 vol;	    //报警音量变量
extern u16 LED_cnt;	//计数变量，控制LED闪烁频率
//-----------------------------------------------------------------------------
//  定时器2初始化
//-----------------------------------------------------------------------------
void Timer2_Init (int counts)
{
    TMR2CN = 0x00;//定时器2工作在16位自动重装载方式                                                                                           
    CKCON |= 0x30; //定时器2工作在系统时钟                  
    TMR2RL  = -counts;                  
    TMR2    = TMR2RL;                  
    ET2= 1;                         
    TR2=1;                     

}

//-----------------------------------------------------------------------------
//  定时器3初始化
//-----------------------------------------------------------------------------
void Timer3_Init (int counts)
{
   TMR3CN = 0x00; //定时器3工作在16位自动重装载方式                                  
   CKCON |= 0xc0;  //定时器3工作在系统时钟             
   TMR3RL  = -counts;               
   TMR3    = TMR3RL;                  
   EIE1 |= 0x80;    //中断允许                  
   TMR3CN |= 0x04; //清标志位，启动TMR3               

}

//-----------------------------------------------------------------------------
//  定时器2中断服务函数，处理三个报警LED闪烁
//-----------------------------------------------------------------------------
void Timer2_ISR (void) interrupt 5
{
   TMR2CN &= ~0x80;                             
   switch(level)                     //判断报警级别
   {  
       case AlarmLLevel:			 //低级报警
	          Low_Led();
	          break;
       case AlarmMLevel:			 //中级报警
	          Mid_Led();
			  break;
       case AlarmHLevel:			 //高级报警
	          High_Led();
			  break;
	   case AlarmNomal:			     //不报警
	          No_Led();
			  break;
	   default:
	          break;
   }
}

//-----------------------------------------------------------------------------
//  定时器3中断
//-----------------------------------------------------------------------------
//变量定义
#define C_Freq 19  //C调频率控制常量 f0=1/(19*2*100us)=263Hz
#define D_Freq 17  //D调频率控制常量
#define E_Freq 15  //E调频率控制常量
#define F_Freq 14  //F调频率控制常量
#define G_Freq 13  //G调频率控制常量
#define A_Freq 11  //A调频率控制常量
#define B_Freq 10  //B调频率控制常量
//
//sbit LED =P0^6;
//
u8 T0Count=0,T1Count=0,T2Count=0;//脉冲频率f0控制变量
u16 DAC_VALUE_MAX=388<<6;        //DAC转换最大值为DAC_VALUE_MAX
u16 DAC_Min=130<<6;				 //小音量控制最大DAC值
u16 DAC_Mid=220<<6;				 //中音量控制最大DAC值
u16 DAC_Max=388<<6;				 //大音量控制最大DAC值
u16 CNT=0;                       //高级报警音调cafaf时间控制变量
u32 Tcount=0;                    //全局时间控制变量
//
u8 up_flag=1;                    //切换更新DAC转换标志变量
u8 i=0;							 //查询up_down[]数组变量
u8 _i=0;						 //控制i大小变量
u8 __i=0;                        //控制i大小变量
u16 code up_down[40]={
0,0,0,0,0,0,0,0,0,0,												 //音量为0
13<<6,26<<6,39<<6,52<<6,65<<6,78<<6,91<<6,104<<6,117<<6,130<<6,	     //小音量
22<<6,44<<6,66<<6,88<<6,110<<6,132<<6,154<<6,176<<6,198<<6,220<<6,   //中音量
40<<6,80<<6,120<<6,160<<6,200<<6,240<<6,280<<6,320<<6,360<<6,388<<6  //高音量
};//上升沿，下降沿DAC转换值,code定义数组的存储位置是程序存储器，只读。

//中断服务函数
void Timer3_ISR (void) interrupt 14
{    
   Warn_Check();                      //查询报警级别 
   Vol_Check();						  //查询音量级别
   switch(vol)						  //判断音量级别
   {
       case 0:						          //音量为0 或 静音
	          DAC_VALUE_MAX=0;
	          break;
	   case Volume1:						  //小音量
	          DAC_VALUE_MAX=DAC_Min;
	          break;
       case Volume2:						  //中音量
	          DAC_VALUE_MAX=DAC_Mid;
			  break;
       case Volume3:						  //大音量
	          DAC_VALUE_MAX=DAC_Max;
			  break;
	   default:
	          break;
   }
   _i=vol*10;                        //计算得到_i 查询up_down[40]数组的计算公式
   __i=_i+9;                         //计算得到__i
   switch(level)					 //判断报警级别
   {  
       case AlarmLLevel:						 //低级报警
	          Low_alarm();
	          break;
       case AlarmMLevel:						 //中级报警
	          Middle_alarm();
			  break;
       case AlarmHLevel:						 //高级报警
	          High_alarm();
			  break;
	   case AlarmNomal:
	          DAC0=0;                //不报警
	          Tcount=1;
	          T0Count=0;
	          T1Count=0;
	          T2Count=0;
			  break;
	   default:
	          break;
   }
//   LED =~LED; //方便测试定时器定时是否准确
   TMR3CN &= ~0x80;//清除中断标志
}
//============================================================================================
//低级报警
//============================================================================================
void Low_alarm(void)
{
	Tcount++;
	if(Tcount>=156401)//低级报警周期为15.64s
	{
		Tcount=1;
		T0Count=0;
		T1Count=0;
		T2Count=0;
		i=_i;
	}
	
	if(Tcount<=200)//E调上升沿20ms
	{
		T0Count++;
		if(T0Count==E_Freq)
		{
		    T0Count=0;
			Up_Ctrl();
		} 
	}
	else if(Tcount<=2200)//td时间段
	{  
		T1Count++;
		if(T1Count==E_Freq)
		{
		    T1Count=0;
			Level_Ctrl();
		} 
		i=__i;  
	}
	if(2200<Tcount && Tcount<=2400)//E调下降沿
	{
		T2Count++;
		if(T2Count==E_Freq)
		{
		    T2Count=0;
			Down_Ctrl();
		}
	}
	if(2401==Tcount)//E调和C调间歇时间段200ms
	{
		DAC0=0;
		T0Count=0;
		T1Count=0;
		T2Count=0;
		i=_i;
	}
	if(4000<Tcount && Tcount<=4200)//C调上升沿
	{
		T0Count++;
		if(T0Count==C_Freq)
		{
		    T0Count=0;
			Up_Ctrl();
		}
	}
	if(4200<Tcount && Tcount<=6200)//td时间段
	{  
		T1Count++;
		if(T1Count==C_Freq)
		{
		    T1Count=0;
			Level_Ctrl();
		} 
		i=__i;  
	}
	if(6200<Tcount && Tcount<=6400)//下降沿
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
//中级报警
//============================================================================================
void Middle_alarm(void)
{
	Tcount++;
	if(Tcount>=60401)//中级报警周期为6.04s
	{
		Tcount=1;
		T0Count=0;
		T1Count=0;
		T2Count=0;
		i=_i;
	}
	
	if(Tcount<=200)//C调上升沿20ms
	{
		T0Count++;
		if(T0Count==C_Freq)
		{
		    T0Count=0;
			Up_Ctrl();
		} 
	}
	if(200<Tcount && Tcount<=2200)//td时间段
	{  
		T1Count++;
		if(T1Count==C_Freq)
		{
		    T1Count=0;
			Level_Ctrl();
		} 
		i=__i;  
	}
	if(2200<Tcount && Tcount<=2400)//C调下降沿
	{
		T2Count++;
		if(T2Count==C_Freq)
		{
		    T2Count=0;
			Down_Ctrl();
		}
	}
	if(2401==Tcount)//C调和A调间歇时间段200ms
	{
		DAC0=0;
		T0Count=0;
		T1Count=0;
		T2Count=0;
		i=_i;
	}
	if(4000<Tcount && Tcount<=4200)//A调上升沿
	{
		T0Count++;
		if(T0Count==A_Freq)
		{
		    T0Count=0;
		    Up_Ctrl();	 
		}
	}
	if(4200<Tcount && Tcount<=6200)//td时间段
	{  
		T1Count++;
		if(T1Count==A_Freq)
		{
		    T1Count=0;
			Level_Ctrl();
		} 
		i=__i;  
	}
	if(6200<Tcount && Tcount<=6400)//下降沿
	{
		T2Count++;
		if(T2Count==A_Freq)
		{
		    T2Count=0;
			Down_Ctrl();
		}
	}
	if(6401==Tcount)//A调和F调间歇时间段200ms
	{
		DAC0=0;
		T0Count=0;
		T1Count=0;
		T2Count=0;
		i=_i;
	}
	if(8000<Tcount && Tcount<=8200)//F调上升沿
	{
		T0Count++;
		if(T0Count==F_Freq)
		{
		    T0Count=0;
			Up_Ctrl();
		}
	}
	if(8200<Tcount && Tcount<=10200)//td时间段
	{  
		T1Count++;
		if(T1Count==F_Freq)
		{
		    T1Count=0;
			Level_Ctrl();
		}  
		i=__i; 
	}
	if(10200<Tcount && Tcount<=10400)//下降沿
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
//高级报警
//============================================================================================
//
void High_alarm(void)
{	
	Tcount++;
	if(Tcount>=66801)//中级报警周期为6.68s
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
//音调 c a f a f 控制函数 
//-------------------------------------------------------------------------
//
void CAFAF(void)
{
	CNT++;	
	//C	
	if(CNT<=200)//C调上升沿20ms
	{
		T0Count++;
		if(T0Count==C_Freq)
		{
		    T0Count=0;
			Up_Ctrl();
		} 
	} 
	if(200<CNT && CNT<=1700)//td时间段
	{  
		T1Count++;
		if(T1Count==C_Freq)
		{
		    T1Count=0;
			Level_Ctrl();  
		}  
		i=__i;
	}
	if(1700<CNT && CNT<=1900)//C调下降沿
	{
		T2Count++;
		if(T2Count==C_Freq)
		{
		    T2Count=0;
			Down_Ctrl(); 
		}
	} 
	if(1901==CNT)//C调和A调间歇时间段200ms
	{
		DAC0=0;
		T0Count=0;
		T1Count=0;
		T2Count=0;
		i=_i;
	} 
	//A	
	if(2500<CNT && CNT<=2700)//A调上升沿
	{
		T0Count++;
		if(T0Count==A_Freq)
		{
		    T0Count=0;
			Up_Ctrl();
		}
	}
	if(2700<CNT && CNT<=4200)//td时间段
	{  
		T1Count++;
		if(T1Count==A_Freq)
		{
		    T1Count=0;
			Level_Ctrl();
		} 
		i=__i; 
	}
	if(4200<CNT && CNT<=4400)//下降沿
	{
		T2Count++;
		if(T2Count==A_Freq)
		{
		    T2Count=0;
			Down_Ctrl();
		}
	}
	if(4401==CNT)//A调和F调间歇时间段200ms
	{
		DAC0=0;
		T0Count=0;
		T1Count=0;
		T2Count=0;
		i=_i; 
	}
	//F
	if(5000<CNT && CNT<=5200)//F调上升沿
	{
		T0Count++;
		if(T0Count==F_Freq)
		{
		    T0Count=0;
			Up_Ctrl();
		}
	}
	if(5200<CNT && CNT<=6700)//td时间段
	{  
		T1Count++;
		if(T1Count==F_Freq)
		{
		    T1Count=0;
            Level_Ctrl();
		} 
		i=__i;  
	}
	if(6700<CNT && CNT<=6900)//下降沿
	{
		T2Count++;
		if(T2Count==F_Freq)
		{
		    T2Count=0;
			Down_Ctrl();
		}
	}
	if(6901==CNT)//F调和A调间歇时间段200ms
	{
		DAC0=0;
		T0Count=0;
		T1Count=0;
		T2Count=0;
		i=_i; 
	}
	//A
	if(10000<CNT && CNT<=10200)//A调上升沿
	{
		T0Count++;
		if(T0Count==A_Freq)
		{
		    T0Count=0;
			Up_Ctrl();
		}
	}
	if(10200<CNT && CNT<=11700)//td时间段
	{  
		T1Count++;
		if(T1Count==A_Freq)
		{
		    T1Count=0;
			Level_Ctrl();
		} 
		i=__i;  
	}
	if(11700<CNT && CNT<=11900)//下降沿
	{
		T2Count++;
		if(T2Count==A_Freq)
		{
		    T2Count=0;
			Down_Ctrl();
		}
	}
	if(11901==CNT)//A调和F调间歇时间段200ms
	{
		DAC0=0;
		T0Count=0;
		T1Count=0;
		T2Count=0;
		i=_i; 
	} 
	//F
	if(12500<CNT && CNT<=12700)//F调上升沿
	{
		T0Count++;
		if(T0Count==F_Freq)
		{
		    T0Count=0;
			Up_Ctrl(); 
		}
	}
	if(12700<CNT && CNT<=14200)//td时间段
	{  
		T1Count++;
		if(T1Count==F_Freq)
		{
		    T1Count=0;
			Level_Ctrl();
		} 
		i=__i; 
	} 
	if(14200<CNT && CNT<=14400)//下降沿
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
//上升沿控制
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
//维持最大值控制
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
//下降沿控制
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
