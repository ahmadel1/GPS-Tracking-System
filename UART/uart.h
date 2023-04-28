#ifndef __uart_H__
#define __uart_H__

#include "..\tm4c123gh6pm.h"
#include "stdint.h"
#include "string.h"

void UART1Init();
void UART0Init();
uint8_t UART1_AVAILABLE(void);
uint8_t UART1_read(void);
void UART1_write(uint8_t c);
void UART1_readstr(uint8_t *str);
void UART1_writestr(uint8_t *str);



#endif
