#include "UART\uart.h"
#include "GPIO\GPIO.h"
#include "LCD\Lcd.h"
#include "SYSTICK\systick.h"
#include "GPS\GPS.h"
#include <stdlib.h>
#include <stdio.h>

void SystemInit(){}
	
// Initialize variables
float distanceCovered = 0; 
float totalDistance = 0;
float remainingDistance = 0;
int firstStep = 0;
double currentLat = 0, currentLong = 0;
double prevLat = 0, prevLong = 0;
double finalLat, finalLong; //enter manually
char message[84] = {0};
char distanceStr[50];
char finalCoords[100]="";
char finalLat_str[100]="";
char finalLong_str[100]="";
char str[100] = "Distance covered: ";
char lat_str[100]="";
char lon_str[100]="";
char prevLat_str[100]="";
char prevLon_str[100]="";
char mdistance_str[100]="";
char rdistance_str[100]="";
	
int main(void){

	systick_init();
	portBinit();
	//delay_IN_ms(15);		
	//LCD_init();
	RGBInit();
	UART0Init();
	UART7Init();
	//RESET_LCD();
	
	while (1)
	{
		int i = 0;
		char *tokens;
		UART7_readstr(message);
		parse_gprmc(message, &currentLat, &currentLong);
		memset(message, 0, 120);
		sprintf(lat_str, "%f", currentLat);
		sprintf(lon_str, "%f", currentLong);
		strcat(lat_str, ",");
		UART0_printf(lat_str);
		UART0_printf(lon_str);
		UART0_readstr(finalCoords);
		RGBset(0x0C);
		// UART0_printf(finalCoords);

		tokens = strtok(finalCoords, ",");
		while (tokens != NULL)
		{
			if (i == 0)
			{
				finalLat = atof(tokens);
			}
			else if (i == 1)
			{
				finalLong = atof(tokens);
			}
			tokens = strtok(NULL, ",");
			i++;
		}

		sprintf(finalLat_str, "%f", finalLat);
		sprintf(finalLong_str, "%f", finalLong);
		// UART0_printf(finalLat_str);
		// UART0_printf(finalLong_str);

		finalLat = atof(finalLat_str);
		finalLong = atof(finalLong_str);
		// RGBset(finalLat+finalLong);
		RGBset(0x0C);
		if (finalLat == 0 || finalLong == 0)
		{
			RGBset(0x0E); // White
			continue;
		}
		else
		{
			break;
		}
	}
	
	//wait until GPS start get readings 
	while (1){
		UART7_readstr(message);
		// delay_IN_ms(1000);
		UART0_printf(message);
		RGBset(0x02); // red
		// delay_IN_ms(1000);
		parse_gprmc(message, &currentLat, &currentLong);
		memset(message, 0, 120);
		// LCD_String("Searching...");
		// delay_IN_ms(1000);
		sprintf(lat_str, "%f", currentLat);
		// UART0_printf(lat_str);

		if (currentLat == 0 && currentLong == 0)
			continue;
		else
			break;
	}
	
	while (1){
		currentLat = 0, currentLong = 0;
		// Read GPS message from UART1
		UART7_readstr(message);
		// Parse GPS message to get current latitude and longitude
		parse_gprmc(message, &currentLat, &currentLong);
		memset(message, 0, 120);
		sprintf(lat_str, "%f", currentLat);
		sprintf(lon_str, "%f", currentLong);
		strcat(lat_str, ",");
		strcat(lon_str, ",");
		;
		// showing on putty
		UART0_printf(lat_str);
		UART0_printf(lon_str);
		if (currentLat == 0 && currentLong == 0)
		{
			RGBset(0x04);
			continue;
		}

		if (firstStep == 0)
		{
			// Update variables for next iteration
			firstStep = 1;
			prevLat = currentLat;
			prevLong = currentLong;
			continue;
		}
		// RGBset(0x0E);

		// Calculate distance covered since last iteration and display on LCD
		distanceCovered += calculate_distance(currentLat, currentLong, prevLat, prevLong);
		sprintf(mdistance_str, "%f", distanceCovered);
		strcat(mdistance_str, ",");
		UART0_printf(mdistance_str);
		prevLat = currentLat;
		prevLong = currentLong;

		// Convert distance covered from float to string and concat it wiht "Distance covered: "
		// sprintf(distanceStr, "%f", distanceCovered);
		// strcat(str, distanceStr);
		// LCD_String(str);

		// Calculate remaining distance and update RGB LED color
		remainingDistance = calculate_distance(currentLat, currentLong, finalLat, finalLong);
		sprintf(rdistance_str, "%f", remainingDistance);
		strcat(rdistance_str, "-");
		UART0_printf(rdistance_str);
		currentState(remainingDistance);
		// delay_IN_s(2);
	}
}
