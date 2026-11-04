#ifndef encoder_h
#define encoder_h

#include "can.h"
#include <stdint.h>

void encoder_init(void);

uint32_t encoder_read(void);

void set_motor_pos_and_dir(CanMsg m);
void set_motor_dir(int8_t value);
void set_motor_speed(int8_t value);






#endif