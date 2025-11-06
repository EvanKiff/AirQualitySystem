// CO2 + temp + humidity sensor

#include <Arduino.h>
#include <SensirionI2cScd4x.h>
#include <Wire.h>

class SCD40{

public:
    SCD40();                // Constructor
    void initialize();      // Initialize the sensor
    bool readData();        // Read temp, humidity, and co2 data from the sensor at once
    String getDataString(); // Get the sensor data as a comma-separated string to write to SD
    void printData();       // Print the sensor data to serial monitor

private:
    SensirionI2cScd4x scd4x; // Instance of the Sensirion SCD4x library
    uint16_t co2;           // Variable to hold CO2 concentration in ppm
    float temperature;      // Variable to hold temperature in ºC
    float humidity;         // Variable to hold humidity as a percentage
    bool dataReady;         // Variable to indicate if data is ready

};