/*
 * USART.h
 *
 * Created: 01.09.2026 12:19:13
 *  Author: sannaeh
 */ 

#ifndef USART_h
#define USART_h

void USART_init(unsigned int ubrr);

void USART_Transmit (unsigned char data);

unsigned char USART_Receive (void);


#endif 