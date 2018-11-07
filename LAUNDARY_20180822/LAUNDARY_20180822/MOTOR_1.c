/*
 * MOTOR_1.c
 *
 * Created: 2018-08-22 오후 4:00:07
 *  Author: kccistc
 */ 

#include "MOTOR_1.h"


void MOTOR_ACCELERATION(void)
{
	for(OCR0 = 0; OCR0 <= 200; OCR0 ++)
	{
		_delay_ms(20);
	}
}

void MOTOR_DECLERATION(void)
{
	for(OCR0 = 200; OCR0 > 0; OCR0 --)
	{
		_delay_ms(20);
	}
}

void MOTOR_RUN_CLOWISE(void)
{
	OCR0 = 0;
	OCR2 = 150;
}

void MOTOR_RUN_UNCLOWISE(void)
{
	OCR0 = 150;
	OCR2 = 0;
}

void MOTOR_WASH_MODE(void)
{
	for(int i = 0; i < 5; i ++)
	{
		MOTOR_RUN_CLOWISE();
		_delay_ms(1000);
		MOTOR_RUN_UNCLOWISE();
		_delay_ms(1000);
	}
}

void MOTOR_DRY_MODE(void)
{
	MOTOR_ACCELERATION();
	_delay_ms(3000);
	MOTOR_DECLERATION();
}