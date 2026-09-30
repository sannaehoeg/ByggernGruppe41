
#include "Joystick.h"
#include "ADC.h"
#include <stdlib.h>


void set_direction(IO_board xy, enum Joystick_dir* direction){
	if(abs(xy.x_val)<=5 && abs(xy.y_val)<=5){
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
