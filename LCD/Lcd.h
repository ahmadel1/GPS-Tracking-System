#ifndef LCD_H_
#define LCD_H_

#include "..\tm4c123gh6pm.h"
#include "stdint.h"
#include "string.h"
#include "..\SYSTICK\systick.h"
#include "stdio.h"

void LCD_String(char* str);
void portBinit(void);
void LCD_init(void);
void GPIO_ORDER(uint8_t E, char RS);
void RESET_LCD(void);
void GPIO_BITS_CLEAR(void);
void split(uint8_t BITS);
void LCD_String(char* str);
void LCD_Float(float number);
void SEND_LCD_BYTE(uint8_t byte);
void SEND_CHAR(char DATA);
void LCD_CMD(uint8_t CMD);



#define ALL_ON 0XFF;
#define ALL_OFF 0X00;
#define RS_ONLY_OFF 0XFE;
#define EN_RS_ON 0X03;
#define EN_ONLY_ON 0X02;


// TO BE USED LATER ON
#define RS_ONLY_OFF 0XFE;
#define EN_RS_ON 0X03;
#define EN_ONLY_ON 0X02;
#define Fn_set 0X28;
#define AUTO_CUORSER_INC 0X06;
#define CLEAR 0X01;
#define LCD_OFF 0X08;
#define LCD_ON 0X03;
#define INITIAL_POSITION 0X80;
#define FOUR_BIT_MODE 0X02;
#define EN_DISP_CURSOR_OFF 0X0C;
#define UPPER_NIBBLE 0XF0;
#define LOWER_NIBBLE 0X0F;
//
#endif
