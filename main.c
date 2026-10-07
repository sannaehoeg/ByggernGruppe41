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
#include "ADC.h"
#include <stdio.h>
#include <stdint.h>
#include "SPI.h"
#include "OLED.h"
#include "OLED_IF.h"
#include "Joystick.h"
#include "tilstandsmaskin.h"


int main(void)
{

	DDRC = 0xFF;

	USART_init(BAUDVAL);
	SPI_init();
	OLED_init();
	adc_clock_init(); 
	OLED_start_up();
	uint8_t pointer_pos=0;
	OLED_starting_meny(pointer_pos);

	fdevopen(transmit, receive);
	uint8_t counter = 0;

	MCUCR |= (1<<SRE); //Writing SRE to1 enables the External Memory Iinterface (taken from AVR datasheet s. 30)

	volatile char *sram_addr = (char *)0x1800;
	volatile char *adc_addr = (char *)0x1000;

	//int8_t x_val, y_val, x_pad, y_pad;
	//uint8_t x_null, y_null, xpad_null, ypad_null;
	IO_board xy;
	adc_calibration(&xy);
	enum Joystick_dir direction;
	direction = NONE;

	enum States state;
	state = Menu;
	


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

		/**sram_addr = 0xAA; //Skriver til SRAM-adresse -> CS_SRAM bør bli aktiv (lav)
		_delay_ms(1000);
		*adc_addr = 0xAA; //Skriver til ADC-adresse -> CS_ADC bør bli aktiv (lav)
		_delay_ms(1000);*/

		//SRAM_test();

		/*adc_read_joystick(&y_val, &x_val, &x_pad, &y_pad, x_null, y_null, xpad_null, ypad_null);
		printf("X_joy: %3d	Y_joy: %3d	X_pad:%3d 	Y_pad: %3d\n\r", x_val, y_val, x_pad, y_pad);
		_delay_ms(200); //leser bare joysticken 5 ganger i sekundet*/

		//adc_read_joystick(&xy);
		//set_direction(xy, &direction);
		//move_pil(&direction, &pointer_pos, &xy);
		printf("X_joy: %3d	Y_joy: %3d	X_pad:%3d 	Y_pad: %3d\n\r", xy.x_val, xy.y_val, xy.x_pad, xy.y_pad);
		state_machine(&state, &xy, &direction, &pointer_pos);
		//printf((char*)pointer_pos);
		//printf("Direction: %3d\n\r", direction);
		
		
		//OLED_clear();
		
    }
	
	return 0;
} 

