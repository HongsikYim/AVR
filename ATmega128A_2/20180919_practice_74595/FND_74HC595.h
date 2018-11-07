/*
 * FND.h
 *
 * Created: 2018-09-14 오후 4:56:46
 *  Author: kccistc
 */ 


#ifndef FND_74HC595_H_
#define FND_74HC595_H_

#include <avr/io.h>
#include <util/delay.h>

#define FND_DATA_DDR		DDRB   // FND Data Port
#define FND_CONTROL_DDR		DDRB   // FND Control Port
#define FND_DATA_PORT		PORTB   // FND Data Port
#define FND_CONTROL_PORT	PORTB   // FND Control Port


void FND_init(void);
void displayFND(uint8_t position, uint8_t number);
void displayNumber(int count);

#endif /* FND_74HC595_H_ */