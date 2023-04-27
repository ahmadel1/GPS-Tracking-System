#include "systick.h"

void SysTick_Init(void){
	NVIC_ST_CTRL_R = 0;  //disable systick during setup
	NVIC_ST_RELOAD_R = 0XFFFFFF;  //maximum reload value
	NVIC_ST_CURRENT_R = 0;   //any write to current clears it 
	NVIC_ST_CTRL_R = 0X05;  //enable systick with core clock
}

void systick_wait_1ms(){
	NVIC_ST_RELOAD_R = 16000-1;
	NVIC_ST_CURRENT_R = 0;
	while((NVIC_ST_CTRL_R & 0x00010000)==0){};
}

void delayInSeconds(uint32_t timeInSeconds){
	uint32_t counter = timeInSeconds*1000, i=0;
	for(i = 0; counter>i; i++){
			systick_wait_1ms();
	}
}

void delayInMilli(uint32_t timeInMilli){
	uint32_t i=0;
	for(i = 0; counter>i; i++){
			systick_wait_1ms();
	}
}