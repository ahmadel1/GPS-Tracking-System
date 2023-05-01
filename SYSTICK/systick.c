#include "systick.h"
void systick_init(void)
{
	NVIC_ST_CTRL_R = 0X00;
	NVIC_ST_RELOAD_R = NVIC_ST_RELOAD_M;

	NVIC_ST_CURRENT_R = 0X00;
	NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE | NVIC_ST_CTRL_CLK_SRC ;
}
void systick_wait_1s(void)
{
	NVIC_ST_RELOAD_R = (16000000) - 1;
	NVIC_ST_CURRENT_R = 0X00;
	while ((NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT) == 0x00){}
}
void systick_wait_1ms(void)
{
	NVIC_ST_RELOAD_R = (16000) - 1;
	NVIC_ST_CURRENT_R = 0X00;
	while ((NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT) == 0x00) {}
}
void systick_wait_1MICROs(void)
{
	NVIC_ST_RELOAD_R = (16) - 1;
	NVIC_ST_CURRENT_R = 0X00;
	while ((NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT) == 0x00) {}
}
void delay_IN_ms(int total)
{
	int i;
	for (i = 0; i < total; i++)
	{
		systick_wait_1ms();
	}
}
void delay_IN_MICROs(int total)
{
	int i;
	for (i = 0; i < total; i++)
	{
		systick_wait_1MICROs();
	}
}
void delay_IN_s(int total)
{
	int i;
	for (i=0; i < total; i++)
	{
		systick_wait_1s();
	}
}
