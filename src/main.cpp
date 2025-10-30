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

void setup() {

  // initialize serial communications and wait for port to open
  Serial.begin(9600);
  while (!Serial);

  #ifdef ENABLE_GPS
  // initialize GPS
  gps.initialize();
  #endif

  #ifdef ENABLE_PMSA003I
  pmsSensor.initialize();
  #endif

}

void loop() {

  #ifdef ENABLE_GPS
  gps.standby();
  delay(10000); // wait for 10 seconds
  gps.wakeup();
  if (gps.waitForData()) {
    gps.printData();
  }
  #endif

  #ifdef ENABLE_PMSA003I
  if (pmsSensor.readData()) {
    pmsSensor.printData();
  }
  delay(1000); // wait for 1 second
  #endif
}