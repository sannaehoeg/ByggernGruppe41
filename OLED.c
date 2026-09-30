#include "OLED.h"
#include "SPI.h"
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "fonts.h"


void OLED_command(uint8_t command){

	PORTB &= ~(1 << PB2); //Setter D/C lav for at dataen skal være en kommando
	SPI_select(OLED);
	SPI_transmit(command);
	SPI_deselect();
}

void OLED_data(uint8_t data){

	PORTB |= (1 << PB2); //Setter D/C høy for at dataen skal være data
	SPI_select(OLED);
	SPI_transmit(data);
	SPI_deselect();
}

void OLED_init(void){

	DDRB |= (1 << PB2); //Setter den som utgang

	//OLED_command(0xFD); 
	//OLED_command(0x12); //Unlock

	OLED_command(0xA1); //Speiler kolonnene
	OLED_command(0xC8); //Speiler radene
	OLED_command(0xAF); //Slår på displayet

	OLED_command(0x20); //Sets adressing mode
	OLED_command(0x00); //Sets it to horizontal adressing mode

	OLED_clear();

}

void OLED_goto_line(uint8_t line){

	OLED_command(0xB0 + line); //Go to page 0 pluss page (line)
}

void OLED_goto_column(uint8_t column){

	OLED_command(0x00 + (column & 0x0F));
	OLED_command(0x10 + ((column >> 4) & 0x0F));
}

void OLED_clear_line(uint8_t line){

	OLED_goto_line(line);
	OLED_goto_column(0);
	for (uint16_t i = 0; i < 128; i++){
		OLED_data(0x00);
	}

}

void OLED_clear(void){

	OLED_goto_column(0);
	OLED_goto_line(0);
	for (uint16_t i = 0; i < 1024; i++){
		OLED_data(0x00);
	}
}

void OLED_pos(uint8_t line, uint8_t column){

	OLED_goto_column(column);
	OLED_goto_line(line);
}

void OLED_print_char(char c, enum Font font){

	uint8_t index = c - ' '; //' ' = 32

	switch(font){

		case(SMALL):
			for (uint8_t i = 0; i < 4; i++){
				uint8_t data = pgm_read_byte(&font4[index][i]);
				OLED_data(data);
			}
			break;
		
		case(MEDIUM):
			for (uint8_t i = 0; i < 5; i++){
				uint8_t data = pgm_read_byte(&font5[index][i]);
				OLED_data(data);
			}
			OLED_data(0x00);
			break;

		case(LARGE):
			for (uint8_t i = 0; i < 8; i++){
				uint8_t data = pgm_read_byte(&font8[index][i]);
				OLED_data(data);
			}
			break;
	}

}

void OLED_print_str(char *str, enum Font font){

	while (*str){
		OLED_print_char(*str, font);
		str++;
	}
}
