/*
 * Encoder_motor_test2.c
 *
 * Created: 2018-11-07 오전 9:33:17
 * Author : kccistc
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "UART0.h"
#include "MOTOR.h"

// 외부 인터럽트(INT0) 핀 설정
#define	EN_A PINE6 // 모터1의 엔코더 신호1, 다른 하나는 PORTG에 연결
#define EN_B PINE7 // 모터2의 엔코더 신호1, 다른 하나는 PORTG에 연결
#define ENCODER_PIN	PINE

#define Ts			0.002
#define PPR			26
#define GEAR_RATIO	50

int pwm_val1, pwm_val2;
int ENcnt1 = 0;
int ENcnt2 = 0;
static int ENcnt1_old = 0;
static int ENcnt2_old = 0;
int diff_ENcnt1 = 0;
int diff_ENcnt2 = 0;
double Err1 = 0;
double Err2 = 0;
double Err1_prev = 0.0;
double Err2_prev = 0.0;
double ref1 = 0.0;
double ref2 = 0.0;
double u1 = 0;
double u2 = 0;
double angular_velocity1 = 0.0;
double angular_velocity2 = 0.0;
double CONV_PARAM = 0.0;

volatile state_INT6 = 0;
volatile state_INT7 = 0;

char edge1, edge2;

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL, UART0_receive, _FDEV_SETUP_READ);

ISR(INT6_vect);
ISR(INT7_vect);
void PID_control();

int main(void)
{
	// UART통신 printf, scanf
	stdout = &OUTPUT;
	stdin = &INPUT;
	
	UART0_init();   //보레이트 9600
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
	
	CONV_PARAM = 60/(Ts*GEAR_RATIO*4);
	
	while (1)
	{
		//UART0_print_1_byte_number(count);
		//printf("%d, %d, ", state_INT6, state_INT7);
		printf("%f\r\n", angular_velocity1);
	}
}


ISR(INT6_vect)
{
	if((PING & (1 << 4)))
	{
		ENcnt1++;
	}
	else // if(ENCODER_PIN & (1 << EN_B))
	{
		ENcnt1--;
	}
	
	PID_control();
}

ISR(INT7_vect)
{
	
}

void PID_control(void)
{
	diff_ENcnt1 = ENcnt1 - ENcnt1_old;
	angular_velocity1 = CONV_PARAM * ENcnt1;
	
	Err1 = ref1 - angular_velocity1;
	u1 = u1 + 0.04295*Err1 - 0.04245*Err1_prev;
	Err1_prev = Err1;
	
	if(u1 > 12)
	{
		u1 = 12;
	}
	else if(u1 < 0)
	{
		u1 = 0;
	}
	
	pwm_val1 = u1*1000/12;
	ENcnt1_old = ENcnt1;
}