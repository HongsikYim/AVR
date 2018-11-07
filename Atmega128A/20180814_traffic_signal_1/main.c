/*
 * 20180814_traffic_signal_1.c
 *
 * Created: 2018-08-14 오후 12:28:24
 * Author : kccistc
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include "LCD.h"
#include <stdio.h>
#include <util/delay.h>

#define RowRed 0
#define RowYellow 1
#define RowGreen 2
#define ColGreen 3
#define ColYellow 4
#define ColRed 5

volatile int count = 0;
volatile int t_standard = 0;

uint8_t MODE = 8;

char day = 1;
char buff[30];
uint8_t hr=12, mm=00, ss=00, ms=00;

enum {RG = 0, RY, GR, YR};
uint8_t signal_state = RG;

ISR(TIMER0_OVF_vect)
{
	count++;
	if(count == 10)
	{
		count = 0;
		ms++;
	}
	TCNT0 = 256 - 250;
}

void INTERRUPT(void)
{
	//인터럽트
	TCCR0 |= (1 << CS02) | (0 << CS01) | (0 << CS00); // 분주비
	TIMSK |= (1 << TOIE0);
	
	sei();
}

void CLOCK(void)
{
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
		t_standard++;
		if(t_standard >= 10)
		{
			t_standard = 0;
		}
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

void LCD_DISPLAY(void)
{
	//LCD_DISPLAY
	LCD_goto_XY(1,0);
	sprintf(buff, "%02d:%02d:%02d:%02d", hr, mm, ss, ms);
	LCD_write_string(buff);
	
	if(day)
	LCD_write_string(" AM");
	if(day == 0)
	LCD_write_string(" PM");
}

void TRAFFIC_SIGNAL(void)
{
	//신호등
	DDRD = 0xFF;
	PORTD = 0xFF;
	
	switch(signal_state)
	{
		case RG :
		PORTD = (1 << RowRed) | (1 << ColGreen);
		LCD_goto_XY(0,12);
		LCD_write_string("R/");
		LCD_goto_XY(0,14);
		LCD_write_string("G");
		if(t_standard >= 4 && t_standard < 5)
		signal_state = RY;
		break;
		
		case RY :
		PORTD = (1 << RowRed) | (1 << ColYellow);
		LCD_goto_XY(0,12);
		LCD_write_string("R/");
		LCD_goto_XY(0,14);
		LCD_write_string("Y");
		if(t_standard >= 5 && t_standard < 9)
		signal_state = GR;
		break;
		
		case GR :
		PORTD = (1 << RowGreen) | (1 << ColRed);
		LCD_goto_XY(0,12);
		LCD_write_string("G/");
		LCD_goto_XY(0,14);
		LCD_write_string("R");
		if(t_standard >= 9 && t_standard < 10)
		signal_state = YR;
		break;
		
		case YR :
		PORTD = (1 << RowYellow) | (1 << ColRed);
		PORTD = 0x22;
		LCD_goto_XY(0,12);
		LCD_write_string("Y/");
		LCD_goto_XY(0,14);
		LCD_write_string("R");
		if(t_standard < 4 && t_standard >= 0)//
		signal_state = RG;
		break;
	}
	
	/*
	if(t_standard < 4)
	{
		PORTD = 0x09;
		LCD_goto_XY(0,12);
		LCD_write_string("R/");
		LCD_goto_XY(0,14);
		LCD_write_string("G");
	}
	if(t_standard >= 4 && t_standard < 5)
	{
		PORTD = 0x11;
		LCD_goto_XY(0,12);
		LCD_write_string("R/");
		LCD_goto_XY(0,14);
		LCD_write_string("Y");
	}
	if(t_standard >= 5 && t_standard < 9)
	{
		PORTD = 0x24;
		LCD_goto_XY(0,12);
		LCD_write_string("G/");
		LCD_goto_XY(0,14);
		LCD_write_string("R");
	}
	if(t_standard >= 9 && t_standard < 10)
	{
		PORTD = 0x22;
		LCD_goto_XY(0,12);
		LCD_write_string("Y/");
		LCD_goto_XY(0,14);
		LCD_write_string("R");
	}
	if(t_standard >= 10)
	{
		t_standard = 0;
	}
	*/
}


int main(void)
{
	//LCD
	LCD_init();
	
	LCD_write_string("Trf_Signal:");
	_delay_ms(1500);
	
	//인터럽트
	INTERRUPT();
	
	/* Replace with your application code */
	while (1)
	{
		//시계
		CLOCK();
		
		//화면
		LCD_DISPLAY();
		
		//신호등
		TRAFFIC_SIGNAL();

	}
	
	return 0;
}

