/*
 * CFile1.c
 *
 * Created: 01.09.2026 12:15:29
 *  Author: sannaeh
 */ 

#include <avr/io.h>
#include "USART.h"

void USART_init(unsigned int ubrr){
	UBRR0H = (unsigned char)(ubrr>>8); //set baud rate
	UBRR0L = (unsigned char)ubrr;
	
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); //Enable receiver and transmitter
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00); //Set frame format: 8data, 2stop bit
}

void USART_Transmit (unsigned char data){
	while ( !(UCSR0A & (1<<UDRE0)) );
	UDR0 = data;
}

unsigned char USART_Receive (void){
	while ( !(UCSR0A & (1<<RXC0)) );
	return UDR0;
}