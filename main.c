/*
 * Byggern41.c
 *
 * Created: 31.08.2026 14:22:18
 * Author : sannaeh
 */ 

//#define F_CPU 16000000UL
#define F_CPU 4915200UL
#define FOSC 4915200
#define BAUD 9600
#define BAUDVAL (FOSC/16/BAUD-1)

#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"
#include "SRAM_Test.h"
#include <stdio.h>

int main(void)
{
    /* Replace with your application code */
	/*DDRC |= (1<<PC0);*/
	
	USART_init(BAUDVAL);

	fdevopen(transmit, receive);

	uint8_t counter = 0;

	MCUCR |= (1<<SRE); //Writing SRE to1 enables the External Memory Iinterface (taken from AVR datasheet s. 30)

	volatile char *sram_addr = (char *)0x1800;
	volatile char *adc_addr = (char *)0x1000;

    while (1) 
    {
		/*PORTC ^= (1<<PC0);
		_delay_ms(100);*/ //Square signal
		
		/*unsigned char data = USART_Receive();
		USART_Transmit(data);
		_delay_ms(500);*/

		/*printf("hello world");
		_delay_ms(1000);*/

		/*volatile char *ptr = (char *)(0x1000 + counter); //Example test code from Claude
		*ptr = 0;
		counter++;
		_delay_ms(1000);*/

		/*sram_addr = 0xAA; //Skriver til SRAM-adresse -> CS_SRAM bør bli aktiv (lav)
		_delay_ms(1000);
		*adc_addr = 0xAA; //Skriver til ADC-adresse -> CS_ADC bør bli aktiv (lav)
		_delay_ms(1000);*/

		SRAM_test();

    }
	
	return 0;
} 

