/*
 * 20180928_practice4.cpp
 *
 * Created: 2018-09-28 오후 4:32:01
 * Author : kccistc
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>

void INIT_PORT(void)
{
	DDRB = 0xF0;
}

void INIT_INTERRUPT(void)
{
	//분주비 32, CTC모드
	TCCR0 |= (0 << WGM00) | (0 << COM01) | (1 << COM00) | (1 << WGM01) | (1 << CS01) | (1 << CS00);
	
	//보정 : 200 -> 199
	OCR0 = 124;
	
	sei();
}

int main(void)
{
	INIT_PORT();
	INIT_INTERRUPT();
 
    while (1) 
    {
    }
}

