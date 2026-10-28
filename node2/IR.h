#ifndef IR_h
#define IR_h

#include <stdint.h>

void adc_init(void);

uint16_t adc_read(void);

void ir_init(void);

uint8_t ir_beam_blocked(void);

uint8_t ir_goal_detected(void);

void score_update(void);

uint8_t score_get(void);

void score_reset(void);




#endif