#include "CAN_com.h"
#include "mcp2515.h"


uint8_t can_init(void){

	mcp2515_reset();
	uint8_t status = mcp2515_read(MCP_CANSTAT);
	if ((status & 0xE0) != 0x80){
		printf("Configuration mode not set. CANSTAT is: 0x%02X\n", status);
		return 1;
	}

	mcp2515_write(MCP_CNF1, 0x03); //125 kbps
	mcp2515_write(MCP_CNF2, 0xAA);
	mcp2515_write(MCP_CNF3, 0x05);
	mcp2515_write(MCP_CANCTRL, MODE_LOOPBACK);

	status = mcp2515_read(MCP_CANSTAT);
	if ((status & 0xE0) != 0x40){
		printf("Loopback mode not set. CANSTAT is: 0x%02X\n", status);
		return 1;
	}

	return 0;
}

void can_transmit(can_message_t* msg){
	
	while(mcp2515_read(0x30) & (1<<3));

	mcp2515_write(0x31, msg->id >> 3); //ID high
	mcp2515_write(0x32, (msg->id & 0x07) << 5); //ID low

	mcp2515_write(0x35, msg->length);

	for (uint8_t i = 0; i < msg->length; i++){
		mcp2515_write(0x36 + i, msg->data[i]);
	}

	mcp2515_rts(0);
}

can_message_t can_receive(void){
	can_message_t msg;

	msg.id = mcp2515_read(0x61) << 3; 
	msg.id |= mcp2515_read(0x62) >> 5;
	
	msg.length = mcp2515_read(0x65) & 0x0F; //Only interested in the last 4 bits
	if (msg.length > 8){
		msg.length = 8;
	}

	for (uint8_t i = 0; i < msg.length; i++){
		msg.data[i] = mcp2515_read(0x66 + i);
	}

	mcp2515_bit_modify(MCP_CANINTF, MCP_RX0IF, 0);

	return msg;
}

