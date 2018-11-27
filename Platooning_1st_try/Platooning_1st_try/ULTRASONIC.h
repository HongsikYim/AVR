/*
 * ULTRASONIC.h
 *
 * Created: 2018-10-01 오후 5:02:35
 *  Author: kccistc
 */ 


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_


#include "AllofLibrary.h"

#define PRESCALER	1024
#define ULTRA_PORT	PORTG
#define ULTAR_DDR	DDRG
#define ULTRA_PIN	PING
#define ULTRA_TRIG	1
#define ULTRA_ECHO	0


void INIT_4_ULTRASONIC(void);
void UltraSonic_Trigger(void);
uint8_t measure_distance(void);


#endif /* ULTRASONIC_H_ */