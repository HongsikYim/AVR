﻿/*
 * LED_2.cpp
 *
 * Created: 2018-09-28 오후 12:47:27
 *  Author: kccistc
 */ 

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