/*
* 20180913_practice1.c
*
* Created: 2018-09-13 오전 10:28:26
* Author : kccistc
*/


#define F_CPU	16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "UART0.h"
#include "I2C_LCD.h"

static FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);
static FILE INPUT = FDEV_SETUP_STREAM(NULL, UART0_receive, _FDEV_SETUP_READ);

void ADC_init()
{
	ADMUX |= (1<<REFS0);
	ADCSRA |= (1<<ADPS2) |  (1<<ADPS1) | (1<<ADPS0); // 분주비 128, 125khz 클록
	ADCSRA |= (1<<ADEN); // ADC 활성화
	ADCSRA |= (0<<ADFR); // 0:단일모드, 1:freerun mode
	
	//ADMUX = ((ADMUX & 0xe0) | channel);
	//ADCSRA |= (1<<ADSC);  // ADC start!
}

int read_ADC(uint8_t channel)
{
	ADMUX = ((ADMUX & 0xe0) | channel);
	ADCSRA |= (1<<ADSC);  // ADC start!
	while(!(ADCSRA & (1<<ADIF))); // 변환 종료대기
	
	return ADC;
}

int	main(void)
{
	int read, temp;
	float input_voltage;
	
	UART0_init;		//UBRR=103: 9600,  USART0 보오레이트 : 115200(UBRR=8), 16MHz
	ADC_init();  // 가변저항 선택
	I2C_LCD_init();
	
	stdout = &OUTPUT;
	stdin = &INPUT;
	
	while(1)
	{
		read = read_ADC(0);
		printf("Cds Value : %04d | ", read);
		//_delay_ms(500);
		read = read_ADC(3);
		input_voltage = read * 100.0 * 5.0 / 1024.0;
		temp = (int)input_voltage;
		// 		//printf("Var Resister Value : %04d\r\n", read);
		//printf("Temperature : %d\r\n", temp);
		printf("Temperature : %d.%d\r\n", temp/10, temp%10);
		
		_delay_ms(1000);
	}

	return 0;
}
void ADC_init(void)
{
	ADMUX |= (1 << REFS0);
	ADMUX |= ((ADMUX & 0xE0));
	
	ADCSRA |= 0x07;
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (0 << ADFR);
	ADCSRA |= (1 << ADSC);
}

int read_ADC(unsigned char channel)
{
	ADMUX |= ((ADMUX & 0xE0) | channel);
	ADCSRA |= (1 << ADSC);
	while(!(ADCSRA & (1 << ADIF)));
	return ADC;
}