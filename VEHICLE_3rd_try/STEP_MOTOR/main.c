/*
 * STEP_MOTOR.c
 *
 * Created: 2018-10-10 오전 9:47:48
 * Author : kccistc
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "UART0.h"

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL, UART0_receive, _FDEV_SETUP_READ);

#define StepMotor(R)	OCR0 = R

uint8_t r;
//uint8_t i = 120;

uint8_t step_data[] = {0x01, 0x03, 0x02, 0x06, 0x04, 0x0C, 0x08, 0x09}; // 1-2상
int step_index = -1;

int count = 0;
int state = 0;

uint8_t stepForward(void)
{
	step_index ++;
	if(step_index >= 8)
	{
		step_index = 0;
	}
	return step_data[step_index];
}

uint8_t stepBackward(void)
{
	step_index --;
	if(step_index < 0)
	{
		step_index = 7;
	}
	return step_data[step_index];
}

ISR(TIMER0_COMP_vect)
{
	count ++;
	TCNT0 = 0;
	if(count == 2)
	{
		count = 0;
		state = !state;
		if(state)
		{
			PORTD = stepForward();
		}
	}
}

int main(void)
{	
	stdout = &OUTPUT;
	stdin = &INPUT;
	
	UART0_init(); //보레이트 9600
	
	DDRD = 0x0F;
	
	// 분주비 128
	TCCR0 |= (1 << CS02) | (0 << CS01) | (1 << CS00);
	TIMSK = (1 << OCIE0);
	
	// OCR0값 설정 -> 스텝모터 속도 결정(OCR값 낮을 수록 스텝모터 속도 빨라짐)
	OCR0 = 255;
	
	sei();
	
	printf("System Starts...\r\n");
	printf("input : ");
    while (1) 
    {
		if (UART0_rx_check())
		{
			scanf("%d", &r);
			StepMotor(r);
			printf("%d\r\n", r);
			printf("input : ");
		}
		/*
		for(int i = 0; i < 1024; i ++) // 1024 -> 90도 회전
		{
			PORTD = stepForward();
			_delay_ms(2);
		}
		_delay_ms(1000);
		
		for(int i = 0; i < 1024; i ++)
		{
			PORTD = stepBackward();
			_delay_ms(2);
		}
		_delay_ms(1000);
		*/
    }

	return 0;
}

