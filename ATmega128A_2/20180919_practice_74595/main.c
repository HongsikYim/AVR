/*
 * 20180919_practice_74595.c
 *
 * Created: 2018-09-19 오후 3:46:29
 * Author : kccistc
 */ 

#define F_CPU	16000000L

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "UART0.h"
#include "FND_74HC595.h"

//bit 위치의 비트를 1 또는 0으로 설정하기 위한 매크로 함수
#define set_bit(bit)	(PORTC |= _BV(bit))
#define clear_bit(bit)	(PORTC &= ~_BV(bit))

//ATmega128A의 포트 C에 연결된 위치
#define DATA		0
#define LATCH_CLOCK	1
#define SHIFT_CLOCK	2

volatile unsigned int FndValue = 0;

static FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);
static FILE INPUT = FDEV_SETUP_STREAM(NULL, UART0_receive, _FDEV_SETUP_READ);

void SetFndValue(int value)
{
	FndValue = value;
}

void ShiftClock(void)
{
	set_bit(SHIFT_CLOCK);
	clear_bit(SHIFT_CLOCK);
}

void LatchClock(void)
{
	set_bit(LATCH_CLOCK);
	clear_bit(LATCH_CLOCK);
}

void ByteDataWrite(uint8_t data)
{
	for(uint8_t i = 0; i < 8; i ++)
	{
		if(data & 0b10000000)
		set_bit(DATA);
		else
		clear_bit(DATA);
		
		ShiftClock();
		data = data << 1;
	}
	LatchClock();
}


int main(void)
{
	stdout = &OUTPUT;
	stdin = &INPUT;
	
	UART0_init();
	FND_init();
	
	//제어 및 데어티 핀을 출력으로 설정
	DDRB |= _BV(SHIFT_CLOCK) | _BV(LATCH_CLOCK) | _BV(DATA);
	
	//uint8_t index = 0;
	unsigned int count = 0;
	
	/* Replace with your application code */
	while (1)
	{
		SetFndValue(count);
		count ++;
		_delay_ms(100);
		
		/*
		uint8_t pattern = 1 << index;
		index = (index + 1) % 8;
		
		uint8_t num[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x67};
		
		ByteDataWrite(num[index]);
		_delay_ms(500);
		*/
	}
	return 0;
}