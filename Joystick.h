#ifndef Joystick_h
#define Joystick_h

#include <stdint.h>

enum Joystick_dir{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};

typedef struct {
	int8_t x_val, y_val, x_pad, y_pad;
	uint8_t x_null, y_null, xpad_null, ypad_null;
}IO_board;

void set_direction(IO_board xy, enum Joystick_dir* direction);










#endif