/*
 * LED_2.cpp
 *
 * Created: 2018-09-28 오후 2:25:50
 *  Author: kccistc
 */ 

#include "LED_2.h"

LED_2::LED_2()
{
	
}

LED_2::~LED_2()
{

}

void LED_2::OneLED(uint8_t position)
{
	if(position > 7)
	{
		position = 7;
	}
	PORTD = (1 << position);
}