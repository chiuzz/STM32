#ifndef _LED_H
#define _LED_H

sbit LED=P0^4;
sbit MLED=P0^6;
sbit HLED=P0^7;
void Led_Init(void);
void No_Led(void);
void Low_Led(void);
void Mid_Led(void);
void High_Led(void);
#endif
