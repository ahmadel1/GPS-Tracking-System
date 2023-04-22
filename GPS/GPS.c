#include "GPS.h"

#define EARTH_RADIUS 6371000
#define M_PI 3.14159265358979323846

double convert_to_degrees(double nmea_value) {
    double degrees = 0.0f;
    double minutes = 0.0f;

    nmea_value = nmea_value / 100.0f;
    degrees = (int)nmea_value;
    minutes = ((nmea_value - degrees) * 100.0f)/60.0f;

    return degrees + minutes;
}

void get_checksum (char check_sum[],  char gprmc_str[]){
    int lenght = strlen(gprmc_str);
    check_sum[0] = gprmc_str[lenght - 2];
    check_sum[1] = gprmc_str[lenght - 1];
}

int calculate_checksum (char gprmc_str[]){
    int checksum = 0;
    int i;
    for(i = 1; i < (int)(strlen(gprmc_str)-3); i++)
        checksum ^= (int)gprmc_str[i];

    return checksum;
}

bool valid_checksum (char gprmc_str[]){
    char checksum[2];
    get_checksum(checksum, gprmc_str);
    int actual_checksum = strtol(checksum, NULL, 16);
    int calculated_checksum = calculate_checksum(gprmc_str);
    return actual_checksum == calculated_checksum;

}

bool is_GPRMC(char *token){
    return strcmp(token, "$GPRMC") == 0;
}

void parse_gprmc(char gprmc_str[], double *latitude, double *longitude) {
    char nmea_str[256];
    int token_count = 0;
	char *token;
    char fix, lat_direction, long_direction;
	
    // Copy the string to a buffer
    strncpy(nmea_str, gprmc_str, sizeof(nmea_str));

	 // Tokenize the string
    token = strtok(nmea_str, ",");
    
    // Check if the correct NMEA sentence is received
    if(!is_GPRMC(token) || !valid_checksum(gprmc_str))
        return ;
        
    // Parse tokens
    while (token != NULL) {
        switch (token_count) {
        case 2: // fix
            fix = *token;
            if (fix != 'A') {
                return ;
            }
            break;
        case 3: // Latitude
            *latitude = convert_to_degrees(atof(token));
            break;
        case 4: // Latitude direction
            lat_direction = *token;
            break;
        case 5: // Longitude
            *longitude = convert_to_degrees(atof(token));
            break;
        case 6: // Longitude direction
            long_direction = *token;
            break;
        default:
            break;
        }

        token = strtok(NULL, ",");
        token_count++;
    }

    // adjust the sign of the latitude and longitude values based on the hemisphere direction.
    if (lat_direction == 'S') {
        *latitude = -1 * (*latitude);
    }
    if (long_direction == 'W') {
        *longitude = -1 *(*longitude);
    }
}

double calculate_distance(double lat1, double lon1, double lat2, double lon2) {
    double dlat = (lat2 - lat1) * M_PI / 180.0;
    double dlon = (lon2 - lon1) * M_PI / 180.0;
    double a = pow(sin(dlat / 2), 2) + cos(lat1 * M_PI / 180.0) * cos(lat2 * M_PI / 180.0) * pow(sin(dlon / 2), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double d = EARTH_RADIUS * c;

    return d;
}
