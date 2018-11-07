/*
 * 20180821_practice_1.c
 *
 * Created: 2018-08-21 오전 9:46:07
 * Author : kccistc
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile int count = 0;
int state = 0;


ISR(TIMER0_COMP_vect)
{
	count++;
}

ISR(TIMER3_COMPA_vect)
{
}

void INIT_PORT(void)
{
	DDRB = 0xFF;
	
	DDRD = 0xFF;
	PORTD = 0x00;
	
	DDRF &= ~0xFF;
	PORTF = 0xFF;
	
	DDRE = 0xFF;
}

void INIT_INTERRUPT(void)
{
	TCCR0 |= (1 << WGM00) | (1 << COM01) | (0 << COM00) | (1 << WGM01) | (1 << CS02) | (0 << CS01) | (0 << CS00);
	//TCCR2 |= (1 << WGM20) | (1 << COM21) | (0 << COM20) | (1 << WGM21) | (0 << CS22) | (1 << CS21) | (1 << CS00);
	TCCR3A |= (1 << COM3A1) | (0 << COM3A0) | (1 << WGM31) | (1 << WGM30);
	TCCR3B |= (1 << WGM33) | (1 << WGM32) | (1 << CS31);
	
	OCR0 = 125;
	//OCR2 = 125;
	OCR3A = 0x7000;
	
	//TIMSK |= (1 << OCIE0);
	//ETIMSK |= (1 << OCIE3A);
	
	sei();
}

uint8_t GET_BUTTON_STATE_0(void)
{
	static uint8_t state_previous = 1, state_current;
	state_current = (PINF & 0x01);
	_delay_ms(10);
	if( state_current != state_previous)
	{
		state_previous = state_current;
		if(state_current == 0)
		{
			return 1;
		}
	}
	return 0;
}
uint8_t GET_BUTTON_STATE_1(void)
{
	static uint8_t state_previous = 1, state_current;
	state_current = (PINF & 0x02) >> 1;
	_delay_ms(10);
	if( state_current != state_previous)
	{
		state_previous = state_current;
		if(state_current == 0)
		{
			return 1;
		}
	}
	return 0;
}
uint8_t GET_BUTTON_STATE_2(void)
{
	static uint8_t state_previous = 1, state_current;
	state_current = (PINF & 0x04) >> 2;
	_delay_ms(10);
	if( state_current != state_previous)
	{
		state_previous = state_current;
		if(state_current == 0)
		{
			return 1;
		}
	}
	return 0;
}

void CONTROL_WITH_BUTTON(void)
{
	if(GET_BUTTON_STATE_0())
	{
		OCR0 = 0;
		//OCR2 = 0;
		OCR3A = 0;
	}
	
	if(GET_BUTTON_STATE_1())
	{
		OCR0 = 0;
		//OCR2 = 125;
		OCR3A = 0x7000;
	}
	
	if(GET_BUTTON_STATE_2())
	{
		OCR0 = 125;
		//OCR2 = 0;
		OCR3A = 0;
	}
}

int main(void)
{
	INIT_PORT();
	INIT_INTERRUPT();
	
		
    /* Replace with your application code */
    while (1) 
    {
		CONTROL_WITH_BUTTON();
		
		
		/*
		if(count == 500)
		{
			count = 0;
			state = !state;
			
			if(state)
			{
				PORTD = 0x01;
			}
			else
			PORTD = 0x00;
		}
		*/
	}
}
    