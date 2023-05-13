

#include "uart.h"
#define maxlen 120


void UART0Init(void){
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
void UART7Init(void){
	SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R7;
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;
	
	UART7_CTL_R &= ~0x01; //disable uart
	UART7_IBRD_R = 104 ; //integer baud rate divisor
	UART7_FBRD_R = 11 ; //float baud rate divisor
	UART7_LCRH_R |= 0x70 ; //fifo enable and width  8 bits
	UART7_CTL_R = 0X0301 ; //uart enable , rx enable , tx enable
	GPIO_PORTE_DEN_R |= 0X03; //digital enable
	GPIO_PORTE_AMSEL_R &= ~0x03; //clear analog mode
	GPIO_PORTE_AFSEL_R |= 0x03; //set alternate function 
	GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R &= ~0xFF) | 0X00000011; //clear PE0 and PE1 then set them as uart
	
}

uint8_t UART7_AVAILABLE(void){
		return (((UART7_FR_R & UART_FR_RXFE)) == UART_FR_RXFE) ? 0:1 ;
}

uint8_t UART0_AVAILABLE(void){
		return (((UART0_FR_R & UART_FR_RXFE)) == UART_FR_RXFE) ? 0:1 ;
}

uint8_t UART7_read(void){
	while (UART7_AVAILABLE() != 1){};
	return (UART7_DR_R & 0xFF);
}

uint8_t UART0_read(void){
	while (UART0_AVAILABLE() != 1){};
	return (UART0_DR_R & 0xFF);
}

void UART7_write(char c){
	while ((UART7_FR_R & UART_FR_TXFF ) == UART_FR_TXFF){};
	UART7_DR_R = c;
	
}
void UART0_write(char c){
	while ((UART0_FR_R & UART_FR_TXFF ) == UART_FR_TXFF){};
	UART0_DR_R = c;
	
}
void UART7_readstr(char* str){
	int i=0;
	char c;
	
	/*for ( i = 0; i < maxlen ; i++){   
		c=UART7_read();
		if (c== '\n' || c == '\r') break;
		str[i]=c;
		
	}*/
	while(1){
		c=UART7_read();
		if (c== '\n' || c == '\r') break;
		str[i]=c;
		i++;
	}
}


void UART0_printf(char* str){

	while(*str){
		UART0_write(*str);
		str++;
	}
}

void UART0_readstr(char* str){
	int i=0;
	char c;
	
	/*for ( i = 0; i < maxlen ; i++){   
		c=UART7_read();
		if (c== '\n' || c == '\r') break;
		str[i]=c;
		
	}*/
	while(1){
		c=UART0_read();
		if (c== ' ' || c == '\r') break;
		str[i]=c;
		i++;
	}
}

