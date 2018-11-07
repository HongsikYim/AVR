/*
 * MOTOR.h
 *
 * Created: 2018-09-20 오전 10:17:15
 *  Author: kccistc
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#include "AllofLibrary.h"

void INIT_PORT_4_MOTOR();
void INIT_INTERRUPT_4_MOTOR();
void MOTOR_SPEED_UP();
void MOTOR_SPEED_DOWN();
void MOTOR_STOP();
void MOTOR_RUN_FORWARD();
void MOTOR_RUN_BACKWARD();
void MOTOR_RUN_RIGHT();
void MOTOR_RUN_LEFT();
void MOTOR_ACCELERATION();
void MOTOR_DECLERATION();


#endif /* MOTOR_H_ */