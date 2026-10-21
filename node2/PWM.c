#include "PWM.h"
#include "sam.h"


void PWM_init(void){
	PMC->PMC_PCER0 |= (1<<ID_PIOB); //enables clocksignal for PIOB
	PMC->PMC_PCER1 |= (1<<(ID_PWM-32));  //enables clocksignal for PWM

	PWM->PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(84); //sets PREA to 0000 -> MCK/1 and DIVA to 84 -> MCK = 1MHz

	PIOB->PIO_PDR = PIO_PB13; //disables PIO
	PIOB->PIO_ABSR |= PIO_ABSR_P13; //selects peripheral B 

	PWM->PWM_CH_NUM[1].PWM_CMR = PWM_CMR_CPRE_CLKA; //sets channel 0 to use CLKA
	PWM->PWM_CH_NUM[1].PWM_CMR |= PWM_CMR_CPOL; //sets polarity on PB12 such that CPOL = 1
	PWM->PWM_CH_NUM[1].PWM_CPRD = PWM_CPRD_CPRD(20000); //sets CPRD = 20000 such that period equals 20 ms
	PWM->PWM_CH_NUM[1].PWM_CDTY = PWM_CDTY_CDTY(1500);  //stes CDTY = 1500 (middle value of duty cycle/joystick in normal position)

	PWM->PWM_ENA = PWM_ENA_CHID1; //selects channel 0

}

void PWM_set_DC(uint16_t ticks){
	if (ticks < 900) {ticks = 900;}
	if (ticks > 2100) {ticks = 2100;}
	
	PWM->PWM_CH_NUM[1].PWM_CDTYUPD = PWM_CDTYUPD_CDTYUPD(ticks);

}