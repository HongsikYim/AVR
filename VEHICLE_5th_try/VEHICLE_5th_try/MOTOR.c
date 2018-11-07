﻿/*
 * MOTOR.c
 *
 * Created: 2018-09-20 오전 10:17:02
 *  Author: kccistc
 */ 

#include "MOTOR.h"
#include "UART0.h"
#include "ULTRASONIC.h"

#define SpeedMotorR1(sR1)		OCR1A = sR1
#define SpeedMotorR2(sR2)		OCR1B = sR2
#define SpeedMotorL1(sL1)		OCR3A = sL1
#define SpeedMotorL2(sL2)		OCR3B = sL2

uint8_t R, L;
uint8_t i = 180;
extern uint8_t auto_states = 0;

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
	i ++;
	if(i > 250)
	{
		i = 250;
	}
	R = i;
	L = i;
	//UART0_print_1_byte_number(i);
}

void MOTOR_SPEED_DOWN(void)
{
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
	SpeedMotorR2(R);
	SpeedMotorL1(0);
	SpeedMotorL2(0.95*L);
	
	/*
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
	SpeedMotorR1(R);
	SpeedMotorR2(0);
	SpeedMotorL1(L);
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
	/*
	i --;
	if(i < 1)
	{
		i = 0;
	}
	R = i;
	
	SpeedMotorR1(0);
	SpeedMotorR2(R);
	SpeedMotorL1(0);
	SpeedMotorL2(L);
	*/
	
	SpeedMotorR1(0);
	SpeedMotorR2(R);
	SpeedMotorL1(0);
	SpeedMotorL2(R/4);
}

void MOTOR_RUN_LEFT(void)
{
	/*
	i --;
	if(i < 1)
	{
		i = 0;
	}
	L = i;
	
	SpeedMotorR1(0);
	SpeedMotorR2(R);
	SpeedMotorL1(0);
	SpeedMotorL2(L);
	*/
	
	SpeedMotorR1(0);
	SpeedMotorR2(R/4);
	SpeedMotorL1(0);
	SpeedMotorL2(L);
}

void MOTOR_ROTATE_RIGHT(void)
{
	SpeedMotorR1(0);
	SpeedMotorR2(R);
	SpeedMotorL1(L);
	SpeedMotorL2(0);
}

void MOTOR_ROTATE_LEFT(void)
{
	SpeedMotorR1(R);
	SpeedMotorR2(0);
	SpeedMotorL1(0);
	SpeedMotorL2(L);
}


void MOTOR_AUTO_DRIVE(void)
{
	
	uint8_t temp1, temp2, temp3, temp4;
	
	temp1 = measure_distance_1();
	temp2 = temp1;
	temp1 = measure_distance_1();
	temp3 = temp2;
	temp2 = temp1;
	temp1 = measure_distance_1();
	
	distance_1 = (temp1+temp2+temp3)/3;
	distance_2 = measure_distance_2();

	
	printf("distance1: %d cm  \r\n", distance_1);
	printf("distance2: %d cm  \r\n", distance_2);
	
	
	switch(auto_states)
	{
		
		//1st course
		case 0:
		MOTOR_RUN_FORWARD();
		if(distance_1 < 60 && distance_2 < 60)
		{
			if(distance_1 < 60 && distance_2 < 60)
			{
				MOTOR_STOP();
				auto_states = 1;
			}
		}
		break;
		
		case 1:
		MOTOR_ROTATE_LEFT();
		_delay_ms(478);
		MOTOR_STOP();
		_delay_ms(100);
		auto_states = 2;
		break;
		
		//2nd course
		case 2:
		MOTOR_RUN_FORWARD();
		if(distance_1 < 60 && distance_2 < 60)
		{
			if(distance_1 < 60 && distance_2 < 60)
			{
				MOTOR_STOP();
				auto_states = 3;
			}
		}
		break;
		
		case 3:
		MOTOR_ROTATE_LEFT();
		_delay_ms(480);
		MOTOR_STOP();
		_delay_ms(100);
		auto_states = 4;
		break;
		
		//3rd course
		case 4:
		MOTOR_RUN_FORWARD();
		if(distance_1 < 60 && distance_2 < 60)
		{
			if(distance_1 < 60 && distance_2 < 60)
			{
				MOTOR_STOP();
				auto_states = 5;
			}
		}
		break;
		
		case 5:
		MOTOR_ROTATE_RIGHT();
		_delay_ms(490);
		MOTOR_STOP();
		_delay_ms(100);
		auto_states = 6;
		break;
		
		//4th course
		case 6:
		MOTOR_RUN_FORWARD();
		if(distance_1 < 60 && distance_2 < 60)
		{
			MOTOR_STOP();
			auto_states = 7;
		}
		break;
		
		case 7:
		MOTOR_ROTATE_LEFT();
		_delay_ms(480);
		MOTOR_STOP();
		_delay_ms(100);
		auto_states = 8;
		break;
		
		//5th course
		case 8:
		MOTOR_RUN_FORWARD();
		if(distance_1 < 60 && distance_2 < 60)
		{
			MOTOR_STOP();
			auto_states = 9;
		}
		break;
		
		case 9:
		MOTOR_ROTATE_RIGHT();
		_delay_ms(480);
		MOTOR_STOP();
		_delay_ms(100);
		auto_states = 10;
		break;
		
		//6th course
		case 10:
		MOTOR_RUN_FORWARD();
		if(distance_1 < 60 && distance_2 < 60)
		{
			MOTOR_STOP();
			auto_states = 11;
		}
		break;
		
		case 11:
		MOTOR_ROTATE_RIGHT();
		_delay_ms(480);
		MOTOR_STOP();
		_delay_ms(100);
		auto_states = 12;
		break;
		
		//7th course
		case 12:
		MOTOR_RUN_FORWARD();
		if(distance_1 < 60 && distance_2 < 60)
		{
			MOTOR_STOP();
			auto_states = 13;
		}
		break;
		
		case 13:
		MOTOR_ROTATE_LEFT();
		_delay_ms(480);
		MOTOR_STOP();
		_delay_ms(100);
		auto_states = 0;
		break;
		
		default:
		break;
	}
	
}

/*
void MOTOR_ACCELERATION(void)
{	
	for(int i = 0; i < 256; i ++)
	{
		SpeedMotorR1(i);
		_delay_ms(25);
	}
}

void MOTOR_DECLERATION(void)
{
	for(int i = 256; i >= 0; i --)
	{
		SpeedMotorR1(i);
		_delay_ms(25);
	}
}
*/