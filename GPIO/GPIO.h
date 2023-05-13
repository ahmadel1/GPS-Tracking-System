#ifndef __GPIO_H__
#define __GPIO_H__

#include "..\tm4c123gh6pm.h"
#include "stdint.h"
#define RED    0x02
#define BLUE   0x04
#define GREEN  0x08
#define YELLOW 0x0A


void RGBInit (void);
void RGBset (uint8_t color);
void RGBclear(void);
void currentState(float distance);

#endif

