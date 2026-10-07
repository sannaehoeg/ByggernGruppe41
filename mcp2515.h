#ifndef MCP2515_h
#define MCP2515_h

#include "_mcp2515.h"
#include <stdio.h>

void mcp2515_reset(void);

uint8_t mcp2515_read(uint8_t adr);

void mcp2515_write(uint8_t adr, uint8_t data);

void mcp2515_rts(uint8_t buffer);

uint8_t mcp2515_read_status(void);

void mcp2515_bit_modify(uint8_t adr, uint8_t mask, uint8_t data);


#endif