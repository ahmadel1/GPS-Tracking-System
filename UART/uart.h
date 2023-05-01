#ifndef __uart_H__
#define __uart_H__

#include "..\tm4c123gh6pm.h"
#include "stdint.h"
#include "string.h"

void UART1Init(void);
void UART0Init(void);
uint8_t UART1_AVAILABLE(void);
uint8_t UART1_read(void);
void UART1_write(char c);
void UART1_readstr(char* str);
void UART1_writestr(char* str);



#endif
