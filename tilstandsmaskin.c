


#include "tilstandsmaskin.h"
#include "OLED_IF.h"
#include "Joystick.h"






void state_machine(enum States* state, IO_board xy, enum Joystick_dir direction, uint8_t pil_pos){
	switch(*state){
		case(Menu):

			OLED_update(&direction, &pil_pos, &xy);
			if(btn_pressed()){
				if(pil_pos == 0){
					*state = Start_spillet;
				} else if (pil_pos == 1){
					*state = High_score;
				}else{
					*state = Instillinger;
				}

			}
			break;

		case(Start_spillet):
			OLED_clear();
			OLED_pos(4, 20);
			char spill[] = "Her spilles det:)";
			OLED_print_str(spill, LARGE);
			OLED_update(&direction, &pil_pos, &xy);
			if(btn_pressed()){
				*state = Menu;
			}
			break;


		case(High_score):
			OLED_update(&direction, &pil_pos, &xy);
			break;

		case(Instillinger):
			OLED_update(&direction, &pil_pos, &xy);
			break;

	}

}



