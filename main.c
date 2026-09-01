/*
 * Byggern41.c
 *
 * Created: 31.08.2026 14:22:18
 * Author : sannaeh
 */ 

//#define F_CPU 16000000UL
#define F_CPU 4915200UL
#define FOSC 4915200UL
#define BAUD 9600
#define BAUDVAL FOSC/16UL/BAUD-1

#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"
#include <stdio.h>

int main(void)
{
    /* Replace with your application code */
	/*DDRC |= (1<<PC0);*/
	
	USART_init(BAUDVAL);

	fdevopen(transmit, receive);

    while (1) 
    {
		/*PORTC ^= (1<<PC0);
		_delay_ms(100);*/ //Square signal
		
		/*unsigned char data = USART_Receive();
		USART_Transmit(data);
		_delay_ms(500);*/

		printf("hello world");
		_delay_ms(1000);

    }
	
	return 0;
} 

