/*
 * STEP_MOTOR.c
 *
 * Created: 2018-10-10 오후 3:40:19
 *  Author: kccistc
 */ 


#include "STEP_MOTOR.h"

uint8_t step_data[] = {0x01, 0x03, 0x02, 0x06, 0x04, 0x0C, 0x08, 0x09};
int step_index = -1;

void INIT_STEP_MOTOR(void)
{
	DDRC = 0x0F;
}

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

void STEP_UNCLOCKWISE_90(void)
{
	for(int i = 0; i < 1024; i ++) // 1024 -> 90도 회전
	{
		PORTC = stepForward();
		_delay_ms(2);
	}
	step_index = -1;
}

void STEP_CLOCKWISE_90(void)
{
	for(int i = 0; i < 1024; i ++)
	{
		PORTC = stepBackward();
		_delay_ms(2);
	}
	step_index = -1;
}

void STEP_UNCLOCKWISE_180(void)
{
	for(int i = 0; i < 2048; i ++) // 1024 -> 90도 회전
	{
		PORTC = stepForward();
		_delay_ms(2);
	}
	step_index = -1;
}

void STEP_CLOCKWISE_180(void)
{
	for(int i = 0; i < 2048; i ++)
	{
		PORTC = stepBackward();
		_delay_ms(2);
	}
	step_index = -1;
}