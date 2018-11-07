/*
 * 20180919_practce_git.c
 *
 * Created: 2018-09-19 오전 10:49:31
 * Author : kccistc
 */ 

#define F_CPU	16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>


#define SpeedMotor1(s)		OCR3B = s

int main(void)
{
	//분주비 64, 고속 PWM
	TCCR3A |= (1 << WGM30) | (0 << WGM31);
	TCCR3B |= (1 << WGM32) | (0 << WGM33);
	TCCR3A |= (1 << COM3B1);
	TCCR3B |= (0 << CS32) | (1 << CS31) | (1 << CS30);
	
	OCR3B = 0;
	
	/* Replace with your application code */
	while (1)
	{
		DDRE |= (1 << PE4);
		
		for(int i = 0; i < 256; i ++)
		{
			SpeedMotor1(i);
			_delay_ms(25);
		}
		_delay_ms(1000);
		
		SpeedMotor1(0);
		_delay_ms(1000);
	}
	return 0;
}
