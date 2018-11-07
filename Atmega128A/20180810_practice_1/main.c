/*
 * 20180810_practice_1.c
 *
 * Created: 2018-08-10 오후 12:01:03
 * Author : kccistc
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
//#include <avr/interrupt.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include "UART0.h"

#define PORT_DATA	PORTC
#define PORT_CONTROL	PORTB
#define DDR_DATA	DDRC
#define DDR_CONTROL	DDRB

#define RS_PIN	5
#define RW_PIN	6
#define E_PIN	7

#define COMMAND_CLEAR_DISPLAY	0x01
#define COMMAND_8_BIT_MODE	0x38
#define COMMAND_16_BIT_MODE	0x28

#define COMMAND_DISPLAY_ON_OFF_BIT	7
#define COMMAND_CURSOR_ON_OFF_BIT	6
#define COMMAND_BLINK_ON_OFF_BIT	5

void LCD_pulse_enable(void)
{
	PORT_CONTROL |= (1 << E_PIN);
	_delay_ms(1);
	PORT_CONTROL &= ~(1 << E_PIN);
	_delay_ms(1);
}

void LCD_write_data(uint8_t data)
{
	PORT_CONTROL |= (1 << RS_PIN);
	PORT_DATA = data;
	LCD_pulse_enable();
	_delay_ms(2);
}

void LCD_write_command(uint8_t command)
{
	PORT_CONTROL &= ~(1 << RS_PIN);
	PORT_DATA = command;
	LCD_pulse_enable();
	_delay_ms(2);
}

void LCD_clear(void)
{
	LCD_write_command(COMMAND_CLEAR_DISPLAY);
	_delay_ms(2);
}

void LCD_init(void)
{
	_delay_ms(50);
	
	// 연결 핀을 출력을 설정
	DDR_DATA = 0xFF;
	PORT_DATA = 0x00;
	DDR_CONTROL |= (1 << RS_PIN) | (1 << RW_PIN) | (1 << E_PIN);
	
	// R/W 핀으로 LOW를 출력하여 쓰기 전용으로 사용
	PORT_CONTROL &= ~(1<< RW_PIN);
	
	LCD_write_command(COMMAND_8_BIT_MODE);
	
	uint8_t command = 0x08 | (1 << COMMAND_DISPLAY_ON_OFF_BIT);
	LCD_write_command(command);
	
	LCD_clear();
	
	LCD_write_command(0x06);
}

void LCD_write_string(char *string)
{
	uint8_t i;
	for(i = 0; string[i]; i ++)
	{
		LCD_write_data(string[i]);
	}
}

void LCD_goto_XY(uint8_t row, uint8_t col)
{
	col %= 16;
	row %= 2;
	
	uint8_t address = (0x40 * row) + col;
	uint8_t command = 0x80 + address;
	
	LCD_write_command(command);
}


/*
FILE OUTPUT \
= FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT \
= FDEV_SETUP_STREAM(NULL, UART0_receive, _FDEV_SETUP_READ);
*/

int main(void)
{
	//stdout = &OUTPUT;
	//stdin = &INPUT; // printf 사용 설정	
	//UART0_init();	// UART0 초기화
	
	LCD_init();
	
	LCD_write_string("HELLO WORLD!");
	_delay_ms(1000);
	
	LCD_clear();
	
	
	LCD_goto_XY(0, 0);
	LCD_write_data('1');
	LCD_goto_XY(0, 5);
	LCD_write_data('2');
	LCD_goto_XY(1, 0);
	LCD_write_data('3');
	LCD_goto_XY(1, 5);
	LCD_write_data('4');
	
	_delay_ms(1000);
	LCD_write_command(0x1C);
	_delay_ms(1000);
	LCD_write_command(0x1C);
	_delay_ms(1000);
	LCD_write_command(0x1C);
	_delay_ms(1000);
	LCD_write_command(0x1C);

    /* Replace with your application code */
    while (1) 
    {
    }
	return 0;
}

