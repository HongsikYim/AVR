/*
 * 20180911_practice.c
 *
 * Created: 2018-09-11 오전 9:49:12
 * Author : kccistc
 */ 
#define TERMINATOR '\r'

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "I2C_LCD.h"
#include "UART0.h"
#include "led_control.h"

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL, UART0_receive, _FDEV_SETUP_READ);

void menu(void)
{
	UART0_print_string("\r\n");
	UART0_print_string("1. LED OFF\r\n");
	UART0_print_string("2. LED ON\r\n");
	UART0_print_string("3. LED BLINK\r\n");
	UART0_print_string("> ");
}

enum {LED_OFF=1, LED_ON, LED_BLINK};

int main(void)
{
	uint8_t select_menu=0, states=0;
	
	I2C_LCD_init();
	UART0_init();   //보레이트 9600
	ledinit();
	
	I2C_LCD_write_string_XY(0, 0, "hello world!");
	
	menu();
	states = LED_OFF;
	
	while (1)
	{
		if (UART0_rx_check())
		{
			select_menu = UART0_receive();
			switch(select_menu)
			{
				case '1':
				states = LED_OFF;
				UART0_print_string("Selected 1. LED OFF\r\n");
				break;
				case '2':
				states = LED_ON;
				UART0_print_string("Selected 2. LED ON\r\n");
				break;
				case '3':
				states = LED_BLINK;
				UART0_print_string("Selected 3. LED BLINK\r\n");
				break;
				default:
				break;
			}
			menu();
		}
		
		switch(states)
		{
			case LED_OFF:
			ledoff();
			break;
			case LED_ON:
			ledon();
			break;
			case LED_BLINK:
			ledblink();
			break;
			default:
			break;
		}
	}
}

