/*
 * 20180807_practice_1.c
 *
 * Created: 2018-08-07 오후 6:59:19
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


int main(void)
{
	stdout = &OUTPUT;
	stdin = &INPUT; // printf 사용 설정
	
	UART0_init();	// UART0 초기화
	
	char *pChar;
	int *pInt;
	long *pLong;
	float *pFloat;
	double *pDouble; // 자료형 데이터 크기와 달리, 주소의 크기는 2byte이다.
	
	int *buffer[3] = {"ABCD", "efgh", "ijkl"}; // [A][B][C][D][null][ ][ ][ ][ ][ ]
	int *buf = "EFGH"; // 
	
	printf("%s\n\r", *buffer[0]);
	printf("%s\n\r", *buffer[1]);
	printf("%s\n\r", *buffer[2]);
	printf("%s\n\r", *buf);
	

	printf("%d\n\r", sizeof(pChar));
	printf("%d\n\r", sizeof(pInt));
	printf("%d\n\r", sizeof(pLong));
	printf("%d\n\r", sizeof(pFloat));
	printf("%d\n\r", sizeof(pDouble));
	
	
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

