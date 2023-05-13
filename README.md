# GPS Tracking System

This project aims to develop a GPS system using TM4C123G LaunchPad to store the coordinates of a starting point and the endpoint, calculate the total distance traveled by the user, and provide an output through built-in LEDs based on the user's distance from the destination point.


## Additional Features

#### Map Navigation Web App

In addition to the GPS system, a web app has been created that reads data from the GPS module and connects to a map API to provide the user with a map and navigation experience. The web app allows the user to input their destination point and receive real-time directions to navigate to the destination. The web app also displays the user's current location on the map, making it easier for the user to track their progress.

#### LCD Display

An LCD has been added to the system to provide additional information to the user about the distance traveled and the current state of the system. The LCD displays the distance traveled by the user and the current state of the system, which is indicated by the built-in LEDs. The distance traveled is calculated by the GPS subsystem, and the current state of the system is determined by the distance from the destination point. The LCD display enhances the user experience by providing real-time information about the system.
<div style="text-align:center;"><img src="https://github.com/ahmadel1/GPS-Tracking-System/assets/73443649/7155fe39-da9a-407f-b6ca-a644ecc60ed0" style="width:50%;" /></div>



## LED Indicators

The LED indicators have three stages:

1.  Stage 1: The built-in LED will be turned on (green) when the target destination is reached.
2.  Stage 2: The built-in LED will be turned on (yellow) when the target destination is about to be reached < 5 meters.
3.  Stage 3: The built-in LED will be turned on (red) when the target destination is far away by distance > 5 meters.

## System Diagram

```mermaid
sequenceDiagram
Website->>Laptop: Send destination point
Laptop->>Tiva  LaunchPad: Send destination point
Tiva  LaunchPad->>GPS  Module: Retrive GPS data
Tiva  LaunchPad->>Laptop: Send Current location
Laptop->>Website: Display route data
loop
Laptop->>Tiva  LaunchPad: Send location data
Tiva  LaunchPad->>GPS  Module: Retrieve GPS data
Tiva  LaunchPad->>Tiva  LaunchPad: Calculate moved distance and remaining distance
Tiva  LaunchPad->>Laptop: Send moved distance, remaining distance, and current location GPS data
Laptop->>Website: Display current location GPS data, moved distance, and remaining distance
end
Laptop->>Tiva  LaunchPad: Send end signal
Tiva  LaunchPad->>GPS  Module: Retrieve GPS data
Tiva  LaunchPad->>Laptop: Send end point GPS data
Laptop->>Website: Display end point GPS data
```

## Credits

|Name            				|ID                         |
|-------------------------------|-----------------------------|
Ahmed Adel Abdelrahman          |2001778            |
Abdelrahman ali Mohamed        	|2000460           |
Amr Essam Mahmoud Anwar			|2001089			|
Ahmed Sherif Mohamed       	    |2001547          
Amr mostafa mohamed             |2001931         |
Abdulrahman Ibrahim Abdulaziz	|2000925|
Hazem mohamed mohamed       	|2002286       |
Aly Ayman Ibrahim      			|2000921           |



