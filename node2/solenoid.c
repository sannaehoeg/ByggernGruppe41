#include "solenoid.h"
#include "sam.h"
#include "time.h"

static uint8_t sol_active = 0;
static uint8_t sol_end = 0;
static uint8_t sol_ready = 0;
static uint8_t last_pressed = 0;

void solenoid_init(void){
	PMC->PMC_PCER0 |= (1<<ID_PIOB);
	PIOB->PIO_PER = PIO_PB25;
	PIOB->PIO_SODR = PIO_PB25; //sets high before enabling the output = relay off
	PIOB->PIO_OER = PIO_PB25;
}

void solenoid_fire(void){
	uint64_t now = time_now(); //time now
	if (sol_active || now < sol_ready) return; //if we're already firing or it's not ready then don't fire
	PIOB->PIO_CODR = PIO_PB25; //clear output, sets it low = relay on
	sol_end = now + msecs(50); //pulse time = 50ms
	sol_ready = now + msecs(300); //delay time = 300ms
	sol_active = 1; //is firing
}

void solenoid_update(void){
	if (sol_active && time_now() >= sol_end){
		PIOB->PIO_SODR = PIO_PB25;
		sol_active = 0;
	}
}

void solenoid_handle_can(CanMsg m){
	if (m.id == 1){
		uint8_t btn = m.byte[4];
		uint8_t pressed = (btn == 0);
		if (pressed && !last_pressed) solenoid_fire();
		last_pressed = pressed;
	}
}