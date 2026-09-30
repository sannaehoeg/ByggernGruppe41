#include "OLED_IF.h"
#include "OLED.h"


void OLED_start_up(void){

	OLED_pos(3, 45);
	char text[] = "Hello";
	OLED_print_str(text, LARGE);
	_delay_ms(3000);
}

void OLED_starting_meny(uint8_t pil_pos){
	OLED_clear();
	OLED_pos(pil_pos, 0);
	char pil[] = "->";
	OLED_print_str(pil, MEDIUM);

	OLED_pos(0, 20);
	char linje1[] = "Start spillet!";
	OLED_print_str(linje1, MEDIUM);

	OLED_pos(1, 20);
	char linje2[] = "High score";
	OLED_print_str(linje2, MEDIUM);

	OLED_pos(2, 20);
	char linje3[] = "Instillinger";
	OLED_print_str(linje3, MEDIUM);
}

void move_pil(enum Joystick_dir* direction, uint8_t* pil_pos, IO_board* xy){
	if(*direction == NONE){return;}
	if(*direction == DOWN && *pil_pos<2){
		(*pil_pos)++;
		while(!(*direction== NONE)){
			adc_read_joystick(xy);
			set_direction(*xy, direction);
		}
		OLED_starting_meny(*pil_pos);
	}
	if(*direction == UP && *pil_pos>0){
		(*pil_pos)--;
		while(!(*direction== NONE)){
			adc_read_joystick(xy);
			set_direction(*xy, direction);
		}
		OLED_starting_meny(*pil_pos);
	}
}


void OLED_update(enum Joystick_dir* direction, uint8_t* pil_pos, IO_board* xy){
	adc_read_joystick(xy);
	set_direction(*xy, direction);
	move_pil(direction, pil_pos, xy);
}


