#include "servo.h"
#include "PWM.h"
#include "can.h"
#include "sam.h"


uint16_t servo_find_ticks(CanMsg m){
	if (m.id == 1){
		int8_t x_val = m.byte[0];
		if (abs(x_val) <= 5) {x_val = 0;}
		if (x_val < -100) {x_val = -100;}
		if (x_val > 100) {x_val = 100;}

		return 1500 + x_val*6;
	}

	return 0;
}
