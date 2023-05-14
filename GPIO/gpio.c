#include "GPIO.h"

void portBInit(void)
{
  
  	SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R1;
  	while ((SYSCTL_PRGPIO_R & SYSCTL_RCGCGPIO_R1 ) == 0) {};
	  GPIO_PORTB_LOCK_R   = GPIO_LOCK_KEY;
	  GPIO_PORTB_CR_R     = 0XFF;
	  GPIO_PORTB_AFSEL_R  = 0X00;
	  GPIO_PORTB_PCTL_R   = 0X00;
	  GPIO_PORTB_AMSEL_R  = 0X00;
	  GPIO_PORTB_DIR_R   |= 0XFF;
	  GPIO_PORTB_DEN_R   |= 0XFF;
	  GPIO_PORTB_DATA_R  &= 0X00;
}


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
	GPIO_PORTF_DATA_R |= color;
}

void RGBclear(void){
	GPIO_PORTF_DATA_R &= ~0x0E;
}



// Update RGB LED color based on remaining distance
void Currentstate(float distance){
    if(distance <= 1){
		RGBclear();
        RGBset(GREEN);
    }else if(distance<=5){
		RGBclear();
        RGBset(YELLOW);
    }else{
		RGBclear();
        RGBset(RED);  
    } 
}
