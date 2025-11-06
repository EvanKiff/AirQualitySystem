// GPS sensor

#ifndef GPS_H
#define GPS_H

#include <Arduino.h>
#include <Arduino_MKRGPS.h>

class GPSModule {
public:
    GPSModule();    // Constructor
    void initialize();  // fully initialize the GPS module
    bool waitForData(); // wait for GPS data to be available
    String getDataString(); // format data as string for SD write
    void printData();       // print member variables for testing

private:
    // Member variables to hold GPS data
    float latitude;
    float longitude;
    float altitude;
    int satellites;
};

#endif // GPS_H