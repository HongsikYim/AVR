/*
 * led_control.h
 *
 * Created: 2018-09-11 오후 3:41:54
 *  Author: kccistc
 */ 


#ifndef LED_CONTROL_H_
#define LED_CONTROL_H_

#define LED_PORT PORTC
#define LED_DDR  DDRC

void ledoff(void);
void ledon(void);
void ledblink(void);
void ledinit(void);


#endif /* LED_CONTROL_H_ */