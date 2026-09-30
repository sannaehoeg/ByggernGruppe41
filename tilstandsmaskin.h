#ifndef tilstandsmaskin_h
#define tilstandsmaskin_h
#include "OLED_IF.h"
#include "OLED.h"

enum States{
	Menu,
	Start_spillet,
	High_score,
	Instillinger

};

void state_machine(enum States* state, IO_board xy, enum Joystick_dir direction, uint8_t pil_pos);

#endif