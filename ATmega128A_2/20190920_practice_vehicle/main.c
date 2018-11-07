/*
 * 20190920_practice_vehicle.c
 *
 * Created: 2018-09-20 오전 9:33:09
 * Author : kccistc
 */ 

#include "AllofLibrary.h"
#include "UART0.h"
#include "MOTOR.h"
//#include "I2C_LCD.h"
//#include "led_control.h"

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL, UART0_receive, _FDEV_SETUP_READ);

enum {STATE_STOP=1, STATE_GO_FORWARD,STATE_GO_BACKWARD, TURN_RIGHT, TURN_LEFT};

void MODE(void)
{
	//모드 출력
	UART0_print_string("\r\n");
	UART0_print_string("1. Stop\r\n");
	UART0_print_string("2. Go Forward\r\n");
	UART0_print_string("3. Go Backward\r\n");
	UART0_print_string("4. Right\r\n");
	UART0_print_string("5. Left\r\n");
	UART0_print_string("> ");
}

void BLUETOOTH_conection(void)
{
	//uint8_t data_4_bluetooth;
}

int main(void)
{
	uint8_t select_mode=0, states=0;
	
	stdout = &OUTPUT;
	stdin = &INPUT;
	
	UART0_init();   //보레이트 9600
	INIT_PORT_4_MOTOR();
	INIT_INTERRUPT_4_MOTOR();
	//I2C_LCD_init();
	//ledinit();
	
	//I2C_LCD_write_string_XY(0, 0, "hello world!");
	
	MODE();
	states = STATE_STOP;
	
	while (1)
	{
		if (UART0_rx_check())
		{
			select_mode = UART0_receive();
			switch(select_mode)
			{
				//메뉴에서 state 입력
				case '1':
				states = STATE_STOP;
				UART0_print_string("Selected 1. STATE_STOP\r\n");
				break;
				
				case '2':
				states = STATE_GO_FORWARD;
				UART0_print_string("Selected 2. STATE_GO_FORWARD\r\n");
				break;
				
				case '3':
				states = STATE_GO_BACKWARD;
				UART0_print_string("Selected 3. STATE_GO_BACKWARD\r\n");
				break;
				
				case '4':
				states = TURN_RIGHT;
				UART0_print_string("Selected 4. TURN_RIGHT\r\n");
				break;
				
				case '5':
				states = TURN_LEFT;
				UART0_print_string("Selected 5. TURN LEFT\r\n");
				break;
				
				default:
				break;
			}
			MODE();
		}

		switch(states)
		{
			//선택한 모드 실행
			case STATE_STOP:
			OCR1A = 0;
			OCR1B = 0;
			OCR3A = 0;
			OCR3B = 0;
			break;
			
			case STATE_GO_FORWARD:
			MOTOR_RUN_FORWARD();
			break;
			
			case STATE_GO_BACKWARD:
			MOTOR_RUN_BACKWARD();
			break;
			
			case TURN_RIGHT:
			MOTOR_RUN_RIGHT();
			break;
			
			case TURN_LEFT:
			MOTOR_RUN_LEFT();
			break;
			
			default:
			break;
		}
	
	}
}