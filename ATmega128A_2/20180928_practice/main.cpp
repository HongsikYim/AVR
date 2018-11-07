/*
 * 20180928_practice.c
 *
 * Created: 2018-09-28 오전 11:35:17
 * Author : kccistc
 */ 

#define  F_CPU 16000000L
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "LED_1.h"
#include "LED_2.h"
#include "UART0.h"

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL, UART0_receive, _FDEV_SETUP_READ);

int main(void)
{
	UART0 uart0;
	LED_2 Led_2;
	
	sei();
	
	uart0.print_string("Hello World!\n\r");
	
    /* Replace with your application code */
    while (1) 
    {
		for(int i = 0; i < 8; i ++)
		{
			Led_2.OneLED(i);
			_delay_ms(100);
		}
    }
}

