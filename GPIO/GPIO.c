#include "GPIO.h"


void RGBInit (void){
		
				SYSCTL_RCGCGPIO_R |= 0X20 ; 
				while ((SYSCTL_PRGPIO_R & 0X20) == 0){};		
				GPIO_PORTF_LOCK_R = 0x4C4F434B  ; 
				GPIO_PORTF_CR_R |=0x0E;
				GPIO_PORTF_AMSEL_R &= ~0x0E;
				GPIO_PORTF_AFSEL_R &= ~0x0E;
				GPIO_PORTF_PCTL_R &= ~0x0000FFF0;
				GPIO_PORTF_DIR_R |=0x0E;
				GPIO_PORTF_DEN_R |=0x0E;
				GPIO_PORTF_DATA_R &= ~0x0E;
		}

void RGBset(uint8_t color){
	GPIO_PORTF_DATA_R = color;
}

void RGBclear(void){
	GPIO_PORTF_DATA_R = 0;
}

// Update RGB LED color based on remaining distance
void currentState(float distance){
    if(distance <= 1){
        RGBset(GREEN);
    }else if(distance<=5){
        RGBset(YELLOW);
    }else{
        RGBset(RED);  
    } 
}
