/*
 * Encoder_motor_test1.c
 *
 * Created: 2018-11-02 오후 4:45:55
 * Author : kccistc
 */ 

#include "AllofLibrary.h"
#include "UART0.h"
#include "MOTOR.h"
#include "MANUAL_DRIVE_MODE.h"
#include <avr/interrupt.h>

#define	EN_A PIND0 // A상, 외부 인터럽트 핀 번호
#define EN_B PIND2 // B상, 인터럽트 0

uint8_t count = 0;


FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL, UART0_receive, _FDEV_SETUP_READ);


ISR(INT0_vect)
{
	if(EN_A)
	{
		count --;
	}
}

ISR(INT2_vect)
{
	if(EN_B)
	{
		count ++;
	}
}


int main(void)
{
	stdout = &OUTPUT;
	stdin = &INPUT;
	
	UART0_init();   //보레이트 9600
	INIT_PORT_4_MOTOR();
	INIT_INTERRUPT_4_MOTOR();
	INIT_MANUAL_MODE();
	
	UART0_print_string("INIT1 Completed\r\n");
	
	DDRD = 0x00;
	PORTD = 0x00;
	
	
	UART0_print_string("INIT2 Completed\r\n");
	
	ETIMSK |= (1 << INT0);
	ETIMSK |= (1 << INT2);
	EICRA |= (1 << ISC01);
	sei();
	
	
	UART0_print_string("INIT3 Completed\r\n");
	
	SELECTE_DIRECTION();
	
	while (1)
	{
		MANUAL_MODE();
		
		//UART0_print_1_byte_number(count);
		//printf("%d\r\n", count);
		//_delay_ms(500);
	}
}