/*
 * ULTRASONIC.cpp
 *
 * Created: 2018-10-01 오전 9:37:30
 *  Author: kccistc
 */ 

#include "ULTRASONIC.h"

ULTRASONIC::ULTRASONIC()
{
	TCCR0 |= (1 << CS02) | (1 << CS01) | (1 << CS00); //8비트 타이머 0번 타이머/카운터 분주비를 1024로 설정
	
	ULTAR_DDR |= (1 << ULTRA_TRIG_1) | (1 << ULTRA_TRIG_2);
	ULTAR_DDR &= ~(1 <<ULTRA_ECHO_1) | (1 << ULTRA_TRIG_2);
}

ULTRASONIC::~ULTRASONIC()
{
	
}

void ULTRASONIC::Trigger(void)
{
	//트리거 핀으로 펄스 출력
	ULTRA_PORT &= ~(1 << ULTRA_TRIG_1) | (1 << ULTRA_TRIG_2);
	_delay_us(1);
	ULTRA_PORT |= (1 << ULTRA_TRIG_1) | (1 << ULTRA_TRIG_2);
	_delay_us(10);
	ULTRA_PORT &= ~(1 << ULTRA_TRIG_1) | (1 << ULTRA_TRIG_2);
}

uint8_t ULTRASONIC::measure_distance_1(void)
{
	ULTRASONIC ultrasonic;
	
	ultrasonic.Trigger();
	
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

uint8_t ULTRASONIC::measure_distance_2(void)
{
	ULTRASONIC ultrasonic;
	
	ultrasonic.Trigger();
	
	TCNT0 = 0;
	while(!(ULTRA_PIN & (1 << ULTRA_ECHO_2))) // echo pin이 high가 될 때까지 대기
	{
		if(TCNT0 > 255)
		return 0;
	}
	
	TCNT1 = 0;
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