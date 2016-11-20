/***************************************************************************
  This is a library for the BME280 humidity, temperature & pressure sensor
  Designed specifically to work with the BME280 Breakout board
  ----> http://www.adafruit.com/products/2650
  This sketch only supports the I2C bus for connection.
 ***************************************************************************/

#include <Wire.h>
#include "Okti_Nanonix_BME280_I2C.h"

#define seaLevelhPa (1013.25)

// Create the BME280 object
BME280_I2C bme;              // I2C using default 0x77 
// or BME280_I2C bme(0x76);  // I2C using address 0x76

void setup() {
  Serial.begin(9600);
  Serial.println("Bosch BME280 Barometric Pressure - Humidity - Temp Sensor | Okti Nanonix"); 

  if (!bme.begin()) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  bme.setTempCal(-1);
  
  Serial.println("Pressure\tHumdity\t\tTemp\t\tAltitude");
  
}

void loop() {

    bme.readSensor(); 
  
    Serial.print(bme.getPressure_MB()); Serial.print("\t\t");    // Pressure in millibars
    Serial.print(bme.getHumidity()); Serial.print(" %\t\t");
    Serial.print(bme.getTemperature_C()); Serial.print(" *C\t");
    Serial.print(bme.readAltitude(seaLevelhPa)); Serial.print(" m\t\n");

    // add a 2 second delay to slow down the output
    delay(2000);
}
