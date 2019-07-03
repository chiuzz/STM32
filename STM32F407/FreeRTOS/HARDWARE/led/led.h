#ifndef __LED_H_
#define __LED_H_

typedef enum {
    TURN_ON = 0,
    TURN_OFF,
} LED_STA;

#define LED_ON		0
#define LED_OFF		1
#define LED_RED		PFout(9)
#define LED_GREEN	PFout(10)

#define LED_RED_ON()		LED_RED=LED_ON
#define LED_RED_OFF()		LED_RED=LED_OFF

#define LED_GREEN_ON()		LED_GREEN=LED_ON
#define LED_GREEN_OFF()		LED_GREEN=LED_OFF

#define LED_ON_OFF_TIME 25
#define LED_CNT_STEP	1

extern void led_init(void);
extern void led_breath(void);

#endif

