#ifndef __uart_H__
#define __uart_H__

#include "..\tm4c123gh6pm.h"
#include "stdint.h"
#include "string.h"

void UART7Init(void);
void UART0Init(void);
uint8_t UART7_AVAILABLE(void);
uint8_t UART7_read(void);
void UART7_write(char c);
void UART7_readstr(char* str);
void UART7_writestr(char* str);
void UART0_write(char c);
void UART0_printf(char* str);
void UART0_readstr(char *str);
uint8_t UART0_read(void);
uint8_t UART0_AVAILABLE(void);

#endif
