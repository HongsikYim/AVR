/*
 * DRIVING_MANUAL_MODE.c
 *
 * Created: 2018-10-02 오후 12:28:05
 *  Author: kccistc
 */ 

#include "DRIVING_MANUAL_MODE.h"

uint8_t select_mode=0, states=0;


void INIT_MANUAL_MODE(void)
{
	states = AUTO_DRIVE;
}

// 디버깅용
void CONTROL_DIRECTION(void)
{
	//모드 출력
	UART0_print_string("\r\n");
	UART0_print_string("1. Stop\r\n");
	UART0_print_string("2. Forward\r\n");
	UART0_print_string("3. Backward\r\n");
	UART0_print_string("4. Right\r\n");
	UART0_print_string("5. Left\r\n");
	UART0_print_string("6. Speed Up\r\n");
	UART0_print_string("7. Speed Down\r\n");
}

void MANUAL_MODE(void)
{	
	/*
	if (UART0_rx_check() == 0)// 무 입력 상태에서는 정지 상태
	{
		states = STATE_STOP;
	}
	*/
	
	if (UART0_rx_check())
	{
		select_mode = UART0_receive();
		switch(select_mode)
		{
			//메뉴에서 state 입력
			case '0':
			states = AUTO_DRIVE;
			break;
			
			case '1':
			states = STATE_STOP;
			//UART0_print_string("Selected 1. STATE_STOP\r\n");
			break;
			
			case '2':
			states = STATE_GO_FORWARD;
			//UART0_print_string("Selected 2. STATE_GO_FORWARD\r\n");
			break;
			
			case '3':
			states = STATE_GO_BACKWARD;
			//UART0_print_string("Selected 3. STATE_GO_BACKWARD\r\n");
			break;
			
			case '4':
			states = TURN_RIGHT;
			//UART0_print_string("Selected 4. TURN_RIGHT\r\n");
			break;
			
			case '5':
			states = TURN_LEFT;
			//UART0_print_string("Selected 5. TURN LEFT\r\n");
			break;
			
			case '6':
			states = SPEED_UP;
			//UART0_print_string("Selected 6. SPEED UP\r\n");
			break;
			
			case '7':
			states = SPEED_DOWN;
			//UART0_print_string("Selected 7. SPEED DOWN\r\n");
			break;
			
			default:
			break;
		}
		//SELECTE_DIRECTION();
	}

	switch(states)
	{
		//선택한 모드 실행
		case STATE_STOP:
		MOTOR_STOP();
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
		
		case SPEED_UP:
		MOTOR_SPEED_UP();
		break;
		
		case SPEED_DOWN:
		MOTOR_SPEED_DOWN();
		break;
		
		default:
		break;
	}
}