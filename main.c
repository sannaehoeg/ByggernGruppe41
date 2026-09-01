/*
 * Byggern41.c
 *
 * Created: 31.08.2026 14:22:18
 * Author : sannaeh
 */ 

#define F_CPU 16000000
#define BAUD 9600
#define BAUDVAL F_CPU/16/BAUD-1

#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"

int main(void)
{
    /* Replace with your application code */
	/*DDRC |= (1<<PC0);*/
	
	DDRD &= ~(1<<PD0); 
	DDRD |= (1<<PD1);
	
	USART_init(BAUDVAL);

    while (1) 
    {
		/*PORTC ^= (1<<PC0);
		_delay_ms(100);*/ //Square signal
		
		unsigned char data = USART_Receive();
		USART_Transmit(data);
    }
	
	return 0;
}

