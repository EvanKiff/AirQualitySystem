#include "GPS.h"

void GPSModule::initialize() {
    // begin the GPS with the GPS_MODE_SHIELD parameter to configure the MKR GPS Shield
    if (!GPS.begin(GPS_MODE_SHIELD)) {
        Serial.println("Failed to initialize GPS!");
        while (1);
    }
}

void GPSModule::standby() {
    // Required standby as implemented by the GPS library
    Serial.println("standby");
    GPS.standby();
}

void GPSModule::wakeup() {
    // Required wakeup as implemented by the GPS library
    Serial.println("wakeup");
    GPS.wakeup();
}

bool GPSModule::waitForData() {
    Serial.print("wait location ... ");

    unsigned long startMillis = millis();
    while (!GPS.available());   // Wait for new GPS data to become available
    unsigned long endMillis = millis();

    Serial.print(endMillis - startMillis);  // Print the time taken to get any data
    Serial.println(" ms");

    // Fill member variables with the latest GPS data
    latitude = GPS.latitude();
    longitude = GPS.longitude();
    altitude = GPS.altitude();
    satellites = GPS.satellites();

    return true;
}

void GPSModule::printData() {
    // Print GPS values
    Serial.println();
    Serial.print("Location: ");
    Serial.print(latitude, 7);
    Serial.print(", ");
    Serial.println(longitude, 7);
    Serial.print("Altitude: ");
    Serial.print(altitude);
    Serial.println("m");
    Serial.print("Number of satellites: ");
    Serial.println(satellites);
    Serial.println();
}