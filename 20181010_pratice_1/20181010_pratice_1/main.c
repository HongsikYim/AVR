/*
 * 20181010_pratice_1.c
 *
 * Created: 2018-10-10 오전 10:39:22
 * Author : kccistc
 */ 

#define F_CPU 1600000L
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "usart.h"

static FILE usart0_stdio = FDEV_SETUP_STREAM(USART0_send, USART0_receive, _FDEV_SETUP_RW);

int main(void)
{
	char cStr[20];
	USART_init(BR9600);
	sei();

	stdin = stdout = stderr = &usart0_stdio;
	
	DDRD = 0xFF;
	
	while(1)
	{
		if(USART0_rx_check())
		{
			scanf("%s", cStr);
			printf("Received %s\n", cStr);
			
			if(strcmp(cStr, "LED1") == 0)
			{
				PORTD ^= (1 << PORTD0);	
			}
			
			if(strcmp(cStr, "LED2") == 0)
			{
				PORTD ^= (1 << PORTD1);
			}
			
			if(strcmp(cStr, "LED3") == 0)
			{
				PORTD ^= (1 << PORTD2);
			}
			
			if(strcmp(cStr, "LED4") == 0)
			{
				PORTD ^= (1 << PORTD3);
			}
		}
	}
}

