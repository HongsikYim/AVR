/*
 * 20180801_UART_practice.c
 *
 * Created: 2018-08-01 오후 2:36:54
 * Author : kccistc
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

void UART0_init(void);
void UART0_transmit(char data);
FILE OUTPUT \
	= FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);
	
void UART0_init(void)
{
	UBRR0H = 0x00;
	UBRR0L = 207;
	
	UCSR0A |= _BV(U2X0);
	UCSR0C |= 0x06;
	
	UCSR0B |= _BV(RXEN0);
	UCSR0B |= _BV(TXEN0);
}

void UART0_transmit(char data)
{
	while( !(UCSR0A & (1 << UDRE0)) );
	UDR0 = data;
}

int main(void)
{
	UART0_init();
	stdout = &OUTPUT;
	
//사용자 작성 코드 시작

	

/* 코드 4-1
	unsigned int count=0;
	while(1)
	{
		printf("%d\n\r",count++);
		_delay_ms(200);
	}
*/
	
/*코드 4-1 응용
	unsigned int count;
	unsigned int Sum = 0;
	
	printf("USART_TEST\n\r\n\r\n\r");
	printf("Add_Counter\n\r");
	
	for(count=0; count<101; count++)
	{
		printf("%d\n\r", count);
		Sum = Sum + count;
		_delay_ms(10);
	}

	printf("Total Sum(1~100):%d\n\r",Sum);
*/


	char str[100] = "Test String";
	
	printf("**Data Types...\n\r");
	printf("Interger   : %d\n\r", 128);
	printf("Float      : %f\n\r", 3.14);
	printf("String     : %s\n\r", str);
	printf("Character  : %c\n\r", 'A');
	
	while(1){}

	return 0;
	
// 사용자 작성 코드 끝
	
}