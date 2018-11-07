/*
 * VEHICLE_4th_try.c
 *
 * Created: 2018-10-10 오후 3:26:57
 * Author : kccistc
 */ 


#ifndef	__USART_H__
#define	__USART_H__

#include "AllofLibrary.h"

#define	USART0	((unsigned char)0)
#define	USART1	((unsigned char)1)
#define	LENGTH_RX_BUFFER	20
#define	LENGTH_TX_BUFFER	20

#define BR9600		103
#define BR57600		16
#define BR115200	8

extern	void USART_init(unsigned int ubrr_baud);
extern	int USART0_send(char data, FILE *stream);
extern	int USART0_receive(FILE *stream);
extern	int	USART0_rx_check(void);
void UART0_printf_string(char *str);

#endif
