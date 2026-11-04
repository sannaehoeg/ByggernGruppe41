#ifndef encoder_h
#define encoder_h

#include "can.h"
#include <stdint.h>


void encoder_init(void);

uint32_t encoder_read(void);
void set_motor_speed_and_dir(CanMsg m);
void set_motor_pos_and_dir(CanMsg m);
void set_motor_dir(int8_t value);
void set_motor_speed(int8_t value);
void pos_calibration(void);
void controller(void);
int32_t set_motor_pos(int32_t value);
int32_t get_motor_pos(void);







#endif