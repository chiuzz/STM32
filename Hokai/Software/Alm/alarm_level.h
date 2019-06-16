#ifndef _ALARM_LEVEL_H
#define _ALARM_LEVEL_H

#define Pin_0 0x01
#define Pin_1 0x02
#define Pin_2 0x04
#define Pin_3 0x08
#define Pin_4 0x10
#define Pin_5 0x20
#define Pin_6 0x40
#define Pin_7 0x80

#define AlarmNomal  0  //
#define AlarmLLevel 1
#define AlarmMLevel 2
#define AlarmHLevel 3

#define Mute    0      //¾²Òô
#define Volume0 0	   //ÒôÁ¿Îª0
#define Volume1 1
#define Volume2 2
#define Volume3 3

sbit vol1=P1^0;
sbit vol2=P1^1; 
sbit vol3=P1^2;
sbit warn1=P1^3;
sbit warn2=P1^4;
void InputIO_Init(void);
void Warn_Check(void);
void Vol_Check(void);

#endif