/*
 * VEHICLE_3rd_try.c
 *
 * Created: 2018-10-04 오전 9:25:56
 * Author : kccistc
 */ 

#include "AllofLibrary.h"
#include "UART0.h"
#include "MOTOR.h"
#include "ULTRASONIC.h"
#include "DRIVING_MANUAL_MODE.h"
#include "led_control.h"
#include "SERVO_MOTOR.h"

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL, UART0_receive, _FDEV_SETUP_READ);

void BLUETOOTH_conection();

int main(void)
{
	uint8_t distance_1, distance_2;
	
	stdout = &OUTPUT;
	stdin = &INPUT;
	
	UART0_init();   //보레이트 9600
	INIT_PORT_4_MOTOR();
	INIT_INTERRUPT_4_MOTOR();
	INTIT_4_ULTRASONIC();
	INIT_MANUAL_MODE();
	
	//SELECTE_DIRECTION();
	
	while (1)
	{
		//MANUAL_MODE();
		
		distance_2 = measure_distance_2();
		printf("distance: %d cm  \r\n", distance_2);
		printf("d");
		
		MOTOR_RUN_FORWARD();
		
		if(distance_1 < 20)
		{
			MOTOR_STOP();
			MOTOR_RUN_RIGHT();
			
		}
		
	}
}

void BLUETOOTH_conection(void)
{
	uint8_t data_4_bluetooth;
}