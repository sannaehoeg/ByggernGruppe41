#include "IR.h"
#include "sam.h"

static uint8_t was_blocked;
static uint8_t score = 0;

void adc_init(void){

	ADC->ADC_CR = ADC_CR_SWRST; //Resets the adc 
	PMC->PMC_PCER1 |= (1<<(ID_ADC-32)); //enables clock signal for adc
	ADC->ADC_MR |= ADC_MR_PRESCAL(2) | ADC_MR_TRGEN_DIS; //Divides MCK = 84MHz by (2+1)*3 = 14MHz
	ADC->ADC_CHER = ADC_CHER_CH0; //Enables channel 0 which corresponds to AD0 (?) from op-amp
	

}

uint16_t adc_read(void){

	ADC->ADC_CR = ADC_CR_START; //starts conversion

	while(!(ADC_ISR_DRDY & ADC->ADC_ISR)){
	}

	uint16_t result = ADC->ADC_LCDR & ADC_LCDR_LDATA_Msk;
	return result;

}

void ir_init(void) {

	adc_init();
}

uint8_t ir_beam_blocked(void){

	uint16_t value = adc_read();

	if(value < 2000){
		return 1;
	}

	return 0;
}

uint8_t ir_goal_detected(void){

	uint8_t blocked = ir_beam_blocked();
	uint8_t goal = (blocked && !was_blocked);
	was_blocked = blocked;
	return goal;

}


void score_update(void){

	if(ir_goal_detected()){
		score++;
	}
}

uint8_t score_get(void){
	return score;
}

void score_reset(void){
	score = 0;
}

