#ifndef SPI_h
#define SPI_h
#define F_CPU 4915200UL
#include <stdint.h>
#include <util/delay.h>

enum Slave {
	OLED, //Verdi 0 (PD2)
	IO, //1 osv... (PD3)
	CAN // PD4
};

void SPI_init(void);

void SPI_select(enum Slave slave);

void SPI_transmit(uint8_t cData);

uint8_t SPI_receive(void);

void SPI_transmit_n(uint8_t* data, uint16_t length);

void SPI_receive_n(uint8_t* dataRec, uint16_t length);

#endif