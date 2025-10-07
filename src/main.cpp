#include <Arduino.h>
#include "GPS.h"

GPSModule gps;

void setup() {

  // initialize serial communications and wait for port to open
  Serial.begin(9600);
  while (!Serial);

  // initialize GPS
  gps.initialize();

}

void loop() {

  gps.standby();
  delay(10000); // wait for 10 seconds
  gps.wakeup();
  if (gps.waitForData()) {
    gps.printData();
  }
}