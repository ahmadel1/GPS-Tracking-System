#ifndef _GPIO_H_
#define _GPIO_H_

#include "..\tm4c123gh6pm.h"
#include "stdint.h"
#define RED    0x02
#define BLUE   0x04
#define GREEN  0x08
#define YELLOW 0x0A


void RGBInit (void);
void RGBset (uint8_t color);
void RGBclear(void);
uint8_t RGBvalue(void);
void currentState(float remaining_distance);

#endif
