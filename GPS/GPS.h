#ifndef __GPScutting_H__
#define __GPScutting_H__
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "..\UART\uart.h"

// Function to convert from NMEA format (ddmm.mmmm) to degrees only (dd.dddddd)
 double convert_to_degrees(double nmea_value);

// Function to get checksum of (GPRMC) string
void get_actual_checksum (char check_sum[],  char gprmc_str[]);

// Function to calculate checksum of (GPRMC) string
int calculate_checksum (char gprmc_str[]);

// Function to check if checksum is correct
bool valid_checksum (char gprmc_str[]);

// Funtion to check for (GPRMC) string
bool is_GPRMC(char *token);

// Function to parse a NMEA (GPRMC) string
void parse_gprmc(char gprmc_str[], double *latitude, double *longitude);

// Function to calculate the distance between two points using the Haversine formula
double calculate_distance(double lat1, double lon1, double lat2, double lon2);

#endif