/*
* 20180801.c
*
* Created: 2018-08-01 오전 9:51:54
* Author : kccistc
*/

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	/* Replace with your application code */
	
	/*
	#ifdef LED_Button
	DDRB |= 0x07;
	DDRF &= ~0x07;
	
	PORTF |= 0x01;
	
	while(1)
	{
		PORTB = (PINF & 0x07);
	}
	#endif
	*/
	
	char a=1, b=4, c=30, d=40;
	int i;
	
	DDRD = 0xFF;
	PORTD = 0xFF;
	
	
	while(1)
	{
		PORTD = 101%10;
		_delay_ms(100);
		PORTD = 101/10;
		_delay_ms(20);
		PORTD = 127%16;
		_delay_ms(30);
		
	}

	return 0;		
}