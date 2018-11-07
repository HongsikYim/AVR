/*
 * 20180821_practice_2.c
 *
 * Created: 2018-08-21 오후 5:39:08
 * Author : kccistc
 */ 
#define F_CPU 16000000L

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>


int state = 0;

ISR(TIMER1_COMPA_vect)
{
	state = !state;
	if(state) PORTB = 0x01;
	else PORTB = 0x00;
	
	TCNT1 = 0;
}

int main(void)
{
	DDRB = 0x01;
	PORTB = 0x00;
	
	OCR1A = 0x7FFF;
	
	TCCR1B |= (1 << CS12);
	
	//TCCR1A |= (1 << COM1A0);
	
	TIMSK |= (1 << OCIE1A);
	
	sei();
	
    /* Replace with your application code */
    while (1) 
    {
		
    }
	return 0;
}

