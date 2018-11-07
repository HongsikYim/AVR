/*
 * VEHICLE_4th_try.c
 *
 * Created: 2018-10-10 오후 3:26:57
 * Author : kccistc
 */ 

#include "AllofLibrary.h"
#include "UART0.h"
#include "USART.h"
#include "MOTOR.h"
#include "ULTRASONIC.h"
#include "DRIVING_MANUAL_MODE.h"
#include "led_control.h"
#include "STEP_MOTOR.h"

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL, UART0_receive, _FDEV_SETUP_READ);

uint8_t select_drive_mode = 0, drive_mode = 0;
enum { MANUAL_DRIVE = 1, AUTO_DRIVE };
enum AUTO_MODE_sequence { S1, S2, S3, S4, S5, S6, S7, S8 } SEQUENCE;
	
	

void BLUETOOTH_conection();
void SELECTE_DRIVE_MODE();
void AUTO_MODE();

int main(void)
{
	
	stdout = &OUTPUT;
	stdin = &INPUT;
	
	UART0_init();   //보레이트 9600
	INIT_PORT_4_MOTOR();
	INIT_INTERRUPT_4_MOTOR();
	INTIT_4_ULTRASONIC();
	INIT_MANUAL_MODE();
	INIT_LED();
	INIT_STEP_MOTOR();
	
	drive_mode = MANUAL_DRIVE;
	
	SELECTE_DRIVE_MODE();
	
	while (1)
	{
		
		
		//select drive mode
		if (UART0_rx_check())
		{
			select_drive_mode = UART0_receive();
			switch(select_drive_mode)
			{
				//메뉴에서 mode 입력
				case 'm':
				drive_mode = MANUAL_DRIVE;
				UART0_print_string("Selected Manual Drive Mode\r\n");
				break;
				
				case 'a':
				drive_mode = AUTO_DRIVE;
				UART0_print_string("Selected Automatic Drive Mode\r\n");
				break;
				
				default:
				break;
			}
			SELECTE_DRIVE_MODE();
		}

		switch(drive_mode)
		{
			//선택한 모드 실행
			case MANUAL_DRIVE:
			MANUAL_MODE();
			break;
			
			case AUTO_DRIVE:
			AUTO_MODE();
			break;
			
			default:
			break;
		}

	}
}

void BLUETOOTH_conection(void)
{
	uint8_t data_4_bluetooth;
}

void SELECTE_DRIVE_MODE(void)
{
	UART0_print_string("\r\n");
	UART0_print_string("1. Manual Drive\r\n");
	UART0_print_string("2. Auto Drive\r\n");
}

void AUTO_MODE(void)
{
	uint8_t Flag1, Flag2, Flag3, Flag4, Flag5, Flag6, Flag7, Flag8;
	
	uint8_t distance_1, distance_2;
	
	distance_1 = measure_distance_1();
	distance_2 = measure_distance_2();
	
	printf("distance: %d cm  \r\n", distance_1);
	printf("distance: %d cm  \r\n", distance_2);
	
	switch(SEQUENCE)
	{
		case S1:
		MOTOR_RUN_FORWARD();
		if(distance_1 < 50)
		{
			MOTOR_STOP();
			STEP_CLOCKWISE_90();
			_delay_ms(1000);
			MOTOR_ROTATE_LEFT();
			if(distance_1 < 60 && distance_2 < 60)
			{
				if((distance_2 - distance_1)^2 < 1)
				{
					MOTOR_STOP();
					SEQUENCE = S2;
				}
			}
		}
		break;
		
		case S2:
		break;
		
		case S3:
		break;
		
		case S4:
		break;
		
		case S5:
		break;
		
		case S6:
		break;
		
		case S7:
		break;
		
		case S8:
		break;
	}
	
	
	/*
	if(distance_1 < 50)
	{
		MOTOR_STOP();
		_delay_ms(500);
		
		STEP_CLOCKWISE_90();
		
		MOTOR_ROTATE_LEFT();
		
	}
	else
	{
		MOTOR_RUN_FORWARD();
	}
	*/
}