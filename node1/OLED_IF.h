#ifndef OLED_IF_h
#define OLED_IF_h
#include "Joystick.h"
#include "ADC.h"
#include "tilstandsmaskin.h"

void OLED_start_up(void);

void OLED_starting_meny(uint8_t pointer_pos);

void move_pil(enum Joystick_dir* direction, uint8_t* pointer_pos, IO_board* xy, enum States* state);

void OLED_update(enum Joystick_dir* direction, uint8_t* pointer_pos, IO_board* xy, enum States* state);


#endif 
