/*
 * BUTTON.h
 *
 * Created: 2018-08-22 오후 3:44:48
 *  Author: kccistc
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_


#include "AllOfLibrary.h"

void INIT_PORT_4_BUTTON();

uint8_t GET_BUTTON_STATE_0();
uint8_t GET_BUTTON_STATE_1();
uint8_t GET_BUTTON_STATE_2();
uint8_t GET_BUTTON_STATE_3();


#endif /* BUTTON_H_ */