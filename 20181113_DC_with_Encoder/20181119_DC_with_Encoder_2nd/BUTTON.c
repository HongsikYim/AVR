/*
 * BUTTON.c
 *
 * Created: 2018-08-22 오후 3:44:06
 *  Author: kccistc
 */ 

#include "BUTTON.h"

void INIT_PORT_4_BUTTON(void)
{
	DDRF &= ~0x0F;
	PORTF = 0x0F; // pull-up resistance
}

uint8_t GET_BUTTON_STATE_0(void)
{
	static uint8_t state_previous = 1, state_current;
	state_current = (PINF & 0x01);
	//_delay_ms(10);
	if( state_current != state_previous)
	{
		state_previous = state_current;
		if(state_current == 0)
		{
			return 1;
		}
	}
	return 0;
}

uint8_t GET_BUTTON_STATE_1(void)
{
	static uint8_t state_previous = 1, state_current;
	state_current = (PINF & 0x02) >> 1;
	//_delay_ms(10);
	if( state_current != state_previous)
	{
		state_previous = state_current;
		if(state_current == 0)
		{
			return 1;
		}
	}
	return 0;
}

uint8_t GET_BUTTON_STATE_2(void)
{
	static uint8_t state_previous = 1, state_current;
	state_current = (PINF & 0x04) >> 2;
	//_delay_ms(10);
	if( state_current != state_previous)
	{
		state_previous = state_current;
		if(state_current == 0)
		{
			return 1;
		}
	}
	return 0;
}

uint8_t GET_BUTTON_STATE_3(void)
{
	static uint8_t state_previous = 1, state_current;
	state_current = (PINF & 0x08) >> 3;
	//_delay_ms(10);
	if( state_current != state_previous)
	{
		state_previous = state_current;
		if(state_current == 0)
		{
			return 1;
		}
	}
	return 0;
}