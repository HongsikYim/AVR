/*
 * MOTOR_2.h
 *
 * Created: 2018-08-28 오후 12:16:18
 *  Author: kccistc
 */ 


#ifndef MOTOR_2_H_
#define MOTOR_2_H_


#include "AllOfLibrary.h"

#define EnableMotor1()		PORTE &= ~0x04
#define DisableMotor1()		PORTE |= 0x04
#define ForwardMotor1()		PORTE &= ~0x01
#define BackwardMotor1()	PORTE |= 0x01
#define SpeedMotor1(s1)		OCR3B = s1

void INIT_PORT_4_TIMER3();
void INIT_TIMER3();

void MOTOR_CLOCKWISE_ACCELERATION_2(uint8_t Speed1);
void MOTOR_UNCLOCKWISE_ACCELERATION_2(uint8_t Speed1);

void MOTOR_CLOCKWISE_DECELERATION_2(uint8_t Speed1);
void MOTOR_UNCLOCKWISE_DECELERATION_2(uint8_t Speed1);

void MOTOR_STOP_21();


//void MOTOR_DRY_MODE_2(uint8_t Speed1);



#endif /* MOTOR_2_H_ */