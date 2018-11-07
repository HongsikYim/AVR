/*
 * LED_1.cpp
 *
 * Created: 2018-09-28 오후 12:47:53
 *  Author: kccistc
 */ 

#include "LED_1.h"

LED_1::LED_1()
{
	DDRD = 0xFF;
	PORTD = 0xFF;
}

LED_1::~LED_1()
{
	
}

void LED_1::blink(int ms)
{
	PORTD = 0xFF;
	Delay_Ms(ms);
	PORTD = 0x00;
	Delay_Ms(ms);
}

void LED_1::Delay_Ms(int ms)
{
	for (int i = 0; i < ms; i ++)
	_delay_ms(1);
}