/*
 * LAUNDARY_20180822.c
 *
 * Created: 2018-08-22 오후 12:38:08
 * Author : kccistc
 */ 

#include "AllOfLibrary.h"
#include "LCD.h"
#include "BUTTON.h"
#include "MOTOR_1.h"

volatile int count = 0; // 1ms 카운팅
volatile int LED_state = 0;	// 현재 LED 상태
//volatile t_standard = 0;

char buff[20];
uint8_t hr = 00, mm = 00, ss = 00;

enum LAUNDRY_state { IDLE, WASH, DRY} L_state;


void INIT_PORT(void)
{
	DDRB = 0xF0;
	
	DDRD = 0xFF;
	PORTD = 0x00;
}

void INIT_INTERRUPT(void)
{
	//분주비 64, 고속 PWM
	TCCR0 |= (1 << WGM00) | (1 << COM01) | (0 << COM00) | (1 << WGM01) | (1 << CS02) | (0 << CS01) | (0 << CS00);
	TCCR2 |= (1 << WGM20) | (1 << COM21) | (0 << COM20) | (1 << WGM21) | (0 << CS22) | (1 << CS21) | (1 << CS00);
	
	OCR0 = 125;
	OCR2 = 125;
	
	TIMSK |= (1 << TOIE0);
	//EIMSK |= (1 << INT0);
	//EICRA |= (1 << ISC01);
	sei();
}

int main(void)
{
	uint8_t washFlag = 0, dryFlag =0;
	
	INIT_PORT();
	INIT_INTERRUPT();
	LCD_init();
	
	LCD_write_string("LAUNDARY");
	LCD_goto_XY(1,0);
	//_delay_ms(1500);

	
	/* Replace with your application code */
	while (1)
	{
		
		switch(L_state)
		{
			case IDLE:
			OCR0 = 0;
			OCR2 = 0;
			
			if (GET_BUTTON_STATE_1()) // 세탁모드
			{
				washFlag = 1;
				dryFlag = 0;
				PORTD = 0x01;
				LCD_goto_XY(1,0);
				LCD_write_string("WASH");
			}
			else if (GET_BUTTON_STATE_2()) // 탈수 모드
			{
				washFlag = 0;
				dryFlag = 1;
				PORTD = 0x02;
				LCD_goto_XY(1,0);
				LCD_write_string("DRY ");
			}
			else if (GET_BUTTON_STATE_3()) // 동작
			{
				if (washFlag)
				{
					washFlag = 0;
					dryFlag = 0;
					L_state =  WASH;
				}
				else if (dryFlag)
				{
					washFlag = 0;
					dryFlag = 0;
					L_state =  DRY;
				}
			}
			break;
			
			case WASH:
			MOTOR_WASH_MODE();
			L_state = IDLE;
			break;
			
			case DRY:
			MOTOR_DRY_MODE();
			L_state = IDLE;
			break;
		}
		
	}
	
	return 0;
}
