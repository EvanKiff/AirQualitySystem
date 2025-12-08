#include <Arduino.h>
#include "config.h"
#include <WiFiNINA.h>
#include <WiFiUdp.h>

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

const char* WIFI_SSID = "iPhone";
const char* WIFI_PASS = "testing123";

// IP address of computer
IPAddress DEST_IP(172, 20, 10, 4);

// UDP port to send to
const uint16_t DEST_PORT = 5005;

WiFiUDP udp;

// wifi connection helper function
void connectToWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  // Block until connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void setup() {
  // Initialize wifi and udp
  connectToWiFi();
  udp.begin(DEST_PORT);
  udp.beginPacket(DEST_IP, DEST_PORT);
  udp.write("Wifi connected");
  udp.endPacket();

  #ifdef ENABLE_GPS
  // initialize GPS and setup working power state
  gps.initialize();
  #endif

  udp.beginPacket(DEST_IP, DEST_PORT);
  udp.write("GPS initialized");
  udp.endPacket();

  #ifdef ENABLE_PMSA003I
  // initialize air particulate sensor
  pmsSensor.initialize();
  #endif

  #ifdef ENABLE_SCD40
  // initialize temp, humidity, and co2 sensor
  scdSensor.initialize();
  #endif
}

void loop() {
  // dataline that will be sent
  String dataLine = "";

  #ifdef ENABLE_GPS
  if (gps.waitForData()) {
    // add gps data to the data line
    dataLine += gps.getDataString();
  }
  #endif

  #ifdef ENABLE_SCD40
  if (scdSensor.readData()) {
    // add scd40 data to the data line
    dataLine += "," + scdSensor.getDataString();
  }
  #endif

  #ifdef ENABLE_PMSA003I
  if (pmsSensor.readData()) {
    // add pmsa003i data to the data line
    dataLine += "," + pmsSensor.getDataString();
  }
  #endif

  // If wifi dropped, reconnect
  if (WiFi.status() != WL_CONNECTED) {
    connectToWiFi();
  }

  // Send data line via udp
  udp.beginPacket(DEST_IP, DEST_PORT);
  udp.write(dataLine.c_str());
  udp.endPacket();

  delay(10000); // wait for 10 seconds
}
