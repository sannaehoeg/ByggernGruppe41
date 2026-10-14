
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
	*adc_ptr = 0x1; //Starts the write functioon
	_delay_ms(10);
	
}

void adc_calibration(IO_board* xy){
	adc_start_conversion();
	xy->y_null = adc_ptr[0];
	xy->x_null = adc_ptr[0];
	xy->ypad_null = adc_ptr[0];
	xy->ypad_null = adc_ptr[0];

}

void adc_read_joystick(IO_board* xy){
	adc_start_conversion();

	uint8_t y_uk = adc_ptr[0]; //finner den styrte verdien til y_joystick
	if (y_uk >= xy->y_null) {xy->y_val = (int16_t)(y_uk-xy->y_null)*100/(244-xy->y_null);} //skalerer verdien for å få -100 til 100
	else {xy->y_val = -(int16_t)(xy->y_null-y_uk)*100/(xy->y_null-70);}
	
	if (xy->y_val > 100){xy->y_val = 100;} 
	if (xy->y_val<-100){xy->y_val=-100;}

	uint8_t x_uk = adc_ptr[0];
	if (x_uk >= xy->x_null) {xy->x_val = (int16_t)(x_uk-xy->x_null)*100/(245-xy->x_null);} 
	else {xy->x_val = -(int16_t)(xy->x_null-x_uk)*100/(xy->x_null-63);}
	
	if (xy->x_val > 100){xy->x_val = 100;} 
	if (xy->x_val<-100){xy->x_val=-100;}
	
	uint8_t ypad_uk = adc_ptr[0];
	xy->y_pad = (ypad_uk-127)*100/127;
	
	uint8_t xpad_uk = adc_ptr[0];
	xy->x_pad = (xpad_uk -127)*100/127;

	

}