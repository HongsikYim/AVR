/*
 * MOTOR_2.c
 *
 * Created: 2018-08-28 오후 12:16:00
 *  Author: kccistc
 */ 

#include "MOTOR_2.h"

uint8_t Speed1 = 0;


void INIT_PORT_4_TIMER3(void)
{
	DDRE |= (1<< PE0) | (1 << PE2) | (1 << PE4);
}

void INIT_TIMER3(void)
{
	TCCR3A |= (1 << WGM30) | (1 << COM3B1);
	TCCR3B |= (1 << WGM32) | (1 << CS31) | (1 << CS30);
	
	OCR3B = 0;
}

void MOTOR_CLOCKWISE_ACCELERATION_2(uint8_t Speed1)
{
	EnableMotor1();
	ForwardMotor1();
	
	for(int i = 0; i < Speed1; i ++)
	{
		SpeedMotor1(i);
		_delay_ms(20);
	}
	return;
}
void MOTOR_UNCLOCKWISE_ACCELERATION_2(uint8_t Speed1)
{
	EnableMotor1();
	BackwardMotor1();
	
	for(int i = 0; i < Speed1; i ++)
	{
		SpeedMotor1(i);
		_delay_ms(20);
	}
	return;
}

void MOTOR_CLOCKWISE_DECELERATION_2(uint8_t Speed1)
{
	EnableMotor1();
	ForwardMotor1();
	
	for(int i = Speed1; i > 0; i --)
	{
		SpeedMotor1(i);
		_delay_ms(20);
	}
	return;
}
void MOTOR_UNCLOCKWISE_DECELERATION_2(uint8_t Speed1)
{
	EnableMotor1();
	BackwardMotor1();
	
	for(int i = Speed1; i > 0; i --)
	{
		SpeedMotor1(i);
		_delay_ms(20);
	}
	return;
}

void MOTOR_STOP_21(void)
{
	SpeedMotor1(0);
	DisableMotor1();
}


void MOTOR_DRY_MODE_2(uint8_t Speed1)
{
	Speed1 = 240;
	MOTOR_CLOCKWISE_ACCELERATION_2(Speed1);
	_delay_ms(3000);
	MOTOR_CLOCKWISE_DECELERATION_2(Speed1);
	
	MOTOR_STOP_21();
	return;
} 

