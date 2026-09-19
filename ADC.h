
#ifndef ADC_h
#define ADC_h

#include <stdint.h>
#include <util/delay.h>

void adc_clock_init(void);

void adc_start_conversion(void);

void adc_read_joystick(uint8_t *y, uint8_t *x);

#endif