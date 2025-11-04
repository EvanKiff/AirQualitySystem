#ifndef SD_MANAGER_H
#define SD_MANAGER_H

#include <Arduino.h>
#include <SD.h>

class SDManager {
public:
    SDManager(); // Constructor
    void initialize(); // Initialize the SD card
    void writeLine(const String& line); // Write a line to the SD card file
    void printFile(); // Print the contents of the file to Serial Monitor

private:
    const char* filename = "data.txt"; // Name of the file on the SD card
};

#endif // SD_MANAGER_H