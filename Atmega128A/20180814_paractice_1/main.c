/*
 * 20180814_paractice_1.c
 *
 * Created: 2018-08-14 오전 9:57:49
 * Author : kccistc
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include "LCD.h"
#include <stdio.h>
#include <util/delay.h>

volatile int count = 0;
volatile int state = 0;

char day = 1;
char buff[30];
uint8_t hr=12, mm=00, ss=00, ms=00;

ISR(TIMER0_OVF_vect)
{
	count++;
	if(count == 5)
	{
		count = 0;
		state = !state;
		if(state)
		{
			ms++;
		}
		
	}
	TCNT0 = 256 - 250;
}

int main(void)
{
	//LCD
	LCD_init();
	
	LCD_write_string("Hongsik's Clock");
	_delay_ms(1500);
	
	//인터럽트
	//DDRD = 0xFF;
	//PORTD = 0x00;
	
	TCCR0 |= (1 << CS02) | (0 << CS01) | (0 << CS00); // 분주비
	TIMSK |= (1 << TOIE0);
	
	sei();
	
	
	
    /* Replace with your application code */
    while (1) 
    {
		//LCD
		LCD_goto_XY(1,0);
		sprintf(buff, "%02d:%02d:%02d:%02d", hr, mm, ss, ms);
		LCD_write_string(buff);
		
		if(day == 1)
		LCD_write_string(" AM");
		if(day == 0)
		LCD_write_string(" PM");
		
		
		//시계
		if(hr >= 12)
		{
			hr=0;
			day = ~day;
		}
		
		if (ms > 100)
		{
			ms=0;
			ss++;
			if (ss >= 60)
			{
				ss=0;
				mm++;
				if (mm >= 60)
				{
					hr++;
					mm=00;
					if(hr >= 12)
					{
						hr=0;
						ss=0;
						day = ~day;
					}
				}
			}
		}
	}
	
	return 0;
}

