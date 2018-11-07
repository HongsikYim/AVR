/*
 * CFile1.c
 *
 * Created: 2018-08-01 오전 9:42:32
 *  Author: kccistc
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

//unsigned char circular_shift_left(unsigned char pattern)
//{
//	return( (pattern<<1)|(pattern>>7) );
//}

int main(void)
{
	/* Replace with your application code */

	/* 20280730 LED 번갈아 깜박이기	
	DDRA |= 0x01; // PA0 핀을 출력으로 설정
	DDRB |= 0x01;
	

	while(1)
	{
		
		PORTA |= 0x01; // PA0 핀에 연결된 LED 켜기
		PORTB &= ~0x01; // 0.5초 대기
		_delay_ms(500);
		
		PORTA &= ~0x01; // PA0 핀에 연결된 LED 끄기
		PORTB |= 0x01;
		_delay_ms(500);
	}
		*/

	/* 20280731 LED 패턴만들기_1
	DDRB = 0xFF;
		
	while(1)
	{
		PORTB = 0x00;
		_delay_ms(1000);
		PORTB = 0xFF;
		_delay_ms(1000);
	}
	*/
	
	/* 20180731 LED 비트 시프트_패턴 값 저장
	unsigned char cuurnet_pattern_value;
	unsigned char next_pattern_value = 0x01;
	
	DDRB = 0xFF; // 포트B 핀을 출력으로 설정
	
	while(1)
	{
		cuurnet_pattern_value = next_pattern_value;
		
		PORTB = cuurnet_pattern_value; // 현재 패턴 표시
		
		//다음 패턴 값 생성
		next_pattern_value = cuurnet_pattern_value << 1;
		if(next_pattern_value == 0) next_pattern_value = 0x01;
		
		_delay_ms(500);
	}
	*/
	
	/* 20180731 LED 비트 시프트 패턴_1개의 패턴 값 저장
	unsigned char pattern_value = 0x01;
	DDRB = 0xFF;
	
	while(1)
	{
		PORTB = pattern_value;
		
		//다음 패턴 값 생성
		pattern_value <<= 1;
		if(pattern_value == 0) pattern_value = 0x01;
		
		_delay_ms(500);
	}
	*/
	
	/*
	unsigned char patterns[] = {0xA0, 0x50, 0x28, 0x14, 0x0A, 0x05, 0x82, 0x41};
	
	int index = 0;
	DDRB = 0xFF;
	
	while(1)
	{
		PORTB = patterns[index];
		index = (index+1)%8;
		
		_delay_ms(1000);
	}
    */
	
	/* 버튼으로 LED 컨트롤
	DDRB |= 0x07;
	DDRF &= ~0x07;
	
	PORTF |= 0x01;
	
	while(1)
	{
		
		PORTB = (PORTB & 0xF8)+(PINF & 0x07);
		
	}
	*/
	
	/*
	DDRB = 0xFF;
	DDRF &= ~0x04;
	
	unsigned char pattern = 0x01;
	unsigned char state_previous = 0, state_current;
	PORTB = pattern;
	
	while(1)
	{
		state_current = (PINF & 0x04) >> 2;
		if( state_current == 1 && state_previous == 0 )
		{
			_delay_ms(30);
			pattern = circular_shift_left(pattern);
			PORTB = pattern;
		}
		state_previous = state_current;	
	}
	*/
	
	/* 리뷰테스트_1
	unsigned char patterns[2][8] = { {0xA0, 0x50, 0x28, 0x14, 0x0A, 0x05, 0x82, 0x41}, {0xA0, 0x50, 0x28, 0x14, 0x0A, 0x05, 0x82, 0x41} };
	
	int i, j;
	
	DDRB = 0xFF;
	
	for(i=0; i<2; i++)
	{
		for(j=0; j<8; j++)
		{
			PORTB = patterns[i][j];
			_delay_ms(1000);
		}
	}
	*/
	
	/* 리뷰 테스트_2
	DDRB |= 0xE0;
	DDRF &= ~0x07;
	PORTF |= 0x01;
	
	while(1)
	{
	
		PORTB = (PORTB & 0x1F)+((PINF & 0x07)<<5);
	}
	*/

	return 0;
}