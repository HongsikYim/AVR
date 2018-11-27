/*
 * MOTOR.c
 *
 * Created: 2018-09-20 오전 10:17:02
 *  Author: kccistc
 */ 

#include "MOTOR.h"
#define SpeedMotorR1(sR1)		OCR1A = sR1
#define SpeedMotorR2(sR2)		OCR1B = sR2
#define SpeedMotorL1(sL1)		OCR3A = sL1
#define SpeedMotorL2(sL2)		OCR3B = sL2

#define Maximum_Speed			100

uint8_t R = 80, L = 80;
uint8_t i;

void INIT_PORT_4_MOTOR(void)
{
	DDRB |= (1 << PB5) | (1 << PB6);
	DDRE |= (1 << PE3) | (1 << PE4);
}

void INIT_INTERRUPT_4_MOTOR(void)
{
	TCCR1A |= (1 << WGM10) | (0 << WGM11);
	TCCR1B |= (1 << WGM12) | (0 << WGM13);
	TCCR1A |= (1 << COM1B1) | (1 << COM1A1);
	TCCR1B |= (0 << CS12) | (1 << CS11) | (1 << CS10);
	
	//분주비 64, 고속 PWM
	TCCR3A |= (1 << WGM30) | (0 << WGM31);
	TCCR3B |= (1 << WGM32) | (0 << WGM33);
	TCCR3A |= (1 << COM3B1) | (1 << COM3A1);
	TCCR3B |= (0 << CS32) | (1 << CS31) | (1 << CS30);
	
	OCR1A = 0;
	OCR1B = 0;
	OCR3A = 0;
	OCR3B = 0;

}

void MOTOR_SPEED_UP(void)
{
	i = R;
	i ++;
	if(i > Maximum_Speed)
	{
		i = Maximum_Speed;
	}
	R = i;
	L = i;
}

void MOTOR_SPEED_DOWN(void)
{
	i = R;
	i --;
	if(i < 1)
	{
		i = 0;
	}
	R = i;
	L = i;
}

void MOTOR_STOP(void)
{
	OCR1A = 0;
	OCR1B = 0;
	OCR3A = 0;
	OCR3B = 0;
}

void MOTOR_RUN_FORWARD(void)
{
	if(R > L)
	{
		L = R;
	}
	if(L > R)
	{
		R = L;
	}
	SpeedMotorR1(0);
	SpeedMotorR2(0.9*R);
	SpeedMotorL1(0);
	SpeedMotorL2(0.9*R);
	
	/* 하드코딩
	OCR1A = 200;
	OCR1B = 0;
	OCR3A = 200;
	OCR3B = 0;
	*/
}

void MOTOR_RUN_BACKWARD(void)
{
	if(R > L)
	{
		L = R;
	}
	if(L > R)
	{
		R = L;
	}
	SpeedMotorR1(0.9*R);
	SpeedMotorR2(0);
	SpeedMotorL1(0.9*R);
	SpeedMotorL2(0);
	
	/*
	OCR1A = 0;
	OCR1B = 200;
	OCR3A = 0;
	OCR3B = 200;
	*/
}

void MOTOR_RUN_RIGHT(void)
{
	SpeedMotorR1(0);
	SpeedMotorR2(0.9*R);
	SpeedMotorL1(0.75*L);
	SpeedMotorL2(0);
}

void MOTOR_RUN_LEFT(void)
{
	SpeedMotorR1(0.75*R);
	SpeedMotorR2(0);
	SpeedMotorL1(0);
	SpeedMotorL2(0.9*L);
}