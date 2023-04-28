#include "uart.h"
#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "string.h"
#define maxlen 83


void UART0Init(){
	SYSCTL_RCGCUART_R |= 0x01;
	SYSCTL_RCGCGPIO_R |= 0x01;
	
	UART0_CTL_R &= ~0x01; //disable uart
	UART0_IBRD_R = 104 ; //integer baud rate divisor
	UART0_FBRD_R = 11 ; //float baud rate divisor
	UART0_LCRH_R |= 0x70 ; //fifo enable and width  8 bits
	UART0_CTL_R = 0X0301 ; //uart enable , rx enable , tx enable
	GPIO_PORTA_AMSEL_R &= ~0x03; //clear analog mode
	GPIO_PORTA_AFSEL_R |= 0x03; //set alternate function 
	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R &= ~0xFF) | 0X00000011; //clear PA0 and PA1 then set them as uart
	GPIO_PORTA_DEN_R |= 0X03; //digital enable

}
void UART1Init(){
	SYSCTL_RCGCUART_R |= 0x02;
	SYSCTL_RCGCGPIO_R |= 0x02;
	
	UART1_CTL_R &= ~0x01; //disable uart
	UART1_IBRD_R = 104 ; //integer baud rate divisor
	UART1_FBRD_R = 11 ; //float baud rate divisor
	UART1_LCRH_R |= 0x70 ; //fifo enable and width  8 bits
	UART1_CTL_R = 0X0301 ; //uart enable , rx enable , tx enable
	GPIO_PORTB_DEN_R |= 0X03; //digital enable

  GPIO_PORTB_AMSEL_R &= ~0x03; //clear analog mode
	GPIO_PORTB_AFSEL_R |= 0x03; //set alternate function 
	GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R &= ~0xFF) | 0X00000011; //clear PB0 and PB1 then set them as uart
	
}

uint8_t UART1_AVAILABLE(void){
		return (((UART1_FR_R & UART_FR_RXFE)) == UART_FR_RXFE) ? 0:1 ;

}

uint8_t UART1_read(void){
	while (UART1_AVAILABLE() != 1){};
	return (UART1_DR_R & 0xFF);
}

void UART1_write(uint8_t c){
	while ((UART1_FR_R & UART_FR_TXFF ) == UART_FR_TXFF){};
	UART0_DR_R = c;

}

void UART1_readstr(uint8_t *str){
	uint8_t i;
	uint8_t c;
	for ( i = 0; i < 83 ; i++)
	{
		c=UART1_read();
		if (c== '\n' || c == '\r') break;
		str[i]=c;
		UART1_write(c);
	}

}
void UART1_writestr(uint8_t *str){

	while(*str){
		UART1_write(*str);
		str++;
	}



}



