/*
 * 20181113_DC_with_Encoder.c
 *
 * Created: 2018-11-13 오전 9:32:49
 * Author : kccistc
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "UART0.h"
#include "MOTOR.h"
#include "BUTTON.h"

// 외부 인터럽트(INT0) 핀 설정
#define	EN_A PINE6 // 모터1의 엔코더 신호1, 다른 하나는 PORTG에 연결
#define EN_B PINE7 // 모터2의 엔코더 신호1, 다른 하나는 PORTG에 연결
#define ENCODER_PIN	PINE

// 0번 카운터 설정
volatile float t_count = 0;
volatile float t_statndard = 0;

// Motor Specification
#define Ts			0.002
#define PPR			26
#define GEAR_RATIO	210
#define RPM			75.0

// PID Controller 변수 설정
float Kp = 3.0;
float Ki = 1.0;
float Kd = 2.0;

float P_term;
float I_term;
float D_term;
unsigned int temp_OCR;

float dT = 0.0;
float ENcnt_t1 = 0.001;
float ENcnt_t2 = 0;
static float ENcnt1_prev = 0.001;
static float ENcnt2_prev = 0;
float ENcnt_t1_prev = 0;
float ENcnt_t2_prev = 0;
float Err1 = 0;
float Err2 = 0;
float Err1_prev = 0.0;
float Err2_prev = 0.0;
volatile uint8_t ref1 = 255;
volatile uint8_t ref2 = 0;
float ref1_velocity = 0.0;
float ref2_velocity = 0.0;
float u1 = 0;
float u2 = 0;
float angular_velocity1 = 0.0;
float angular_velocity2 = 0.0;

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL, UART0_receive, _FDEV_SETUP_READ);

ISR(TIMER0_OVF_vect) // 주기 0.000001s
{
	//t_count++;
	t_statndard++;
	
	TCNT0 = 256 - 2;
}

void INTERRUPT(void)
{
	// 분주비 설정 -> 8
	TCCR0 |= (0 << CS02) | (1 << CS01) | (0 << CS00);
	TIMSK |= (1 << TOIE0);
	
	sei();
}

ISR(INT6_vect);
ISR(INT7_vect);
void PID_control();
void SpeedUp();
void SpeedDown();

int main(void)
{
	// UART통신 printf, scanf
	stdout = &OUTPUT;
	stdin = &INPUT;
	
	UART0_init();   //보레이트 9600
	INTERRUPT();
	INIT_PORT_4_MOTOR();
	INIT_INTERRUPT_4_MOTOR();

	
	UART0_print_string("INIT1 Completed\r\n");
	
	DDRE = 0x00;	// PORTD 입력포트 설정
	PORTE = 0x00;	// PORTD 풀업저항 설정
	
	DDRG = 0x00;	// 엔코더 입력포트 설정
	PORTG = 0xFF;	// PORTG 풀업저항 설정
	
	UART0_print_string("INIT2 Completed\r\n");
	
	EIMSK |= (1 << INT6);
	EIMSK |= (1 << INT7);
	EICRB |= (1 << ISC61) | (1 << ISC71) | (1 << ISC60) | (1 << ISC70); // 상승엣지 인터럽트 발생
	sei();
	
	UART0_print_string("INIT3 Completed\r\n");
	
	while (1)
	{
		if(GET_BUTTON_STATE_2())
		{
			SpeedUp();
		}
		if(GET_BUTTON_STATE_3())
		{
			SpeedDown();
		}

		PID_control();
	}
}

void SpeedUp(void)
{
	uint8_t i;
	i ++;
	if(i > 250)
	{
		i = 250;
	}
	ref1 = i;
	printf("ref1 : %d\r\n", ref1);
}

void SpeedDown(void)
{
	uint8_t j;
	j --;
	if(j <= 0)
	{
		j = 0;
	}
	ref1 = j;
	printf("ref1 : %d\r\n", ref1);
}


ISR(INT6_vect)
{
	// 외부인터럽트 발생 시 시간 저장
	ENcnt_t1 = t_statndard;
}

ISR(INT7_vect)
{
	
}

void PID_control(void)
{
	// 엔코더 펄스 주기
	dT = (ENcnt_t1 - ENcnt_t1_prev)*0.000001;
	//printf("ENcnt_t1 : %f, ", ENcnt_t1);
	//printf("ENcnt_t1_prev : %f, ", ENcnt_t1_prev);
	//printf("dT : %f, ", dT);
	
	// 각속도 계산, 기어비x7x2, rad/sec
	angular_velocity1 = (2*M_PI)/(210*7*2*dT);
	//printf("angular velocity : %f, ", angular_velocity1);
	//diff_ENcnt1 = ENcnt1 - ENcnt1_prev;
	
	// 에러 계산
	//printf("ref1 : %d, ", ref1);
	ref1_velocity = (RPM*ref1/255)*((2*M_PI)/60);
	//printf("ref1_velocity : %f, ", ref1_velocity);
	Err1 = angular_velocity1 - ref1_velocity;
	//printf("Err1 : %f, ", Err1);
	
	// PID 계산
	P_term = - Kp*Err1;
	//printf("P_term : %f, ", P_term);
	I_term =  Ki*dT*(Err1+Err1_prev)/2;
	//printf("I_term : %f, ", I_term);
	D_term = Kd*(Err1 - Err1_prev)/dT;
	//printf("D_term : %f, ", D_term);
	
	Err1_prev = Err1;
	ENcnt_t1_prev = ENcnt_t1;
	
	//printf("u1_prev : %f, ", u1);
	u1 = P_term + I_term + D_term;
	//printf("u1 : %f\r\n", u1);
	
	temp_OCR = 34.46*u1;
	printf("%d\r\n", temp_OCR);
	
	if(temp_OCR > 255)	temp_OCR = 255;
	if(temp_OCR < 0)	temp_OCR = 0;
	
	OCR1A = temp_OCR;

}
