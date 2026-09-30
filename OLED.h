#ifndef OLED_h
#define OLED_h

#include <stdint.h>
#include <util/delay.h>

enum Font {
	SMALL,
	MEDIUM,
	LARGE
};

void OLED_init(void);

void OLED_command(uint8_t command);

void OLED_data(uint8_t data);

void OLED_goto_line(uint8_t line);

void OLED_goto_column(uint8_t column);

void OLED_clear_line(uint8_t line);

void OLED_clear(void);

void OLED_pos(uint8_t line, uint8_t column);

void OLED_print_char(char c, enum Font font);

void OLED_print_str(char *str, enum Font font);

#endif