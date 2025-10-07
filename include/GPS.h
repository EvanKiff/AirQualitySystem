#ifndef GPS_H
#define GPS_H

#include <Arduino.h>
#include <Arduino_MKRGPS.h>

class GPSModule {
public:
    void initialize();
    void standby();
    void wakeup();
    bool waitForData();
    void printData();

private:
    float latitude;
    float longitude;
    float altitude;
    int satellites;
};

#endif