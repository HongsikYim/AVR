/*
 * SERVO_MOTOR.h
 *
 * Created: 2018-10-04 오후 6:29:58
 *  Author: kccistc
 */ 


#ifndef SERVO_MOTOR_H_
#define SERVO_MOTOR_H_

#include "AllofLibrary.h"
#define ROTATION_DELAY	1000
#define PULSE_MIN		50
#define PULSE_MID		150
#define PULSE_MAX		250

void INIT_SERVO(void);
void ROTATE_SERVO(void);

#endif /* SERVO_MOTOR_H_ */