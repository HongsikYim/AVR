/*
 * Platooning_2nd_try.c
 *
 * Created: 2018-11-21 오전 9:20:54
 * Author : kccistc
 */ 

#include "AllofLibrary.h"
#include "UART0.h"
#include "MOTOR.h"
#include "ULTRASONIC.h"
#include "DRIVING_MANUAL_MODE.h"
#include "DRIVING_AUTO_MODE.h"

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL, UART0_receive, _FDEV_SETUP_READ);

volatile unsigned int t_count = 0;
volatile char state_ultrasonic = 0;
extern uint8_t distance = 0;

ISR(TIMER2_OVF_vect);
ISR(INT0_vect);
ISR(INT1_vect);
ISR(INT2_vect);
ISR(INT3_vect);

void INIT_Timer_INTERRUPT();
void Timer();
void BLUETOOTH_conection();

int main(void)
{
	
	
	stdout = &OUTPUT;
	stdin = &INPUT;
	
	DDRD = 0x00;	// 엔코더 입력포트 설정
	PORTD = 0x00;	// PORTG 풀업저항 설정
	
	UART0_init();   //보레이트 9600
	INIT_PORT_4_MOTOR();
	INIT_Timer_INTERRUPT();
	INIT_INTERRUPT_4_MOTOR();
	INIT_4_ULTRASONIC();
	INIT_MANUAL_MODE();
	
	//CONTROL_DIRECTION();
	
	while (1)
	{
		// 초음파 센싱
		Timer();
		if(state_ultrasonic == 1)
		{
			distance = measure_distance();
			//printf("distance: %d cm\r\n", distance);
		}
		
		AUTO_MODE();
		
		//MANUAL_MODE();
	}
}

ISR(TIMER2_OVF_vect) // 2번 타이머, 주기 0.001s
{
	t_count++;
	
	TCNT2 = 256 - 250;
}

void INIT_Timer_INTERRUPT(void)
{
	// 분주비 설정 -> 64
	TCCR2 |= (0 << CS22) | (1 << CS21) | (1 << CS20);
	TIMSK |= (1 << TOIE2);
	
	sei();
}

void Timer(void)
{
	if(t_count >= 100) // 100ms 주기
	{
		state_ultrasonic = (state_ultrasonic + 1) % 2;
		//printf("state: %d, \r\n", state_ultrasonic);
		t_count = 0;
	}
}

ISR(INT0_vect)
{
	MOTOR_RUN_RIGHT();
}

ISR(INT1_vect)
{
	MOTOR_RUN_LEFT();
}

ISR(INT2_vect)
{
	MOTOR_RUN_FORWARD();
}

ISR(INT3_vect)
{
	MOTOR_RUN_BACKWARD();
}

void BLUETOOTH_conection(void)
{
	uint8_t data_4_bluetooth;
}