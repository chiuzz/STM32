#ifndef __BEEP_H_
#define __BEEP_H_

typedef enum {
    BEEP_TURN_OFF = 0,
    BEEP_TURN_ON,
} BEEP_STA;

#define _BEEP_ON	1
#define _BEEP_OFF	0
#define BEEP		PFout(8)

#define BEEP_ON()		BEEP=_BEEP_ON
#define BEEP_OFF()		BEEP=_BEEP_OFF

#define BEEP_ON_TIME 20

void beep_init(void);
void beep_deal(void);
void Beep_Trigger(void);




#endif

