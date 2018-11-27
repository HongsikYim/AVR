/*
 * 20181119_DC_with_Encoder_2nd.c
 *
 * Created: 2018-11-19 오전 10:52:59
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
int Kp = 2.0;
int Ki = 0.5;
int Kd = 1.2;

int P_term;
int I_term;
int D_term;
int temp_OCR;

int ENcnt1 = 0;
int ENcnt2 = 0;
volatile int ENcnt1_temp = 0;
volatile int ENcnt2_temp = 0;
static int ENcnt1_prev = 0;
static int ENcnt2_prev = 0;
int Err1 = 0;
int Err2 = 0;
int Err1_prev = 0;
int Err2_prev = 0;
volatile int ref1 = 500;
volatile int ref2 = 0;
int ref1_velocity = 500;
int ref2_velocity = 0;
int u1 = 0;
int u2 = 0;

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL, UART0_receive, _FDEV_SETUP_READ);

ISR(TIMER0_OVF_vect) // 주기 0.001s
{
	t_count++;
	//t_statndard++;
	
	TCNT0 = 256 - 250;
}

void INTERRUPT(void)
{
	// 분주비 설정 -> 64
	TCCR0 |= (1 << CS02) | (0 << CS01) | (0 << CS00);
	TIMSK |= (1 << TOIE0);
	
	sei();
}

ISR(INT6_vect);
ISR(INT7_vect);

void PID_control();
void SpeedUp();
void SpeedDown();
void Get_Encoder();

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
	
	DDRE = 0x00;	// PORTE 외부 인터럽트 입력포트 설정
	PORTE = 0x00;	// PORTE 풀업저항 설정
	
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
		Get_Encoder();
		
		/*
		if(GET_BUTTON_STATE_2())
		{
			SpeedUp();
		}
		if(GET_BUTTON_STATE_3())
		{
			SpeedDown();
		}
		*/
		
		//PID_control();
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
}


ISR(INT6_vect)
{
	// 외부인터럽트 엔코딩 카운트
	ENcnt1_temp ++ ;
	/*
	if((PING & (1 << 4)))
	{
		ENcnt1_temp++;
	}
	else if(!(PING & (1 << 4)))
	{
		ENcnt1_temp--;
	}
	*/
}

ISR(INT7_vect)
{

}

void Get_Encoder(void)
{
	if(t_count >= 200)
	{
		printf("%d\r\n", ENcnt1); // 5V 인가 시 평균 1547~8 카운팅, OCR값 255 -> 656~7 카운팅
		// 1초마다 엔코더 카운터 수 초기화
		ENcnt1 = ENcnt1_temp;
		ENcnt1_temp = 0;
		t_count = 0;
	}
}

void PID_control(void)
{	
	// 에러 계산
	//printf("ENcnt1: %d, ", ENcnt1);
	Err1 = ref1_velocity - ENcnt1;
	printf("Err1 : %d, ", Err1);
	
	// PID 계산
	P_term = Kp*Err1;
	//printf("P_term : %d, ", P_term);
	I_term +=  Ki*Err1;
	//printf("I_term : %f, ", I_term);
	D_term = Kd*(Err1 - Err1_prev);
	//printf("D_term : %f, ", D_term);
	
	Err1_prev = Err1;
	
	//printf("u1_prev : %f, ", u1);
	u1 = P_term + I_term + D_term;
	//printf("u1 : %d, ", u1);
	
	temp_OCR = u1/2.57;
	//printf("temp_OCR: %d, ", temp_OCR);
	
	if(temp_OCR > 255)	temp_OCR = 255;
	if(temp_OCR < 0)	temp_OCR = 0;
	printf("Output: %d\r\n", temp_OCR);
	
	OCR1A = temp_OCR;


}
