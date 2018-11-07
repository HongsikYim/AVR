/*
 * 20180803.c
 *
 * Created: 2018-08-03 오전 10:23:39
 * Author : kccistc
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <avr/interrupt.h>
//#include <util/delay.h>
//#include <string.h>
//#include <stdio.h>
//#include "UART0.h"


/*
#define MILLIS_INCREMENT_PER_OVERFLOW 1
#define MICROS_INCREMNET_PER_OVERFLOW 24
*/


/*
FILE OUTPUT \
= FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT \
= FDEV_SETUP_STREAM(NULL, UART0_receive, _FDEV_SETUP_READ);
*/

/*
volatile unsigned long timer0_millis;
volatile int timer0_micros = 0;
*/

volatile int intterupt_count = 0;

ISR(TIMER0_OVF_vect)
{
	
	/*
	unsigned long m = timer0_millis;
	int f = timer0_micros;
	
	m += MILLIS_INCREMENT_PER_OVERFLOW;
	f += MICROS_INCREMNET_PER_OVERFLOW;
	
	m += (f / 1000);
	f = f % 1000;
	
	timer0_millis = m;
	timer0_micros = f;
	*/
	
	intterupt_count ++;
}


/*
unsigned long millis()
{
	unsigned long m;
	uint8_t oldSREG = SREG;
	
	cli();
	
	m = timer0_millis;
	
	SREG = oldSREG;
	
	return m;
}
*/

/*
void init_timer0_()
{
	TCCR0 |= (1<< CS02);
	TIMSK |= (1<< TOIE0);
	
	sei();
}
*/

int main(void)
{
	/*
	stdout = &OUTPUT;
	stdin = &INPUT; // printf 사용 설정
	
	UART0_init();	// UART0 초기화
    */
	
	/*
	uint8_t state = 0;
	init_timer0_();
	
	DDRB = 0x01;
	PORTB = 0x00;
	
	unsigned long time_previous, time_current;
	time_previous = millis();
	
	while (1) 
    {
		time_current = millis();
		
		if((time_current - time_previous) > 1000)
		{
			time_previous = time_current;
			
			state = (state + 1) % 2;
			PORTB = state;
		}
    }
	*/
	
	uint8_t number[] \
		//= {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xD8, 0x80, 0x98};
		= {0b11000000, 0b11111001, 0b10100100, 0b10110000, 0b10011001, 0b10010010, 0b10000010, 0b11011000, 0b10000000, 0b10011000};
	
	int count = 0;
	DDRB = 0xFF;
	PORTB = number[0];
	
	TCCR0 |= (1<< CS02) | (1<< CS01) | (1<< CS00);
	TIMSK |= (1<< TOIE0);
	sei();
	
	while(1)
	{
		if(intterupt_count >= 64)
		{
			intterupt_count = 0;
			
			count = (count + 1) % 10;
			PORTB = number[count];
		}
	}
	
	return 0;
}

