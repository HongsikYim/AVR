/*
 * 20180802_practice_1.c
 *
 * Created: 2018-08-02 오후 4:45:38
 * Author : kccistc
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
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
	
	while(1)
	{
	char str[50]="";
	scanf("%s", str);
	
	printf("Before: %s\n\r",str);
	for(int i=0; i <50; i++)
	{
		if((str[i]>='a') && (str[i]<='z'))//if(islower(str[i]))
		{
			str[i] -= 0x20;
		}
		else if((str[i]>='A') && (str[i]<='Z'))//if(isupper(str[i]))
		{
			str[i] += 0x20;
		}
	}
	printf("After: ");
	printf(str, "%s");
	printf("\n\r");
	}
    return 0;
}

