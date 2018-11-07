/*
 * MOTOR.h
 *
 * Created: 2018-09-28 오후 2:30:20
 *  Author: kccistc
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#include "AllofLibrary.h"

class MOTOR
{
	public:
		MOTOR();
		~MOTOR();
		
		//void INIT_PORT_4_MOTOR();
		//void INIT_INTERRUPT_4_MOTOR();
		void IDLE();
		void RUN_FORWARD();
		void RUN_BACKWARD();
		void RUN_RIGHT();
		void RUN_LEFT();
		void ACCELERATION();
		void DECLERATION();
	
	protected:
	
	private:
	
};

#endif /* MOTOR_H_ */