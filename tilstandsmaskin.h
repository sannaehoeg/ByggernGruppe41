#ifndef tilstandsmaskin_h
#define tilstandsmaskin_h

#include "OLED.h"

enum States{
	Menu,
	Start_game,
	High_score,
	Settings

};

#include "OLED_IF.h"

void state_machine(enum States* state, IO_board* xy, enum Joystick_dir* direction, uint8_t* pointer_pos);

#endif