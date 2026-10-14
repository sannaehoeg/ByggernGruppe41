
#include "Joystick.h"
#include "ADC.h"
#include <stdlib.h>
#include <avr/io.h>


void set_direction(IO_board xy, enum Joystick_dir* direction){
	if(abs(xy.x_val)<=10 && abs(xy.y_val)<=10){
		*direction = NONE;
		return;
	}
	if (abs(xy.x_val) > abs(xy.y_val)) {
        if (xy.x_val < 0) {
            *direction = LEFT;
        } else {
            *direction = RIGHT;
        }
    } else {
        if (xy.y_val < 0) {
            *direction = DOWN;
        } else {
            *direction = UP;
        }
    }

}

uint8_t btn_pressed(void){

	DDRB &= ~(1 << PB3);
	uint8_t pressed = !(PINB&(1<<PB3));
	while(!(PINB&(1<<PB3))){
	}
	return pressed;

}
