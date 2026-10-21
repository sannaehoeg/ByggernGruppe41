#ifndef servo_h
#define servo_h
#include <stdint.h>
#include "can.h"

uint16_t servo_find_ticks(CanMsg m);

#endif