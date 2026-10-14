
#ifndef ADC_h
#define ADC_h
#define F_CPU 4915200UL
#include <stdint.h>
#include <util/delay.h>
#include "Joystick.h"


void adc_clock_init(void);

void adc_start_conversion(void);

void adc_read_joystick(IO_board* xy);

void adc_calibration(IO_board* xy);

#endif