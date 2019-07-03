#ifndef __KEY_H_
#define __KEY_H_
#include "stm32f4xx.h"

typedef enum
{
    KEY_UP_ID = 0,
    KEY_LEFT_ID,
    KEY_MID_ID,
    KEY_RIGHT_ID,
    KEY_NUM,
} KEY_ID;

typedef enum {
    NONE = 0,
    SINGLE,
    LONG,
} KEY_VALUE;

typedef enum {
    KEY_OFF = 0,
    KEY_ON,
    KEY_SINGLE,
    KEY_LONG,
    KEY_TURN_OFF,
} KEY_STA;

typedef struct key_stu {
    u8 id;
    u8 value;
    KEY_STA key_sta;
    u16 cnt;
    u8 key;
} KEY_STU;

#define _KEY_ON		1
#define _KEY_OFF	0

#define KEY_UP		PAin(0)
#define KEY_LEFT	PEin(2)
#define KEY_MID		PEin(3)
#define KEY_RIGHT	PEin(4)

#define GET_KEY_UP()		(KEY_UP		? _KEY_ON  : _KEY_OFF)
#define GET_KEY_LEFT()		(KEY_LEFT	? _KEY_OFF : _KEY_ON)
#define GET_KEY_MID()		(KEY_MID	? _KEY_OFF : _KEY_ON)
#define GET_KEY_RIGHT()		(KEY_RIGHT	? _KEY_OFF : _KEY_ON)

#define KEY_UP_BIT		0x01
#define KEY_LEFT_BIT	0x02
#define KEY_MID_BIT		0x04
#define KEY_RIGHT_BIT	0x08

#define BEEP_ON_TIME 20

extern void key_init(void);
extern void key_scan(void);
void key_deal(KEY_STU *key_stu);

extern KEY_STU key_stu[KEY_NUM];
extern u8 read_OK;

#endif

