/*
 * MOTOR.c
 *
 * Created: 2018-09-20 오전 10:17:02
 *  Author: kccistc
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "MOTOR.h"
//#define SpeedMotor1(sR1)		OCR1A = sR1	// PB5
//#define SpeedMotor2(sR2)		OCR1B = sR2	// PB6

//uint8_t R, L;
//uint8_t i = 200;

void INIT_PORT_4_MOTOR(void)
{
	DDRB |= (1 << PB5) | (1 << PB6);
}

void INIT_INTERRUPT_4_MOTOR(void)
{
	//분주비 64, 고속 PWM
	TCCR1A |= (1 << WGM10) | (0 << WGM11);
	TCCR1B |= (1 << WGM12) | (0 << WGM13);
	TCCR1A |= (1 << COM1B1) | (1 << COM1A1);
	TCCR1B |= (0 << CS12) | (1 << CS11) | (1 << CS10);
	
	//초기 OCR값
	OCR1A = 0;
	OCR1B = 250;
}

void MOTOR_STOP(void)
{
	OCR1A = 0;
	OCR1B = 0;
}

void MOTOR_RUN_FORWARD(void)
{
	OCR1A = 200;
	OCR1B = 0;
}

void MOTOR_RUN_BACKWARD(void)
{
	OCR1A = 0;
	OCR1B = 200;
}