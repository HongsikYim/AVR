/*
 * 20180806_practice_1.c
 *
 * Created: 2018-08-06 오후 6:50:11
 * Author : kccistc
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include "UART0.h"

FILE OUTPUT \
= FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT \
= FDEV_SETUP_STREAM(NULL, UART0_receive, _FDEV_SETUP_READ);

uint8_t sorting_function(uint8_t buffer[99])
{
	int new_buffer[99];
	for (int i=0; i<100; i++)
	{
		for (int j=i+1; j<100; j++)
		{
			if(buffer[i] < buffer[j])
			{
				int temp = buffer[i];
				buffer[i] = buffer[j];
				buffer[j] = temp;
			}
		}
	}
	return new_buffer[99];
}


int main(void)
{
	stdout = &OUTPUT;
	stdin = &INPUT; // printf 사용 설정
	
	UART0_init();	// UART0 초기화
	
	uint8_t counter = 0;
	uint8_t i; // 1byte짜리 자료형
	uint8_t buffer[99];//1byte짜리가 다섯개 만들고, 순서대로 넣어라.
	
	for (int i=0; i<100; i++)
	{
		buffer[i]=rand()%10000;
		printf("%4d\r\n", buffer[i]);
	}
	
	buffer[99] = sorting_function(buffer[99]);
		
	//printf("%x : %d\r\n",(buffer+i) buffer[i]);//괄호: 배열의 이름은 주소다, 
	
	
	printf("가장 작은 수는: %d\n\r", buffer[99]);
	
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

