﻿/*
 * LCD.h
 *
 * Created: 2018-08-22 오후 12:40:16
 *  Author: kccistc
 */ 


#ifndef LCD_H_
#define LCD_H_


#include "AllOfLibrary.h"

#define PORT_DATA		PORTC
#define PORT_CONTROL	PORTA
#define DDR_DATA		DDRC
#define DDR_CONTROL		DDRA

#define RS_PIN	5
#define RW_PIN	6
#define E_PIN	7

#define COMMAND_CLEAR_DISPLAY	0x01
#define COMMAND_8_BIT_MODE	0x38
#define COMMAND_16_BIT_MODE	0x28

#define COMMAND_DISPLAY_ON_OFF_BIT 2
#define COMMAND_CURSOR_ON_OFF_BIT 1
#define COMMAND_BLINK_ON_OFF_BIT 0

void LCD_pulse_enable(void);
void LCD_write_data(uint8_t data);
void LCD_write_command(uint8_t command);
void LCD_clear(void);
void LCD_init(void);
void LCD_write_string(char *string);
void LCD_goto_XY(uint8_t row, uint8_t col);


#endif /* LCD_H_ */