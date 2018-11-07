/*
 * LED_2.h
 *
 * Created: 2018-09-28 오후 12:07:23
 *  Author: kccistc
 */ 


#ifndef LED_2_H_
#define LED_2_H_

#include "LED_1.h"

class LED_2 : public LED_1
{
	public:
	LED_2();
	~LED_2();
	void OneLED(uint8_t position);
	int var_test;
	
	protected:
	private:
};



#endif /* LED_2_H_ */