#define F_CPU	16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "usart.h"
#include "UART1.h"
#include "PWM.h"

static FILE usart0_stdio = FDEV_SETUP_STREAM(USART0_send, USART0_receive, _FDEV_SETUP_RW);

ISR(TIMER1_COMPA_vect)
{
	TCNT1 = 0;
}

int	main(void)
{
	char cStr[100];
	char buff_motor;
	int count=0;
	int j = 0;
	USART_init(BR9600);		//UBRR=103: 9600,  USART0 보오레이트 : 115200(UBRR=8), 16MHz
	UART1_init(BR9600_1);
	sei();
	PWM_init();
	DDRB = 0xff;
	DDRE = 0xff;
	DDRA = 0xf0;
	
	//PORTB = 0x20;
	//PORTE = 0x10;
	
	OCR1A = 400;  //top 0xff;
	OCR1B = 100;  //PB6 에서 25%duty
	OCR3A = 400;
	OCR3B = 100;  //PE4 에서 25%duty

	
	
	
	stdin = stdout = stderr = &usart0_stdio;
	//printf("Hello World\r\n");	// USART0에 테스트문자 출력
	//UART1_print_string("hello bluetooth\r\n");
	printf("1.GO\r\n2.RIGHT\r\n3.LEFT\r\n4.STOP\r\n5.BACK\r\nSelect Num>\r\n");
	printf("6.FULL SPEED\r\n7.FULL SPEED RIGHT\r\n8.FULL SPEED LEFT\r\n9.FULL SPEED BACK\r\nSelect Num>\r\n");
	//printf("float : %f\r\n", 3.14f);	// USART0에 테스트문자 출력
	
	while(1){
		if(USART0_rx_check())
		{
			buff_motor = USART0_receive();
			//scanf("%s", cStr);	// 정수 x 입력
			//printf("Received %s\n", cStr);
			
			if (buff_motor == '1')
			{
				//PORTB = 0x20;
				//PORTE = 0x10;
				OCR1A = 100;
				OCR1B = 0;
				
				OCR3A = 100;
				OCR3B = 0;
				
				//OCR1A = 0xff;
				//OCR3A = 0xff;
				printf("%d\r\n",buff_motor-48);
				buff_motor = '0';
				printf("\r\nGO\r\n");
			}
			else if (buff_motor == '2')
			{
				//PORTB = 0x00;
				//PORTE = 0x10;
				OCR1A = 0;
				OCR1B = 0;
				
				OCR3A = 100;
				OCR3B = 0;
				//OCR1A = 0x00;
				//OCR3A = 0xff;
				printf("%d\r\n",buff_motor-48);
				buff_motor = '0';
				printf("\r\nRIGHT\r\n");
			}
			else if (buff_motor == '3')
			{
				//PORTB = 0x20;
				//PORTE = 0x00;
				OCR1A = 100;
				OCR1B = 0;
				
				OCR3A = 0;
				OCR3B = 0;
				//OCR1A = 0xff;
				//OCR3A = 0x0000;
				printf("%d\r\n",buff_motor-48);
				buff_motor = '0';
				printf("\r\nLEFT\r\n");
			}
			else if (buff_motor == '4')
			{
				//PORTB = 0x00;
				//PORTE = 0x00;
				OCR1A = 0;
				OCR1B = 0;
				
				OCR3A = 0;
				OCR3B = 0;
				//OCR1A = 0x00;
				//OCR3A = 0x00;
				printf("%d\r\n",buff_motor-48);
				buff_motor = '0';
				printf("\r\nSTOP\r\n");
			}
			else if (buff_motor == '5')
			{
				//PORTB = 0x40;
				//PORTE = 0x08;
				OCR1A = 0;
				OCR1B = 100;
				
				OCR3A = 0;
				OCR3B = 100;
				
				printf("%d\r\n",buff_motor-48);
				buff_motor = '0';
				printf("\r\nBACK\r\n");
			}
			else if (buff_motor == '6')
			{
				//PORTB = 0x40;
				//PORTE = 0x08;
				OCR1A = 0xff;
				OCR1B = 0;
				
				OCR3A = 0xff;
				OCR3B = 0;
				
				printf("%d\r\n",buff_motor-48);
				buff_motor = '0';
				printf("\r\nFULL SPEED\r\n");
			}
			else if (buff_motor == '7')
			{
				//PORTB = 0x40;
				//PORTE = 0x08;
				OCR1A = 0xff;
				OCR1B = 0;
				
				OCR3A = 0;
				OCR3B = 0;
				
				printf("%d\r\n",buff_motor-48);
				buff_motor = '0';
				printf("\r\nFULL SPEED Right\r\n");
			}
			else if (buff_motor == '8')
			{
				//PORTB = 0x40;
				//PORTE = 0x08;
				OCR1A = 0;
				OCR1B = 0;
				
				OCR3A = 0xff;
				OCR3B = 0;
				
				printf("%d\r\n",buff_motor-48);
				buff_motor = '0';
				printf("\r\nFULL SPEED Left\r\n");
			}
			else if (buff_motor == '9')
			{
				//PORTB = 0x40;
				//PORTE = 0x08;
				OCR1A = 0;
				OCR1B = 0xff;
				
				OCR3A = 0;
				OCR3B = 0xff;
				
				printf("%d\r\n",buff_motor-48);
				buff_motor = '0';
				printf("\r\nFULL SPEED BACK\r\n");
			}
			
		}
	}

	return 0;
}
