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
#define ULTRA_TRIG_1	1
#define ULTRA_ECHO_1	2
#define ULTRA_TRIG_2	3
#define ULTRA_ECHO_2	4

void INTIT_4_ULTRASONIC(void);
void UltraSonic_Trigger_1(void);
void UltraSonic_Trigger_2(void);
uint8_t measure_distance_1(void);
uint8_t measure_distance_2(void);


#endif /* ULTRASONIC_H_ */