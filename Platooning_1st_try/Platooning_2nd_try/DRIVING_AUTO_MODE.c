/*
 * DRIVING_AUTO_MODE.c
 *
 * Created: 2018-11-19 오전 10:25:02
 *  Author: kccistc
 */ 

#include "DRIVING_AUTO_MODE.h"

void AUTO_MODE(void)
{
	// 차량거리 12-20cm로 유지
	if(distance < 25 && distance > 18)
	{
		MOTOR_STOP();
	}
	else if(distance <= 18)
	{
		MOTOR_RUN_BACKWARD();
	}
	else if(distance >=  25)
	{
		MOTOR_RUN_FORWARD();
	}
}