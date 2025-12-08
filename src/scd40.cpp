#include "scd40.h"

// Constructor with member variables initialized at 0.0
SCD40::SCD40() : co2(0.0), temperature(0.0), humidity(0.0), dataReady(false) {}

// Initialize the sensor
void SCD40::initialize() {
    Wire.begin();
    scd4x.begin(Wire, SCD41_I2C_ADDR_62);
    static int16_t error = scd4x.startPeriodicMeasurement();
    // Error checking
    if (error != 0){
        Serial.println("Error executing periodic measurement for SCD40");
    }
}

// Read temp, humidity, and co2 data from the sensor at once
bool SCD40::readData(){
    static int16_t error;
    while (!dataReady){     // Continuously check for data until ready to read
        delay(100);
        error = scd4x.getDataReadyStatus(dataReady);
        if (error != 0){
            Serial.println("Error getting data ready status for SCD40");
            return false;
        }
    }

    // read data and fill member variables
    error = scd4x.readMeasurement(co2, temperature, humidity);
    if (error != 0){
        Serial.println("Error reading measurement for SCD40");
        return false;
    }
    return true;
}

String SCD40::getDataString(){
    // Create a comma-separated string of the data to write to SD
    String dataString = String(co2) + "," +
                        String(temperature) + "," +
                        String(humidity);
    return dataString;
}

// Print the sensor data to serial monitor for testing
void SCD40::printData(){
    Serial.print("CO2 [ppm]: ");
    Serial.println(co2);
    Serial.print("Temp [°C]: ");
    Serial.println(temperature);
    Serial.print("Humidity [%]: ");
    Serial.println(humidity);
    Serial.println();
}

void SCD40::powerDown() {
    scd4x.stopPeriodicMeasurement(); // Stop periodic measurements to save power
    Serial.println("SCD40 powered down.");
}