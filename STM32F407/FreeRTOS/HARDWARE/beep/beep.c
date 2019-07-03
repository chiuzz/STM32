#include "includes.h"

void beep_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    BEEP_OFF();
}

u16 BeepCnt=0;
static BEEP_STA beep_sta=BEEP_TURN_OFF;

void beep_deal(void)
{
    switch(beep_sta)
    {
    case BEEP_TURN_ON:
        BEEP_ON();
        BeepCnt++;
        if(BeepCnt>=BEEP_ON_TIME) {
            BeepCnt=0;
            beep_sta=BEEP_TURN_OFF;
        }
        break;

    case BEEP_TURN_OFF:
        BEEP_OFF();
        break;

    default:
        break;
    }
}

void Beep_Trigger(void)
{
    beep_sta=BEEP_TURN_ON;
}













