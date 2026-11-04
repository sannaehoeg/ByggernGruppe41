#include "encoder.h"
#include "can.h"
#include "sam.h"




void encoder_init(void){

	PMC->PMC_PCER1 |= (1<<(ID_TC6 - 32)); //enables clocksignal 
	PMC->PMC_PCER0 |= (1<<ID_PIOC); //enables clocksignal for PIOC

	TC2->TC_BMR = TC_BMR_QDEN | TC_BMR_TC0XC0S_TCLK0 | TC_BMR_POSEN; // sets clock (XC0), enables quadrature decoding and the position

	PIOC->PIO_PDR = PIO_PC26 | PIO_PC25; //disables PIO on pin 26 and 25
	PIOC->PIO_ABSR |= PIO_ABSR_P26 | PIO_ABSR_P25; //selects peripheral B 

	TC2->TC_CHANNEL[0].TC_CMR = TC_CMR_TCCLKS_XC0 | TC_CMR_ABETRG | TC_CMR_ETRGEDG_RISING;
	TC2->TC_CHANNEL[0].TC_CMR &= ~TC_CMR_WAVE;
	TC2->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;

	/*
	TC2->TC_CHANNEL[1].TC_CMR |= TC_CMR_TCCLKS_XC0 | TC_CMR_ABETRG | TC_CMR_ETRGEDG_RISING;
	TC2->TC_CHANNEL[1].TC_CMR &= ~TC_CMR_WAVE;
	TC2->TC_CHANNEL[1].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
	*/

	PIOC->PIO_PER = PIO_PC23; //enables PIO
	PIOC->PIO_OER = PIO_PC23; //output enable
	PIOC->PIO_CODR = PIO_PC23; //starts low (clear output data register)

	PIOB->PIO_PDR = PIO_PB12; //disables PIO on pin 12
	PIOB->PIO_ABSR = PIO_PB12; //selects peripheral B 

	PWM->PWM_CH_NUM[0].PWM_CMR = PWM_CMR_CPRE_MCK; //sets channel 0 to use MCK
	PWM->PWM_CH_NUM[0].PWM_CPRD = PWM_CPRD_CPRD(840);
	PWM->PWM_CH_NUM[0].PWM_CDTY = PWM_CDTY_CDTY(0);  //sets CDTY = 0

	PWM->PWM_ENA = PWM_ENA_CHID0; //selects channel 0

}

uint32_t encoder_read(void){
	return TC2->TC_CHANNEL[0].TC_CV;
}

void set_motor_pos_and_dir(CanMsg m){
	if (m.id == 1){
		int8_t x_val = m.byte[0]; 
		if (abs(x_val) <= 5) {x_val = 0;}
		if (x_val < -100) {x_val = -100;}
		if (x_val > 100) {x_val = 100;}

		set_motor_dir(x_val);
		set_motor_speed(x_val);

	}
	return;
}

void set_motor_dir(int8_t value){
	if(value <= 0){
		PIOC->PIO_SODR = PIO_PC23; // sets high
		}else{
			PIOC->PIO_CODR = PIO_PC23; //sets low
		}
}

void set_motor_speed(int8_t value){

	uint8_t duty = abs(value) * 840 / 100;

	if(duty > 252){ //sets limit for maximum speed (30%)
		duty = 252;
	}
	PWM->PWM_CH_NUM[0].PWM_CDTYUPD = PWM_CDTYUPD_CDTYUPD(duty); //sets duty cycle based on x-val

}