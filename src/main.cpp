#include <Arduino.h>
#include "config.h"

#ifdef ENABLE_GPS
#include "mkr_gps.h"
GPSModule gps;
#endif

#ifdef ENABLE_PMSA003I
#include "pmsa003i.h"
PMSA003I pmsSensor;
#endif

#ifdef ENABLE_SCD40
#include "scd40.h"
SCD40 scdSensor;
#endif

#ifdef ENABLE_SD
#include "sd_manager.h"
SDManager sdManager;
#endif

void setup() {

  // initialize serial communications and wait for port to open
  Serial.begin(9600);
  while (!Serial);

  #ifdef ENABLE_GPS
  // initialize GPS and setup working power state
  gps.initialize();
  #endif

  #ifdef ENABLE_PMSA003I
  pmsSensor.initialize();
  #endif

  #ifdef ENABLE_SCD40
  scdSensor.initialize();
  #endif

  #ifdef ENABLE_SD
  sdManager.initialize();
  #endif

}

void loop() {

  String dataLine = "";

  #ifdef ENABLE_GPS
  if (gps.waitForData()) {
    dataLine += gps.getDataString();
    gps.printData();
  }
  #endif

  #ifdef ENABLE_SCD40
  if (scdSensor.readData()) {
    dataLine += "," + scdSensor.getDataString();
    scdSensor.printData();
  }
  #endif

  #ifdef ENABLE_PMSA003I
  if (pmsSensor.readData()) {
    dataLine += "," + pmsSensor.getDataString();
    pmsSensor.printData();
  }
  #endif

  #ifdef ENABLE_SD
  sdManager.writeLine(dataLine);  // Write the data collected to a new line on the SD card file
  sdManager.printFile();
  #endif

  delay(20000); // wait for 20 seconds
  
}