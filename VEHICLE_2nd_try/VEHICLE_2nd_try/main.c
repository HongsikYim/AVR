/*
 * VEHICLE_2nd_try.c
 *
 * Created: 2018-10-02 오전 8:58:33
 * Author : kccistc
 */ 

#include "AllofLibrary.h"
#include "UART0.h"
#include "MOTOR.h"
#include "ULTRASONIC.h"
#include "DRIVING_MANUAL_MODE.h"

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL, UART0_receive, _FDEV_SETUP_READ);

void BLUETOOTH_conection();

int main(void)
{
	stdout = &OUTPUT;
	stdin = &INPUT;
	
	UART0_init();   //보레이트 9600
	INIT_PORT_4_MOTOR();
	INIT_INTERRUPT_4_MOTOR();
	INTIT_4_ULTRASONIC();
	INIT_MANUAL_MODE();
	
	SELECTE_DIRECTION();
	
	while (1)
	{
		MANUAL_MODE();
	}
}

void BLUETOOTH_conection(void)
{
	uint8_t data_4_bluetooth;
}




