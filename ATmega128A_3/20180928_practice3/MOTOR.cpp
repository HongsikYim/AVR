/*
 * MOTOR.cpp
 *
 * Created: 2018-09-28 오후 2:30:35
 *  Author: kccistc
 */ 

#include "MOTOR.h"

#define SpeedMotorR1(sR1)		OCR1A = sR1
#define SpeedMotorR2(sR2)		OCR1B = sR2
#define SpeedMotorL1(sL1)		OCR3A = sL1
#define SpeedMotorL2(sL2)		OCR3B = sL2

uint8_t ControlSpeed;


MOTOR::MOTOR() // 생성자 > PORT, PWM 초기화
{
	// Init port for motors
	DDRB |= (1 << PB5) | (1 << PB6);
	DDRE |= (1 << PE3) | (1 << PE4);
	
	// Init PWM for motors
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

MOTOR::~MOTOR() // 소멸자
{
	
}

/*
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
*/

uint8_t GetSpeedValue(void)
{
	ControlSpeed = 0;
}

void MOTOR::IDLE(void)
{
	OCR1A = 0;
	OCR1B = 0;
	OCR3A = 0;
	OCR3B = 0;
}

void MOTOR::RUN_FORWARD(void)
{
	OCR1A = ControlSpeed;
	OCR1B = 0;
	OCR3A = ControlSpeed;
	OCR3B = 0;
}

void MOTOR::RUN_BACKWARD(void)
{
	OCR1A = 0;
	OCR1B = 200;
	OCR3A = 0;
	OCR3B = 200;
}

void MOTOR::RUN_RIGHT(void)
{
	OCR1A = 200;
	OCR1B = 0;
	OCR3A = 100;
	OCR3B = 0;
}

void MOTOR::RUN_LEFT(void)
{
	OCR1A = 100;
	OCR1B = 0;
	OCR3A = 200;
	OCR3B = 0;
}

void MOTOR::ACCELERATION(void)
{
	int i;
	i ++;
	_delay_us(5);
	ControlSpeed = i;
	
}

void MOTOR::DECLERATION(void)
{
	for(int i = 256; i >= 0; i --)
	{
		SpeedMotorR1(i);
		_delay_ms(25);
	}
}