#include "pmsa003i.h"

// constructor
PMSA003I::PMSA003I() {
    // Create struct with default values
    memset(&data, 0, sizeof(PM25_AQI_Data));
}

// Initialize sensor
void PMSA003I::initialize() {
    // Initialize the sensor via I2C
    if (!aqi.begin_I2C()) {
        Serial.println("Could not find PM2.5 sensor!");
        while (1);
    }
    Serial.println("PMSA003I initialized");
}

bool PMSA003I::readData(){
    // Read data from the sensor
    if (!aqi.read(&data)){
        Serial.println("Could not read data from PM2.5 sensor");
        return false;
    }
    return true;
}

String PMSA003I::getDataString(){
    // Create a comma-separated string of the data to write to SD
    String dataString = String(data.pm10_standard) + "," +
                        String(data.pm25_standard) + "," +
                        String(data.pm100_standard);
    return dataString;
}

void PMSA003I::printData(){
    // Print out the data obtained for testing
    Serial.println("PMSA003I Sensor Data:");
    Serial.print("PM 1.0 (ug/m3): ");
    Serial.println(data.pm10_standard);
    Serial.print("PM 2.5 (ug/m3): ");
    Serial.println(data.pm25_standard);
    Serial.print("PM 10.0 (ug/m3): ");
    Serial.println(data.pm100_standard);
    Serial.println();
}