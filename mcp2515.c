#include "mcp2515.h"
#include "SPI.h"


void mcp2515_reset(void){
	SPI_select(CAN);
	SPI_transmit(MCP_RESET);
	SPI_deselect();
	_delay_ms(1);
}

uint8_t mcp2515_read(uint8_t adr){
	SPI_select(CAN);
	SPI_transmit(MCP_READ);
	SPI_transmit(adr);
	uint8_t result = SPI_receive();
	SPI_deselect();
	return result;

}

void mcp2515_write(uint8_t adr, uint8_t data){
	SPI_select(CAN);
	SPI_transmit(MCP_WRITE);
	SPI_transmit(adr);
	SPI_transmit(data);
	SPI_deselect();
}

void mcp2515_rts(uint8_t buffer){
	SPI_select(CAN);
	SPI_transmit(0x80 | (1<<buffer));
	SPI_deselect(); 
}

uint8_t mcp2515_read_status(void){
	SPI_select(CAN);
	SPI_transmit(MCP_READ_STATUS);
	uint8_t data = SPI_receive();
	SPI_receive(); //Repeated data
	SPI_deselect();
	return data;
}

void mcp2515_bit_modify(uint8_t adr, uint8_t mask, uint8_t data){
	SPI_select(CAN);
	SPI_transmit(MCP_BITMOD);
	SPI_transmit(adr);
	SPI_transmit(mask);
	SPI_transmit(data);
	SPI_deselect();
}


