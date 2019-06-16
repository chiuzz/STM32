#include"c8051f330.h"
#include"alarm_level.h"
#include"timer.h"
u8 level=3;	//报警级别变量
u8 vol=2;	//报警音量变量
//-------------------------------------------------
//报警级别，音量级别数字信号输入IO口初始化
//-------------------------------------------------
void InputIO_Init(void)
{ 
   P1SKIP  |= Pin_0 + Pin_1 + Pin_2 + Pin_3 + Pin_4;          
   XBR1     = 0x40;  //交叉开关使能 
}
//-------------------------------------------------
//报警级别查询
//-------------------------------------------------
void Warn_Check(void)
{
  
   if     (warn1==0 && warn2==0)
   	level=AlarmNomal;  //不报警
   else if(warn1==1 && warn2==0)
   	level=AlarmLLevel; //低级报警
   else if(warn1==0 && warn2==1)
   	level=AlarmMLevel; //中级报警
   else                         
   	level=AlarmHLevel; //高级报警
}
//-------------------------------------------------
//报警音量查询
//-------------------------------------------------
void Vol_Check(void)
{
   if(vol3)vol=Mute;                           //静音
   else
   {
       if     (vol1==0 && vol2==0)
	   	vol=Volume0; //音量为0
   	   else if(vol1==1 && vol2==0)
	   	vol=Volume1; //低音
   	   else if(vol1==0 && vol2==1)
	   	vol=Volume2; //中音
	   else 					  
	   	vol=Volume3; //高音
   }
}