/*
 * 20181002_practice_2.c
 *
 * Created: 2018-10-02 오후 3:38:10
 * Author : kccistc
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <stdio.h>
#include "UART0.h"

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL, UART0_receive, _FDEV_SETUP_READ);

int main(void)
{
	UART0_init();
	
	DDRG = 0xFF;
	PORTG = 0xFF;
	
	stdout = &OUTPUT;
	stdin = &INPUT;
	
	char message[10];
	char data;
    /* Replace with your application code */
    while (1) 
    {
		//scanf("%s", message);
		if( UART0_rx_check())
		{
			data = UART0_receive();
			printf("%c", data);
			//if(strcmp(message, "1") == 0)
			if(data == '1')
			{
				PORTG = 0xFF;
				UART0_print_1_byte_number(data);
			}
			if(data == '2')
			{
				PORTG = 0x00;
				UART0_print_1_byte_number(data);
			}
		}
		
		
    }
}

