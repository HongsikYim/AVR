/*
 * LED_1.h
 *
 * Created: 2018-09-28 오전 11:56:28
 *  Author: kccistc
 */ 


#ifndef LED_1_H_
#define LED_1_H_

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

class LED_1
{
	public:
		LED_1();
		~LED_1();
		void blink(int ms);
		int var_test;
	
	private:
		void Delay_Ms(int ms);
	
};

#endif /* LED_1_H_ */