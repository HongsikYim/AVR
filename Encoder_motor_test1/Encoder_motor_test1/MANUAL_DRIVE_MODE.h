/*
 * MANUAL_DRIVE_MODE.h
 *
 * Created: 2018-11-02 오후 4:50:45
 *  Author: kccistc
 */ 


#ifndef MANUAL_DRIVE_MODE_H_
#define MANUAL_DRIVE_MODE_H_

#include "AllofLibrary.h"
#include "UART0.h"
#include "MOTOR.h"

void INIT_MANUAL_MODE();
void SELECTE_DIRECTION();
void MANUAL_MODE();

enum {STATE_STOP=1, STATE_GO_FORWARD,STATE_GO_BACKWARD, TURN_RIGHT, TURN_LEFT, SPEED_UP, SPEED_DOWN};


#endif /* MANUAL_DRIVE_MODE_H_ */