
#include "ADC.h"
#include <avr/io.h>


volatile char *adc_ptr = (char *)0x1000;

void adc_clock_init(void){
	DDRD |= (1<<PD5); //Configures it as an output (datasheet s. 78)

	TCCR1A = (1 << COM1A0); //Toggle OC1A by compare match
	TCCR1B = (1 << WGM12) | (1 << CS10); //CTC-mode (mode 4), no prescaling

	OCR1A = 1; //Gives ca. 1,23 MHz to OC1A

}

void adc_start_conversion(void){
	*adc_ptr = 0x1;
	_delay_ms(10);
	
}

void adc_calibration(uint8_t *x_null, uint8_t *y_null, uint8_t *ypad_null, uint8_t *xpad_null){
	adc_start_conversion();
	*y_null = adc_ptr[0];
	*x_null = adc_ptr[0];
	*ypad_null = adc_ptr[0];
	*xpad_null = adc_ptr[0];

}

void adc_read_joystick(int8_t *y, int8_t *x, int8_t *xpad, int8_t *ypad, uint8_t x_null, uint8_t y_null, uint8_t xpad_null, uint8_t ypad_null){
	adc_start_conversion();

	uint8_t y_uk = adc_ptr[0]; //finner den styrte verdien til y_joystick
	if (y_uk >= y_null) {*y = (int16_t)(y_uk-y_null)*100/(244-y_null);} //skalerer verdien for å få -100 til 100
	else {*y = -(int16_t)(y_null-y_uk)*100/(y_null-70);}
	
	if (*y > 100){*y = 100;} 
	if (*y<-100){*y=-100;}

	uint8_t x_uk = adc_ptr[0];
	if (x_uk >= x_null) {*x = (int16_t)(x_uk-x_null)*100/(245-x_null);} 
	else {*x = -(int16_t)(x_null-x_uk)*100/(x_null-63);}
	
	if (*x > 100){*x = 100;} 
	if (*x<-100){*x=-100;}
	
	uint8_t ypad_uk = adc_ptr[0];
	*ypad = (ypad_uk-127)*100/127;
	
	uint8_t xpad_uk = adc_ptr[0];
	*xpad = (xpad_uk -127)*100/127;

	

}