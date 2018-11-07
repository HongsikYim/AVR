/*
 * 20180810_practice_3.c
 *
 * Created: 2018-08-10 오후 5:40:02
 * Author : kccistc
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "LCD.h"

volatile int count = 0;
volatile int state = 0;	// 현재 LED 상태
volatile int hr_alrm, mm_alrm, ss_alrm;
volatile int num;

ISR(TIMER0_COMP_vect)
{
	count++;
	TCNT0 = 0;
	if (count == num)
	{
		count = 0;
		state = !state;
		if(state) PORTD = 0xFF;
		_delay_ms(2000);
		else PORTD = 0x00;
	}
}

void INIT_PORT(void)
{
	DDRD = 0xFF;
	PORTD = 0xFF;
}

void INIT_INT0(void)
{
	EIMSK |= (1 << INT0);
	EICRA |= (1 << ISC01);
	sei();
}

int main(void)
{
	INIT_PORT();
	INIT_INT0();
	
	char day = 1;
	char buff[20];
	uint8_t hr=12, mm=00, ss=00;
	LCD_init();
	
	
	LCD_write_string("HONG SIK's Clock");
	_delay_ms(1500);
	
	
	/* Replace with your application code */
	while (1)
	{
		LCD_goto_XY(1,0);
		sprintf(buff, "%02d:%02d:%02d", hr, mm, ss);
		LCD_write_string(buff);
		
		if(day == 1)
		LCD_write_string(" AM");
		
		if(day == 0)
		LCD_write_string(" PM");
		
		if(state ==1 )
		{
			PORTD = 0x01;
		}
		
		if(hr >= 12)
		{
			hr=0;
			day = ~day;
		}
		
		_delay_ms(1);
		ss++;
		
		if (ss >= 60 && hr < 12)
		{
			ss = 0;
			mm++;
			if (mm >= 60)
			{
				hr++;
				mm=0;
				if(hr >= 12)
				{
					hr=0;
					ss=0;
					day = ~day;
				}
			}
		}
		
		
	}
	return 0;
}
