# AirQualitySystem
A complete embedded system strapped to a drone, and deployed into the rainforest to collect vital air quality data. Data is saved onto an SD card for later analysis.

Needed Metrics:
- Latitude, Longitude, and Altitude
- CO₂ in ppm
- Temperature in °C
- Humidity as a percentage
- PM 1.0 : Particules with diameter of <= 1.0 um
- PM 2.5 : Particles with diameter of <= 2.5 um
- PM 10.0 : Particles with diameter of <= 10 um

---

## Features

- **MKR_GPS Arduino Shield Module**: Tracks the drone's location (latitude, longitude, altitude).
- **PMSA003I Sensor**: Measures particulate matter (PM1.0, PM2.5, PM10.0) in `µg/m³`.
- **SCD40 Sensor**: Measures CO₂ concentration (ppm), temperature (°C), and humidity (%).
- **MH-SD Card Module**: Stores all sensor data in a structured format for offline analysis.
- **Modular Design**: Easily enable or disable sensors via configuration.

---

## System Architecture

### Sensors and Components
- **GPS Module**: Arduino MKR GPS Shield
- **Particulate Matter Sensor**: Adafruit PMSA003I via I2C
- **CO₂, Temperature, and Humidity Sensor**: Adafruit SCD40 via I2C
- **MH-SD Card Module**: Standard SPI-based SD card module

### Workflow
1. **Initialization**: All sensors and the SD card module are initialized.
2. **Data Collection**: Sensors collect data at a regular interval (about 20s).
3. **Data Logging**: Sensor data is written to the SD card in a structured format.

SD Card Line Format:
```<latitude>, <longitude>, <altitude>, <CO₂>, <temperature>, <humidity>, <PM1.0>, <PM2.5>, <PM10.0>```

---

## File Structure

```plaintext
AirQualitySystem/
├── include/
│   ├── config.h          # Configuration file for enabling/disabling sensors
│   ├── mkr_gps.h         # GPS module header
│   ├── pmsa003i.h        # PMSA003I sensor header
│   ├── scd40.h           # SCD40 sensor header
│   └── sd_manager.h      # SD card manager header
├── lib/
│   └── SPI/              # SPI library (manually added)
├── src/
│   ├── main.cpp          # Main system logic
│   ├── mkr_gps.cpp       # GPS module implementation
│   ├── pmsa003i.cpp      # PMSA003I sensor implementation
│   ├── scd40.cpp         # SCD40 sensor implementation
│   └── sd_manager.cpp    # SD card manager implementation
├── platformio.ini        # PlatformIO project configuration
└── README.md             # Project documentation
