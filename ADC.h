
#ifndef ADC_h
#define ADC_h
#define F_CPU 4915200UL
#include <stdint.h>
#include <util/delay.h>

void adc_clock_init(void);

void adc_start_conversion(void);

void adc_read_joystick(int8_t *y, int8_t *x, int8_t *xpad, int8_t *ypad, uint8_t x_null, uint8_t y_null, uint8_t xpad_null, uint8_t ypad_null);

void adc_calibration(uint8_t *x_null, uint8_t *y_null, uint8_t *ypad_null, uint8_t *xpad_null);

#endif