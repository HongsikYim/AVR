/*
 * 20180802.c
 *
 * Created: 2018-08-02 오전 9:26:45
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


/*
#define set_bit(value, bit) ( _SFR_BYTE(value) |= _BV(bit) )
#define clear_bit(value, bit) ( _SFR_BYTE(value) &= ~_BV(bit) )
#define invert_bit(value, bit) ( _SFR_BYTE(value) ^= _BV(bit) )
#define read_bit(value, bit) ( (_SFR_BYTE(value) & _BV(bit)) >> bit )

#define BINARY_PATTERN "0b%d%d%d%d%d%d%d%d"
#define BYTE2BINARY(byte) \
(byte & 0x80 ? 1:0), \
(byte & 0x40 ? 1:0), \
(byte & 0x20 ? 1:0), \
(byte & 0x10 ? 1:0), \
(byte & 0x08 ? 1:0), \
(byte & 0x04 ? 1:0), \
(byte & 0x02 ? 1:0), \
(byte & 0x01 ? 1:0)
*/


int main(void)
{
	uint8_t counter = 100;
	char buffer[20] = "";
	
	stdout = &OUTPUT;
	stdin = &INPUT; // printf 사용 설정
	
	UART0_init();	// UART0 초기화
	
	printf("Current Counter Value : ");
	printf("%d\n\r", counter);
	
	while(1)
	{
		scanf("%s", buffer);	//문자열 수신
		
		if(strcasecmp(buffer, "DOWN") == 0)
		{
			counter--;
			printf("Current Coounter value : ");
			printf("%d\n\r", counter);
		}
		else if(strcasecmp(buffer, "UP") == 0)
		{
			counter++;
			printf("Current Coounter value : ");
			printf("%d\n\r", counter);
		}
		else
		{
			printf("** Unknown Command **\n\r");
		}
	}
	
	/* 배열사용_오름차순, 내림차순
	int no[10] = {25, 41, 11, 8, 90, 87, 37, 52, 73, 63};
	
	for (int i=0; i<9; i++)
	{
		for (int j=i+1; j<10; j++)
		{
			if(no[i] < no[j])
			{
				int temp = no[i];
				no[i] = no[j];
				no[j] = temp;
			}
		}
	}
	
	for (int i=0; i<10; i++)
	{
		printf("%d\n\r", no[i]);
	}
	
	char str[100] = "Test String";
	printf("%s\n\r", str);
	sprintf(str, "The first element in array is %d", no[0]);
	printf("%s\n\r", str);
	
	*/
	
	/*비트 매크로
	unsigned char value = 0b000111;
	printf("Original	  : "BINARY_PATTERN"\n\r", BYTE2BINARY(value));
	
	//bit set
	set_bit(value, 6);
	printf("Set 7th bit   : "BINARY_PATTERN"\n\r", BYTE2BINARY(value));
	//bit clear
	clear_bit(value, 2);
	printf("Clear 3rd bit : "BINARY_PATTERN"\n\r", BYTE2BINARY(value));
	//bit invert
	invert_bit(value, 0);
	printf("Invert 1st bit: "BINARY_PATTERN"\n\r", BYTE2BINARY(value));
	int read = read_bit(value, 5);
	printf("6th bit is    : %d\n\r", read);
	*/
	
	/*
	char str[] = "Test using UART0 Library";
	uint8_t num = 128;
	
	UART0_print_string(str);
	UART0_print_string("\n\r");
	
	UART0_print_1_byte_number(num);
	UART0_print_string("\n\r");
	*/
	
	
    return 0;
}