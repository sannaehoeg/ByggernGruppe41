


#include "tilstandsmaskin.h"
#include "OLED_IF.h"
#include "Joystick.h"






void state_machine(enum States* state, IO_board* xy, enum Joystick_dir* direction, uint8_t *pointer_pos){
	switch(*state){
		case(Menu):

			OLED_update(direction, pointer_pos, xy, state);
			if(btn_pressed()){
				if(*pointer_pos == 0){
					OLED_clear();
					OLED_pos(4, 20);
					char game[] = "Here you will play:)";
					OLED_print_str(game, LARGE);
					*state = Start_game;
				} else if (*pointer_pos == 1){
					*state = High_score;
				}else{
					*state = Settings;
				}

			}
			break;

		case(Start_game):
			
			OLED_update(direction, pointer_pos, xy, state);
			if(btn_pressed()){
				OLED_starting_meny(0);
				*pointer_pos = 0;
				*state = Menu;
			}
			break;


		case(High_score):
			OLED_update(direction, pointer_pos, xy, state);
			break;

		case(Settings):
			OLED_update(direction, pointer_pos, xy, state);
			break;

	}

}



