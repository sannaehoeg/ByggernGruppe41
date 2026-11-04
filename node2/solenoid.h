#ifndef solenoid_h
#define solenoid_h

#include "can.h"


void solenoid_init(void);

void solenoid_fire(void);

void solenoid_update(void);

void solenoid_handle_can(CanMsg m);

#endif