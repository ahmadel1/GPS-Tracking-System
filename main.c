#include "UART\uart.h"
#include "GPIO\GPIO.h"
#include "LCD\Lcd.h"
#include "SYSTICK\systick.h"
#include "GPS\GPS.h"
#include <stdlib.h>

void SystemInit(){}
void currentState(float distance);

int main(void){
    // Initialize variables
    float distanceCovered = 0; 
    float totalDistance = 0;
    float remainingDistance = 0;
    int firstStep = 0;
    double currentLat = 0.0, currentLong = 0.0;
    double prevLat = 0.0, prevLong = 0.0;
    double finalLat, finalLong; //enter manually
    char message[84] = {0};
    
    // Initialize hardware
    systick_init();
    portBinit();
    LCD_init();
    UART0Init();
    UART1Init();

    while(1){
        // Read GPS message from UART1
        UART1_readstr(message);
        // Parse GPS message to get current latitude and longitude
        parse_gprmc(message, &currentLat, &currentLong);
        
        if(firstStep == 0){
            // Calculate total distance and display on LCD
            totalDistance = calculate_distance(currentLat, currentLong, finalLat, finalLong);
            LCD_Float(totalDistance); //show the total distance at beginning
            delay_IN_s(5);
            // Update variables for next iteration
            firstStep++;
            prevLat = currentLat;
            prevLong = currentLong;
            continue;
        }
        
        // Calculate distance covered since last iteration and display on LCD
        distanceCovered +=  calculate_distance(currentLat, currentLong, prevLat, prevLong);
        prevLat = currentLat;
        prevLong = currentLong;
        LCD_Float(distanceCovered);
        delay_IN_s(3);
        
        // Calculate remaining distance and display on LCD, and update RGB LED color
        remainingDistance = calculate_distance(currentLat, currentLong, finalLat, finalLong);
        LCD_Float(remainingDistance);
        currentState(remainingDistance);
        delay_IN_s(3);
    }
}


// Update RGB LED color based on remaining distance
void currentState(float distance){
    if(distance <= 1){
        RGBset(GREEN);
    }else if(distance<=5){
        RGBset(YELLOW);
    }else{
        RGBset(RED);  
    } 
}

