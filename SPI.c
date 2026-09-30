#include "SPI.h"
#include <avr/io.h>



void SPI_init(void){

	DDRB |= (1 << PB5) | (1 << PB7); //Setter de som outputs - MOSI
	DDRB &= ~(1 << PB6); //MISO - settess høy
	PORTD |= (1 << PD2) | (1 << PD3) | (1 << PD4); //Setter alle til 1
	SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0); //SPE er SPI Enable som 'skrus på' ved å sette til 1. MSTR gjør at vi kan sette SS_, setter klokkehastighet til F_CPU/16
	//SPCR = SPI conroll register
}

void SPI_select(enum Slave slave){

	PORTD |= (1 << PD2) | (1 << PD3) | (1 << PD4); //Setter alle til 1
	
	switch(slave){

		case(OLED): PORTD &= ~(1 << PD2); break; //setter riktig slave lav (aktiv lav)
		case(IO): PORTD &= ~(1 << PD3); break;
		case(CAN): PORTD &= ~(1 << PD4); break;

	}
}

void SPI_transmit(uint8_t cData){

	SPDR = cData; //Start transmission (SPDR = SPI data register)
	while(!(SPSR & (1 << SPIF))); // venter på fullført transmisjon
	
}

uint8_t SPI_receive(void){

	SPDR = 0x00; //sender em dummy byte
	while(!(SPSR & (1 << SPIF))); // venter på fullført transmisjon
	return SPDR; //returner mottatt byte

}

void SPI_transmit_n(uint8_t* data, uint16_t length){

	for (uint16_t i = 0; i < length; i++){
		SPI_transmit(data[i]);
	}
}

void SPI_receive_n(uint8_t* dataRec, uint16_t length){
	
	for (uint16_t i = 0; i < length; i++){
		dataRec[i] = SPI_receive();
	}
}
