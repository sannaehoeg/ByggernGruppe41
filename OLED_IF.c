#include "OLED_IF.h"
#include "OLED.h"


void OLED_start_up(void){

	OLED_pos(3, 50);
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

void move_pil(enum Joystick_dir* direction, uint8_t* pil_pos, int8_t* x_val, int8_t *y_val, uint8_t x_null, uint8_t y_null){
	if(*direction == DOWN && *pil_pos<3){
		(*pil_pos)++;
		while(!(*direction== NONE)){
			adc_read_joystick(x_val, y_val, 0, 0, 0, 0, 0, 0);
			set_direction(*x_val, *y_val, direction);
		}
		OLED_starting_meny(*pil_pos);
	}
	if(*direction == UP && *pil_pos>0){
		(*pil_pos)--;
		while(!(*direction== NONE)){
			adc_read_joystick(x_val, y_val, 0, 0, 0, 0, 0, 0);
			set_direction(*x_val, *y_val, direction);
		}
		OLED_starting_meny(*pil_pos);
	}
}



