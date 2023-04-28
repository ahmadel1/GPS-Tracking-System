#ifndef systic_H_
#define systic_H_

#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "string.h"

//prototypes 
void systick_init();
void systick_wait_1s();
void systick_wait_1ms();
void delay_IN_ms(int total);
void delay_IN_s(int total);
void systick_wait_1MICROs();
void delay_IN_MICROs(int total);

#endif
