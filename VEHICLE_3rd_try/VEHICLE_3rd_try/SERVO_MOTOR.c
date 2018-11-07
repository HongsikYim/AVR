/*
 * SERVO_MOTOR.c
 *
 * Created: 2018-10-04 오후 6:30:06
 *  Author: kccistc
 */ 


#include "SERVO_MOTOR.h"

void INIT_SERVO(void)
{
	TCCR2 |= (1 << WGM20) | (1 << WGM21) | (1 << CS20) | (0 << CS21) | (1 << CS22) | (1 << COM20);
	OCR2 = 20;
	
	DDRB |= (1 << PB7);
}
void ROTATE_SERVO(void)
{
	OCR2 = PULSE_MAX;
}