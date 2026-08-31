/*
 * Byggern41.c
 *
 * Created: 31.08.2026 14:22:18
 * Author : sannaeh
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    /* Replace with your application code */
	DDRC |= (1<<PC0);
	
    while (1) 
    {
		PORTC ^= (1<<PC0);
		_delay_ms(100);
    }
}

/*
Sanna som tester å pushe igjen, og igjeeeeeen
*/