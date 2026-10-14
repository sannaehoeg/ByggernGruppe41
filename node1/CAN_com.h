#ifndef CAN_com_h
#define CAN_com_h

#include "_mcp2515.h"
#include <stdint.h>


typedef struct { //Generated code
	uint16_t id;
	uint8_t length;
	uint8_t data[8];
} can_message_t;


uint8_t can_init(void);

void can_transmit(can_message_t* msg);

can_message_t can_receive(void);


#endif