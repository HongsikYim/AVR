/*
 * 20180802_practice_2.c
 *
 * Created: 2018-08-02 오후 7:45:01
 * Author : kccistc
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

char circular_shift_left_1(char pattern_1)
{
	char new_pattern_1 = (pattern_1 >> 7) | (pattern_1 << 1);
	
	return new_pattern_1;
}

char circular_shift_left_2(char pattern_2)
{
	char new_pattern_2 = (pattern_2 >> 7) | (pattern_2 << 1);
	
	return new_pattern_2;
}


int main(void)
{
	char pattern_1 = 0x01;
	char pattern_2 = 0x01;
	
	DDRB = 0xFF;
	DDRD = 0xFF;
	
	PORTD = pattern_2;
	
    while (1)
    {
			
			PORTB = pattern_1;
			pattern_1 = circular_shift_left_1(pattern_1);
			_delay_ms(200);
			if(PORTB == 0x80)
			{
				pattern_2 = circular_shift_left_2(pattern_2);
				PORTD = pattern_2;
			}
			
    }
	return 0;
}

