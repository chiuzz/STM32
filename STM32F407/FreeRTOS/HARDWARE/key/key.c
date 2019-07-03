#include "includes.h"

KEY_STU key_stu[KEY_NUM];

void key_init(void)
{
    u8 i;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
//    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
//    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    for(i=0; i<KEY_NUM; i++) {
        key_stu[i].id=i;
        key_stu[i].cnt=0;
        key_stu[i].key_sta=KEY_OFF;
        key_stu[i].value=NONE;
    }
}

void key_scan(void)
{
    u8 i;
    if(FALSE==GET_KEY_UP())
        key_stu[KEY_UP_ID].key=FALSE;
    else
        key_stu[KEY_UP_ID].key=TRUE;

    if(FALSE==GET_KEY_LEFT())
        key_stu[KEY_LEFT_ID].key=FALSE;
    else
        key_stu[KEY_LEFT_ID].key=TRUE;

    if(FALSE==GET_KEY_MID())
        key_stu[KEY_MID_ID].key=FALSE;
    else
        key_stu[KEY_MID_ID].key=TRUE;

    if(FALSE==GET_KEY_RIGHT())
        key_stu[KEY_RIGHT_ID].key=FALSE;
    else
        key_stu[KEY_RIGHT_ID].key=TRUE;

    for(i=0; i<KEY_NUM; i++) {
        key_deal(&key_stu[i]);
    }
}
#define DEBOUNCE_TIME	10
#define KEY_SINGLE_TIME	200
#define KEY_LONG_TIME	100
#define KEY_LEAVE_TIME	500
u8 read_OK=0;
void key_deal(KEY_STU *key_stu)
{
    switch(key_stu->key_sta)
    {
    case KEY_OFF:
        key_stu->value=NONE;
        key_stu->cnt=0;
        if(key_stu->key==TRUE) {
            key_stu->key_sta=KEY_ON;
            break;
        }
        break;
    case KEY_ON:
        if(key_stu->key==FALSE) {		//ËÉÊÖ
            key_stu->key_sta=KEY_TURN_OFF;
            key_stu->cnt=0;
            break;
        }

        if(key_stu->cnt>=DEBOUNCE_TIME) {
            key_stu->key_sta=KEY_SINGLE;
            key_stu->value=SINGLE;
            key_stu->cnt=0;
        }
        key_stu->cnt++;
        break;
    case KEY_SINGLE:
        if(key_stu->key==FALSE) {		//ËÉÊÖ
            key_stu->key_sta=KEY_TURN_OFF;
            key_stu->cnt=0;
            break;
        }

        if(key_stu->cnt>=KEY_SINGLE_TIME) {
            key_stu->key_sta=KEY_LONG;
            key_stu->value=LONG;
            key_stu->cnt=0;
        }
        key_stu->cnt++;
        break;
    case KEY_LONG:
        if(key_stu->key==FALSE) {
            key_stu->key_sta=KEY_TURN_OFF;
            key_stu->cnt=0;
            break;
        }

        if(key_stu->cnt>=KEY_LONG_TIME) {
            key_stu->key_sta=KEY_LONG;
            key_stu->value=LONG;
            key_stu->cnt=0;
            read_OK=1;
        }
        key_stu->cnt++;
        break;
    case KEY_TURN_OFF:
        if(key_stu->value!=NONE) {
            read_OK=1;
        }
        key_stu->key_sta=KEY_OFF;
        break;
    default:
        break;
    }
}
















