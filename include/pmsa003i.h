// Air particulate sensor

/*
Sensor data format:
PM 1.0 in ug/m^3
PM 2.5 in ug/m^3
PM 10 in ug/m^3
*/

#ifndef PMSA003I_H
#define PMSA003I_H

#include <Arduino.h>
#include <Adafruit_PM25AQI.h>
#include <Wire.h>

class PMSA003I {
public:
    PMSA003I(); // Constructor
    void initialize(); // Initialize the sensor
    bool readData(); // Read data from the sensor
    String getDataString(); // Get the sensor data as a comma-separated string
    void printData(); // Print the sensor data to serial monitor for testing

private:
    Adafruit_PM25AQI aqi; // Instance of the Adafruit PM25 AQI library
    PM25_AQI_Data data;   // struct to hold the sensor data
};

#endif // PMSA003I_H