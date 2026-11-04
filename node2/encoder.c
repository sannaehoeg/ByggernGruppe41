#include "encoder.h"

#include "sam.h"




void encoder_init(void){

	PMC->PMC_PCER0 |= (1<<ID_TC2); //enables clocksignal 
	PMC->PMC_PCER0 |= (1<<ID_PIOC); //enables clocksignal for PIOC

	TC2->TC_BMR = TC_BMR_QDEN | TC_BMR_TC0XC0S_TCLK0 | TC_BMR_POSEN; // sets clock (XC0), enables quadrature decoding and the position

	PIOC->PIO_PDR = PIO_PC26 | PIO_PC25; //disables PIO on pin 26 and 25
	PIOC->PIO_ABSR |= PIO_ABSR_P26 | PIO_ABSR_P25; //selects peripheral B 

	TC2->TC_CHANNEL[0].TC_CMR = TC_CMR_TCCLKS_XC0 | TC_CMR_ABETRG | TC_CMR_ETRGEDG_RISING;
	TC2->TC_CHANNEL[0].TC_CMR &= ~TC_CMR_WAVE;
	TC2->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;

	TC2->TC_CHANNEL[1].TC_CMR |= TC_CMR_TCCLKS_XC0 | TC_CMR_ABETRG | TC_CMR_ETRGEDG_RISING;
	TC2->TC_CHANNEL[1].TC_CMR &= ~TC_CMR_WAVE;
	TC2->TC_CHANNEL[1].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;


}

uint32_t encoder_read(void){
	return TC2->TC_CHANNEL[0].TC_CV;
}