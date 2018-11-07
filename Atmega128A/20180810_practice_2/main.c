/*
 * 20180810_practice_2.c
 *
 * Created: 2018-08-10 오후 2:33:08
 * Author : kccistc
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "LCD.h"


int main(void)
{
	char buff[20];
	uint8_t mm=0, ss=0, ms=0;
	LCD_init();
	
	DDRF &= ~((1 << PORTF0) | (1 << PORTF1));
	PORTF |= ((1 << PORTF0) | (1 << PORTF1)); // 풀업저항
	
	char state_pre1 = 1, state_cur1;
	char state_pre2 = 1, state_cur2;
	char LCD_stat = 1, LCD_CNT_reset = 0;
	
	LCD_write_string("STOP WATCH");
	_delay_ms(1500);
	
	
    /* Replace with your application code */
    while (1) 
    {
		LCD_goto_XY(1,0);
		sprintf(buff, "%02d:%02d:%02d", mm, ss, ms);
		LCD_write_string(buff);
		_delay_ms(1);
		
		state_cur1 = (PINF & 0x01) >> 0;
		if ( state_cur1 == 0 && state_pre1 == 1)
		{
			LCD_stat = ~LCD_stat;
		}
		state_pre1 = state_cur1;
		
		state_cur2 = (PINF & 0X02) >> 2;
		if ( state_cur2 == 0 && state_pre2 == 0)
		{
			LCD_CNT_reset = 1;
		}
		state_pre2 = state_cur2;
		
		if( LCD_CNT_reset == 1)
		{
			LCD_stat = 1;
			mm = 0;
			ss = 0;
			ms = 0;
			LCD_CNT_reset = 0;
		}
		
		if (LCD_stat |= 1) ms++;
		
		if (ms >= 100)
		{
			ms = 0;
			ss++;
			if (ss >= 60)
			{
				mm++;
				ss=0;
			}
		}
		
    }
	return 0;
}


