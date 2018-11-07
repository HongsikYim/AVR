/*
 * 20180928_practice3.cpp
 *
 * Created: 2018-09-28 오후 2:23:14
 * Author : kccistc
 */ 

#define  F_CPU 16000000L
#include "AllofLibrary.h"
#include "LED_1.h"
#include "LED_2.h"
#include "UART0.h"
#include "MOTOR.h"
#include "ULTRASONIC.h"

// FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);
// FILE INPUT = FDEV_SETUP_STREAM(NULL, UART0_receive, _FDEV_SETUP_READ);

using namespace std;

uint8_t select_mode=0, states=0;

UART0 uart0;
MOTOR motor;
ULTRASONIC ultrasonic;

enum {STATE_IDLE=1, STATE_GO_FORWARD,STATE_GO_BACKWARD, TURN_RIGHT, TURN_LEFT};

void MODE();
void BLUETOOTH_conection();
void STATE();

int main(void)
{
	uint8_t distance_1, distance_2;
	
	sei();
	
	//stdout = &OUTPUT;
	//stdin = &INPUT;
	
	//MODE();
	
	//states = STATE_IDLE;
	
	while (1)
	{
		distance_1 = ultrasonic.measure_distance_1();
		distance_2 = ultrasonic.measure_distance_2();
		
		uart0.print_string("d1 = ");
		uart0.print_1_byte_number(distance_1);
		uart0.print_string("  / ");
		
		uart0.print_string("d2 = ");
		uart0.print_1_byte_number(distance_2);
		
		_delay_ms(500);
		
		
		//STATE();
	}
}

void MODE(void)
{
	//모드 출력
	uart0.print_string("\r\n");
	uart0.print_string("1. Stop\r\n");
	uart0.print_string("2. Go Forward\r\n");
	uart0.print_string("3. Go Backward\r\n");
	uart0.print_string("4. Right\r\n");
	uart0.print_string("5. Left\r\n");
	uart0.print_string("> ");
}

void BLUETOOTH_conection(void)
{
	//uint8_t data_4_bluetooth;
}

void STATE(void)
{
	
	
	if (uart0.rx_check())
	{
		select_mode = uart0.receive();
		switch(select_mode)
		{
			//메뉴에서 state 입력
			case '1':
			states = STATE_IDLE;
			uart0.print_string("Selected 1. STATE_IDLE\r\n");
			break;
			
			case '2':
			states = STATE_GO_FORWARD;
			uart0.print_string("Selected 2. STATE_GO_FORWARD\r\n");
			break;
			
			case '3':
			states = STATE_GO_BACKWARD;
			uart0.print_string("Selected 3. STATE_GO_BACKWARD\r\n");
			break;
			
			case '4':
			states = TURN_RIGHT;
			uart0.print_string("Selected 4. TURN_RIGHT\r\n");
			break;
			
			case '5':
			states = TURN_LEFT;
			uart0.print_string("Selected 5. TURN LEFT\r\n");
			break;
			
			default:
			break;
		}
		MODE();
	}

	switch(states)
	{
		//선택한 모드 실행
		case STATE_IDLE:
		motor.IDLE();
		break;
		
		case STATE_GO_FORWARD:
		motor.RUN_FORWARD();
		_delay_us(20);
		states = STATE_IDLE;
		break;
		
		case STATE_GO_BACKWARD:
		motor.RUN_BACKWARD();
		_delay_us(20);
		states = STATE_IDLE;
		break;
		
		case TURN_RIGHT:
		motor.RUN_RIGHT();
		break;
		
		case TURN_LEFT:
		motor.RUN_LEFT();
		break;
		
		default:
		break;
	}
}