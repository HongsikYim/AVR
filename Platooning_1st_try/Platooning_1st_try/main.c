/*
 * Platooning_1st_try.c
 *
 * Created: 2018-11-19 오전 9:38:06
 * Author : kccistc
 */ 

// 기본 Library 및 Header 추가
#include "AllofLibrary.h"
#include "UART0.h"
#include "MOTOR.h"
#include "ULTRASONIC.h"
#include "DRIVING_MANUAL_MODE.h"

// UART 관련
FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL, UART0_receive, _FDEV_SETUP_READ);

// Ultrasonic sensing 관련 변수
volatile unsigned int t_count = 0;
volatile char state_ultrasonic = 0;

// 함수(자세한 내용은 아래)
ISR(TIMER2_OVF_vect);			// Timer Interrupt 실행 함수
void INIT_Timer_INTERRUPT();	// Timer Interrupt 분주비 설정 함수
void Timer();					// Timer Interrupt 에 따른 상태 변화 함수
void BLUETOOTH_conection();		// Bluetooth 설정 함수 -> 사용안함

int main(void)
{
	// Ultrasonic sensing 측정값 변수
	int distance = 0;
	
	stdout = &OUTPUT;
	stdin = &INPUT;
	
	// Arduino로부터 신호 Input port 설정
	DDRD = 0x00;	// PORTG 입력포트 설정
	PORTD = 0x00;	// PORTG 풀업저항 설정
	
	UART0_init();				// BaudRate 9600 UART 통신 설정
	INIT_PORT_4_MOTOR();		// Motor PWM 출력 포트 설정
	INIT_Timer_INTERRUPT();		
	INIT_INTERRUPT_4_MOTOR();	// Motor PWM 출력 분주비 설정
	INIT_4_ULTRASONIC();		// Ultrasonic 출력 설정
	INIT_MANUAL_MODE();			// 수동주행모드 -> 사용안함 (사용시 Bluetooth 기능과 함께 사용)
	
	//CONTROL_DIRECTION();
	
	while (1)
	{
		// 초음파 센싱
		// 설정한 주기마다 Ultrasonic sensing
		Timer();
		if(state_ultrasonic == 1)
		{
			distance = measure_distance();
			//printf("distance: %d cm\r\n", distance);	// Debuging 할 때 활성화 
 		}
		
		// Platooing 주행 코드
		// 주행 환경(앞차와의 간격 유지, Image sensing 방법)에 따라 수정하여 사용
		if (distance < 0)
		{
			distance = -distance;
		}
		
		// 선두차량과 15-22cm 간격 유지
		// Image sensing에 따라 left or Right 로 이동
		if(distance <= 22 && distance >= 15)
		{
			if(PIND & (1 << 0))
			{
				MOTOR_RUN_RIGHT();
			}
			else if(PIND & (1 << 1))
			{
				MOTOR_RUN_LEFT();
			}
			else
			{
				MOTOR_STOP();
			}
		}
		
		// 선두 차량과 간격이 22cm 초과일 경우
		else if(distance >  22)
		{
			if(PIND & (1 << 0))
			{
				MOTOR_RUN_RIGHT();
			}
			else if(PIND & (1 << 1))
			{
				MOTOR_RUN_LEFT();
			}
			else
			{
				MOTOR_RUN_FORWARD();
			}
		}
		
		// 선두 차량과 간격이 15cm 미만일 경우
		else if(distance < 15)
		{
			MOTOR_RUN_BACKWARD();
		}
			
		
		//MANUAL_MODE(); // 수동주행모드일 때 활성화
	}
}

ISR(TIMER2_OVF_vect)		// 2번 타이머, 주기 0.001s
{
	t_count++;
	
	TCNT2 = 256 - 250;		// (64/16,000,000)*250 = 0.001(second) 
}

void INIT_Timer_INTERRUPT(void)
{
	// BaudRate 설정 -> 64
	TCCR2 |= (0 << CS22) | (1 << CS21) | (1 << CS20);
	TIMSK |= (1 << TOIE2);
	
	sei();
}

void Timer(void)
{
	if(t_count >= 150) // 150ms 주기로 상태 변화
	{
		state_ultrasonic = (state_ultrasonic + 1) % 2;
		t_count = 0;
	}
}

void BLUETOOTH_conection(void)
{
	uint8_t data_4_bluetooth;
}