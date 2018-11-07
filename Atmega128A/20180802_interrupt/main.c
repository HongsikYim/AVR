/*
 * 20180802_interrupt.c
 *
 * Created: 2018-08-02 오후 3:38:04
 * Author : kccistc
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//#include <stdio.h>
//#include "UART0.h"


volatile int state = 0;	// 현재 LED 상태

ISR(INT0_vect)
{
	state = (state + 1) % 2;
}

void INIT_PORT(void)
{
	DDRB = 0xFF;
	PORTB = 0xFF;
	
	DDRD = 0x00;
	PORTD = 0x01;
}

void INIT_INT0(void)
{
	EIMSK |= (1 << INT0);
	EICRA |= (1 << ISC01);
	sei();
}


char circular_shift_right(char pattern)
{
	char new_pattern_1 = (pattern << 7) | (pattern >> 1);
	
	return new_pattern_1;
}

char circular_shift_left(char pattern)
{
	char new_pattern_2 = (pattern >> 7) | (pattern << 1);
	
	return new_pattern_2;
}


int main(void)
{
	
	INIT_PORT();
	INIT_INT0();
	
	char pattern = 0x01;
	
	DDRB = 0xFF;
	
    while (1) 
    {
		if(state == 0)
		{
			PORTB = pattern;
			pattern = circular_shift_left(pattern);
			_delay_ms(100);
		}
		else
		{
			PORTB = pattern;
			pattern = circular_shift_right(pattern);
			_delay_ms(100);			
		}
    }
	
	return 0;
}

