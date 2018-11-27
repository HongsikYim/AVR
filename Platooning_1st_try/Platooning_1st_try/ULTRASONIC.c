/*
 * ULTRASONIC.c
 *
 * Created: 2018-10-01 오후 5:02:21
 *  Author: kccistc
 */ 

#include "ULTRASONIC.h"

void INIT_4_ULTRASONIC(void)
{
	TCCR0 |= (1 << CS02) | (1 << CS01) | (1 << CS00); //16비트 타이머 1번 타이머/카운터 분주비를 1024로 설정
	
	ULTAR_DDR |= (1 << ULTRA_TRIG);
	ULTAR_DDR &= ~(1 <<ULTRA_ECHO);
}

void UltraSonic_Trigger(void)
{
	//트리거 핀으로 펄스 출력
	ULTRA_PORT &= ~(1 << ULTRA_TRIG);
	_delay_us(1);
	ULTRA_PORT |= (1 << ULTRA_TRIG);
	_delay_us(10);
	ULTRA_PORT &= ~(1 << ULTRA_TRIG);
}

uint8_t measure_distance(void)
{
	UltraSonic_Trigger();
	
	TCNT0 = 0;
	while(!(ULTRA_PIN & (1 << ULTRA_ECHO))) // echo pin이 high가 될 때까지 대기
	{
		if(TCNT0 > 255)
		return 0;
	}
	
	TCNT0 = 0;
	while(ULTRA_PIN & (1 << ULTRA_ECHO))
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