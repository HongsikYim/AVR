/*
 * UART0.h
 *
 * Created: 2018-09-28 오후 2:19:03
 *  Author: kccistc
 */ 


#ifndef UART0_H_
#define UART0_H_

#define	LENGTH_RX0_BUFFER	20
#define	LENGTH_TX0_BUFFER	20

#define BR9600		103
#define BR57600		16
#define BR115200	8


class UART0
{
	public:
	UART0();
	
	~UART0();
	
	
	void print_string(char *str);
	void transmit(char data);
	int receive(FILE *stream);
	int	rx_check(void);
	
	protected:
	private:
	void UART0_init(unsigned int ubrr_baud);

	
};


#endif /* UART0_H_ */