
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
	*adc_ptr = 0x00;
	_delay_ms(10);
}

void adc_read_joystick(uint8_t *y, uint8_t *x){
	adc_start_conversion();
	*y = *adc_ptr;
	*x = *adc_ptr;
}