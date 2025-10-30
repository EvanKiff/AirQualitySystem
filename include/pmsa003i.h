// Air particulate sensor

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
    void printData(); // Print the sensor data to Serial Monitor

private:
    Adafruit_PM25AQI aqi; // Instance of the Adafruit PM25 AQI library
    PM25_AQI_Data data;   // Struct to hold the sensor data
};

#endif // PMSA003I_H