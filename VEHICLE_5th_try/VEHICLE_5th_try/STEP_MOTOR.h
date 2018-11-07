/*
 * STEP_MOTOR.h
 *
 * Created: 2018-10-10 오후 3:40:32
 *  Author: kccistc
 */ 


#ifndef STEP_MOTOR_H_
#define STEP_MOTOR_H_


#include "AllofLibrary.h"



void INIT_STEP_MOTOR(void);
uint8_t stepForward(void);
uint8_t stepBackward(void);
void STEP_CLOCKWISE_90(void);
void STEP_UNCLOCKWISE_90(void);
void STEP_CLOCKWISE_180(void);
void STEP_UNCLOCKWISE_180(void);



#endif /* STEP_MOTOR_H_ */