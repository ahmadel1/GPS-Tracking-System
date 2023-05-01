#include "LCD.h"

/*
* USE PORT B FOR THE LCD 
* RS WILL BE ASSOCIATED TO PB0
* R_W WILL BE ATTACHED TO GND SINCE THIS CODE IS FOR WRITING ONLY 
* E RS WILL BE ASSOCIATED TO PB1
* DB0->DB3 WILL BE ATTACHED TO GND
* DB4->DB7 -----> PB4->PB7
*/

void portBinit(void)
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
void LCD_init(void)
{
	portBinit();
	LCD_CMD(0X03);
	delay_IN_ms(5);
	LCD_CMD(0X03);
	delay_IN_MICROs(200);
	LCD_CMD(0X03);
	delay_IN_MICROs(200);
	LCD_CMD(0X02);
	delay_IN_MICROs(40);
	LCD_CMD(0X28);
	LCD_CMD(0X08);
	LCD_CMD(0X01);
	LCD_CMD(0X06);
	LCD_CMD(0X0C);
}
void GPIO_ORDER(uint8_t E, char RS)
{
	if (E == 0 & RS == 0)
	{
		GPIO_PORTB_DATA_R &= ~EN_RS_ON;
	}
	if (E == 1 & RS == 1)
	{
		GPIO_PORTB_DATA_R |= EN_RS_ON;
	}
	if (E == 1 & RS == 0)
	{
		GPIO_PORTB_DATA_R &= RS_ONLY_OFF;
	}
	if (E == 1 & RS == 'x')
	{
		GPIO_PORTB_DATA_R |= EN_ONLY_ON;
	}
	if (E == 0 & RS == 'x')
	{
		GPIO_PORTB_DATA_R &= ~EN_ONLY_ON;
	}
}
void GPIO_BITS_CLEAR(void)
{
	//CLEARS DATA ON THE DATA BUS OF THE LCD
	GPIO_PORTB_DATA_R &= 0X0F;
}

uint8_t UP;
uint8_t LOW;

void split(uint8_t BITS)
{
	// BREAK THE DATA INTO 2 NIBBLES 4 BITS EACH 
	UP = 0;
	LOW = 0;
	UP = BITS & 0XF0;
	LOW = BITS & 0X0F;
	LOW = LOW << 4;
}
void LCD_CMD(uint8_t CMD)
{
	SEND_LCD_BYTE(CMD);
	if (CMD < 4)
	{
		delay_IN_ms(2);
	}
	else
	{
		delay_IN_MICROs(40);
	}
	
}
void SEND_CHAR(char DATA)
{
	SEND_LCD_BYTE(DATA);
	delay_IN_MICROs(40);
}
void SEND_LCD_BYTE(uint8_t byte)
{
	split(byte);
	//UPPER NIBBLE 
	GPIO_ORDER(1, 0);
	GPIO_BITS_CLEAR();
	GPIO_PORTB_DATA_R |= UP;
	GPIO_ORDER(1, 'x');//EN ON
	delay_IN_MICROs(40);
	GPIO_ORDER(0, 'x');//EN OFF

	//LOWER NIBBLE
	GPIO_BITS_CLEAR();
	GPIO_PORTB_DATA_R |= LOW;
	GPIO_ORDER(1, 'x');//EN ON
	delay_IN_MICROs(40);
	GPIO_ORDER(0, 'x');//EN OFF
	// EN ON _ EN OFF USED TO PULSE AN EN SIGNAL FOR THE LCD TO RECOGNISE THE DATA 
}

//functions to be used in main 

void LCD_String(char *str)
{
	uint8_t i;
	uint8_t last_char_at;
	last_char_at = strlen(str);
	for (i = 0; i < last_char_at; i++)
	{
		SEND_CHAR(str[i]);
	}
	delay_IN_ms(1);
}
void LCD_Float(float number)
{
	char str[10] = { 0 };
	sprintf(str, "%f", number);
	RESET_LCD();
	LCD_String(str);
}
void RESET_LCD(void)
{
	LCD_CMD(0x01);
	LCD_CMD(0x80);
	delay_IN_MICROs(100);
}
/*
// MAIN FOR TESTING 
int main()
{
	LCD_init();
	RESET_LCD();
	//e.g.
	LCD_String("GPS PROJECT");
	LCD_Float(37.372891)
}
*/
