#ifndef OLED_IF_h
#define OLED_IF_h
#include "Joystick.h"
#include "ADC.h"

void OLED_start_up(void);

void OLED_starting_meny(uint8_t pil_pos);

void move_pil(enum Joystick_dir* direction, uint8_t* pil_pos, IO_board* xy);


#endif 
