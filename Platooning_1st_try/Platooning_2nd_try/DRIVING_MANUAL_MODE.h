/*
 * DRIVING_MANUAL_MODE.h
 *
 * Created: 2018-10-02 오후 12:28:25
 *  Author: kccistc
 */ 


#ifndef DRIVING_MANUAL_MODE_H_
#define DRIVING_MANUAL_MODE_H_

#include "AllofLibrary.h"
#include "UART0.h"
#include "MOTOR.h"
#include "DRIVING_AUTO_MODE.h"

void INIT_MANUAL_MODE();
void CONTROL_DIRECTION();
void MANUAL_MODE();

enum {AUTO_DRIVE=1, STATE_STOP, STATE_GO_FORWARD,STATE_GO_BACKWARD, TURN_RIGHT, TURN_LEFT, SPEED_UP, SPEED_DOWN};


#endif /* DRIVING_MANUAL_MODE_H_ */