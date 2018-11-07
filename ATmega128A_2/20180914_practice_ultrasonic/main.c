/*
 * 20180914_practice_ultrasonic.c
 *
 * Created: 2018-09-14 오전 11:04:32
 * Author : kccistc
 */ 

#define F_CPU	16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "UART0.h"

#define PRESCALER	1024
#define ULTRA_PORT	PORTG
#define ULTAR_DDR	DDRG
#define ULTRA_PIN	PING
#define ULTRA_TRIG_1	1
#define ULTRA_ECHO_1	2
#define ULTRA_TRIG_2	3
#define ULTRA_ECHO_2	4

static FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);
static FILE INPUT = FDEV_SETUP_STREAM(NULL, UART0_receive, _FDEV_SETUP_READ);

void UltraSonic_init(void)
{
	TCCR0 |= (1 << CS02) | (1 << CS01) | (1 << CS00); //16비트 타이머 1번 타이머/카운터 분주비를 1024로 설정
	
	ULTAR_DDR |= (1 << ULTRA_TRIG_1) | (1 << ULTRA_TRIG_2);
	ULTAR_DDR &= ~(1 <<ULTRA_ECHO_1) | (1 << ULTRA_TRIG_2);
}

void UltraSonic_Trigger_1(void)
{
	//트리거 핀으로 펄스 출력
	ULTRA_PORT &= ~(1 << ULTRA_TRIG_1);
	_delay_us(1);
	ULTRA_PORT |= (1 << ULTRA_TRIG_1);
	_delay_us(10);
	ULTRA_PORT &= ~(1 << ULTRA_TRIG_1);
}

void UltraSonic_Trigger_2(void)
{
	//트리거 핀으로 펄스 출력
	ULTRA_PORT &= ~(1 << ULTRA_TRIG_2);
	_delay_us(1);
	ULTRA_PORT |= (1 << ULTRA_TRIG_2);
	_delay_us(10);
	ULTRA_PORT &= ~(1 << ULTRA_TRIG_2);
}

uint8_t measure_distance_1(void)
{
	UltraSonic_Trigger_1();
	
	TCNT0 = 0;
	while(!(ULTRA_PIN & (1 << ULTRA_ECHO_1))) // echo pin이 high가 될 때까지 대기
	{
		if(TCNT0 > 255)
		return 0;
	}
	
	TCNT0 = 0;
	while(ULTRA_PIN & (1 << ULTRA_ECHO_1))
	{
		if(TCNT0 > 255)
		{
			TCNT0 = 0;
			break;
		}
	}
	
	double pulse_width = 1000000.0*TCNT0*PRESCALER/F_CPU;
	
	return pulse_width / 58;
}

uint8_t measure_distance_2(void)
{
	UltraSonic_Trigger_2();
	
	TCNT0 = 0;
	while(!(ULTRA_PIN & (1 << ULTRA_ECHO_2))) // echo pin이 high가 될 때까지 대기
	{
		if(TCNT0 > 255)
		return 0;
	}
	
	TCNT0 = 0;
	while(ULTRA_PIN & (1 << ULTRA_ECHO_2))
	{
		if(TCNT0 > 255)
		{
			TCNT0 = 0;
			break;
		}
	}
	
	double pulse_width = 1000000.0*TCNT0*PRESCALER/F_CPU;
	
	return pulse_width / 58;
}

int main(void)
{
	uint8_t distance_1, distance_2;
	
	stdout = &OUTPUT;
	stdin = &INPUT;
	
	UART0_init();
	UltraSonic_init();
	
    /* Replace with your application code */
    while (1) 
    {
		distance_1 = measure_distance_1();
		distance_2 = measure_distance_2();
		
		printf("D1: %d cm\r\n", distance_1);
		printf("D2: %d cm\r\n", distance_2);
		
		_delay_ms(500);
		
		
    }
	return 0;
}

