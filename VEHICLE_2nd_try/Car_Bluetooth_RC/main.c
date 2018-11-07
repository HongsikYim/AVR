/*
 * Car_Bluetooth_RC.c
 *
 * Created: 2018-10-02 오전 11:45:38
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
	uint8_t data;
	
	stdout = &OUTPUT;
	stdin = &INPUT;
	
	UART0_init();
	
    /* Replace with your application code */
    while (1) 
    {
		scanf("%c", &data);
		printf("%c", data);
    }
	return 0;
}

