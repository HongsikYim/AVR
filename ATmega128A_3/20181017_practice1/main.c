/*
 * 20181017_practice1.c
 *
 * Created: 2018-10-17 오전 9:34:15
 * Author : kccistc
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "UART0.h"

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL, UART0_receive, _FDEV_SETUP_READ);

// 타이머 인터럽트 변수
volatile int count = 0;
uint8_t hr=12, mm=00, ss=00, ms=00;

// LED 관련 배열, 변수
enum {LED1=1, LED2, LED3, LED4, LED5, LED6, LED7, LED8};
uint8_t click = 0, states = 0;
uint8_t sts_LED = 0;

// 온도, 습도 변수
uint8_t temperature = 0, humidity = 0;

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

int main(void)
{
	stdin = &INPUT;
	stdout = &OUTPUT;
	
	UART0_init();
	INTERRUPT();
	
	DDRD = 0xFF;
	PORTD = 0x00;
	
    /* Replace with your application code */
    while (1) 
    {
		// 1초 주기로 온도, 습도 센싱
		if(ms > 100)
		{
			temperature ++;
			humidity ++;
			printf("temp, %d, humid, %d\r\n", temperature, humidity);
			
			ms = 0;
		}
		
		if(UART0_rx_check())
		{

			//LED 점등
			click = UART0_receive();
			switch(click)
			{
				//
				case '1':
				states = LED1;
				PORTD ^= (1 << PORTD0);
				if((PORTD & 0x01) == 0x01)
				{
					UART0_print_string("LED,1,ON\r\n");
				}
				else
				{
					UART0_print_string("LED,1,OFF\r\n");
				}
				break;
				
				case '2':
				states =LED2;
				PORTD ^= (1 << PORTD1);
				if((PORTD & 0x02) == 0x02)
				{
					UART0_print_string("LED,2,ON\r\n");
				}
				else
				{
					UART0_print_string("LED,2,OFF\r\n");
				}
				break;
				
				case '3':
				states = LED3;
				PORTD ^= (1 << PORTD2);
				if(PORTD == 0x04)
				{
					UART0_print_string("LED,3,ON\r\n");
				}
				else
				{
					UART0_print_string("LED,3,OFF\r\n");
				}
				break;
				
				case '4':
				states = LED4;
				PORTD ^= (1 << PORTD3);
				if(PORTD == 0x08)
				{
					UART0_print_string("LED,4,ON\r\n");
				}
				else
				{
					UART0_print_string("LED,4,OFF\r\n");
				}
				break;
				
				case '5':
				states = LED5;
				PORTD ^= (1 << PORTD4);
				if(PORTD == 0x10)
				{
					UART0_print_string("LED,5,ON\r\n");
				}
				else
				{
					UART0_print_string("LED,5,OFF\r\n");
				}
				break;
				
				case '6':
				states = LED6;
				PORTD ^= (1 << PORTD5);
				if(PORTD == 0x20)
				{
					UART0_print_string("LED,6,ON\r\n");
				}
				else
				{
					UART0_print_string("LED,6,OFF\r\n");
				}
				break;
				
				case '7':
				states = LED7;
				PORTD ^= (1 << PORTD6);
				if(PORTD == 0x40)
				{
					UART0_print_string("LED,7,ON\r\n");
				}
				else
				{
					UART0_print_string("LED,7,OFF\r\n");
				}
				break;
				
				case '8':
				states = LED8;
				PORTD ^= (1 << PORTD7);
				if(PORTD == 0x80)
				{
					UART0_print_string("LED,8,ON\r\n");
				}
				else
				{
					UART0_print_string("LED,8,OFF\r\n");
				}
				break;
				
				default:
				break;
			}
			
		}
	}
}

