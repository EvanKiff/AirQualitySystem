#include "sd_manager.h"

//Constructor
SDManager::SDManager() {}

// Initialize SD card
void SDManager::initialize() {
    if (!SD.begin()) {
        Serial.println("Initialization of SD card failed!");
        return;
    }
    Serial.println("SD card initialized.");
}

// Write a line to the SD card file
void SDManager::writeLine(const String& line){
    File dataFile = SD.open(filename, FILE_WRITE);      // open file for writing
    if (dataFile) {
        dataFile.println(line);     // Write line to the file
        dataFile.close();           // Close file
        Serial.println("Data written to SD card.");
    } else {
        Serial.println("Error opening file on SD card.");
    }
}

// Print the contents of the file to Serial Monitor
void SDManager::printFile(){
    File dataFile = SD.open(filename);      // open file for reading
    if (dataFile) {
        Serial.println("Contents of SD card file:");
        while (dataFile.available()) {
            Serial.write(dataFile.read()); // Read and print each character
        }
        dataFile.close(); // Close file
    } else {
        Serial.println("Error opening file on SD card.");
    }
}