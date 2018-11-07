/*
 * Encoder_motor_test2.c
 *
 * Created: 2018-11-07 오전 9:33:17
 * Author : kccistc
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "UART0.h"
#include "MOTOR.h"

// 외부 인터럽트(INT0) 핀 설정
#define	EN_A PIND6 // A상
#define EN_B PIND7 // B상

int count = 0;

volatile state_INT6 = 0;
volatile state_INT7 = 0;

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL, UART0_receive, _FDEV_SETUP_READ);

ISR(INT6_vect);
ISR(INT7_vect);

int main(void)
{
	// UART통신 printf, scanf
	stdout = &OUTPUT;
	stdin = &INPUT;
	
	UART0_init();   //보레이트 9600
	INIT_PORT_4_MOTOR();
	INIT_INTERRUPT_4_MOTOR();
	
	UART0_print_string("INIT1 Completed\r\n");
	
	DDRD = 0x00; // PORTD 입력포트 설정
	PORTD = 0x00;
	
	UART0_print_string("INIT2 Completed\r\n");
	
	EIMSK |= (1 << INT6);
	EIMSK |= (1 << INT7);
	EICRA |= (1 << ISC61) | (1 << ISC71);
	sei();
	
	UART0_print_string("INIT3 Completed\r\n");
	
	uint8_t val_portD;
	while (1)
	{
		if(state_INT6 == 1)
		{
			if(state_INT7 == 1) count ++;
			
			//else if(state_INT7 == 0) count --;
		}
		
		else if(state_INT7 == 1)
		{
			if(state_INT6 == 1) count ++;
			
			//else if(state_INT6 == 0) count --;
		}
		
		/*
		if(state_INT0 == 1)
		{
			if (state_INT2 == state_INT0) //시게방향
			{
				count ++;
			}
		}
		if(state_INT2 == 1)
		{
			if (state_INT0 == state_INT0)
			{
				count--;
			}
		}
		*/
		
		//UART0_print_1_byte_number(count);
		printf("%d, %d, ", state_INT6, state_INT7);
		printf("%d\r\n", count);

	}
}

ISR(INT6_vect)
{
	if(EN_A)
	{
		state_INT6 = (state_INT6 + 1) % 2;
	}	
}

ISR(INT7_vect)
{
	if(EN_B)
	{
		state_INT7 = (state_INT7 + 1) % 2;
	}
}