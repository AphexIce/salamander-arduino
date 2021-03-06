/*********************************************************************
This is the Nanonix Salamander All Weather Display

	Using  	- Adafruit OLED Library
			- DS1307RTC
			- Nanonix BME280 library redux of Cactus.io
	
	Author	- Nanonix
	Created - 12/11/2016
	Website - http://www.nanonix.net
	License - Creative Commons Attribution, ShareAlike
				
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Okti_Nanonix_BME280_I2C.h"
#include <Time.h>
#include <DS1307RTC.h>

#define OLED_RESET 4
#define seaLevelhPa (1013.25)
#define DS1307_ADDRESS 0x57

Adafruit_SSD1306 display(OLED_RESET);

// Create the BME280 object
BME280_I2C bme;              // I2C using default 0x76 
// or BME280_I2C bme(0x77);  // I2C using address 0x77

//const char* zile[] =
// { "Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"}; //days of the week 
const char* Mon[] =
 {"Dec", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov" }; //months of the week

static const unsigned char PROGMEM dfly [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x04, 0x00, 0x00, 0x00,
0x00, 0x00, 0xCF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0xB0, 0x9B, 0x00, 0x00,
0x00, 0x00, 0xE7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1D, 0x55, 0xFB, 0x00, 0x00,
0x00, 0x00, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x55, 0x73, 0x00, 0x00,
0x00, 0x00, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x35, 0xDB, 0x00, 0x00,
0x00, 0x00, 0x7F, 0xD8, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3F, 0xF8, 0x00, 0x07, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3F, 0xF8, 0x00, 0x04, 0x70, 0x00, 0x00, 0x60, 0x00, 0x00, 0x66, 0x00, 0x00, 0x00,
0x00, 0x00, 0x1F, 0xFE, 0x00, 0x08, 0x19, 0xE0, 0x42, 0x43, 0xE6, 0x17, 0x22, 0xC3, 0x80, 0x00,
0x00, 0x00, 0x07, 0xFF, 0xE0, 0x18, 0x1F, 0x20, 0xC4, 0x04, 0x37, 0x36, 0x02, 0x70, 0x00, 0x00,
0x00, 0x00, 0x01, 0xFF, 0xFC, 0x18, 0x09, 0x20, 0x24, 0x08, 0x33, 0x92, 0x02, 0x38, 0x00, 0x00,
0x00, 0x00, 0x03, 0xFF, 0xFE, 0x18, 0x09, 0xC1, 0x2C, 0x08, 0x12, 0x92, 0x22, 0x18, 0x00, 0x00,
0x00, 0x00, 0x07, 0xBF, 0x20, 0x0C, 0x19, 0x61, 0x34, 0x2C, 0x12, 0x52, 0x02, 0x08, 0x00, 0x00,
0x00, 0x00, 0x07, 0x3F, 0x80, 0x0E, 0x11, 0x22, 0x16, 0x2C, 0x22, 0x72, 0x02, 0x08, 0x00, 0x00,
0x00, 0x00, 0x0E, 0x1F, 0xC0, 0x07, 0xE1, 0xB6, 0x1B, 0xE7, 0xC2, 0x32, 0x03, 0xC8, 0x00, 0x00,
0x00, 0x00, 0x1C, 0x0F, 0xE0, 0x00, 0x00, 0x10, 0x00, 0x20, 0x00, 0x12, 0x00, 0x08, 0x00, 0x00,
0x00, 0x00, 0x3C, 0x03, 0xE0, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x02, 0x00, 0x08, 0x00, 0x00,
0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00,
0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x08, 0x00, 0x00,
0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()   {                
  Serial.begin(9600);
  Serial.println("Bosch BME280 Barometric Pressure - Humidity - Temp Sensor | Okti Nanonix"); 

  bme.setTempCal(-1);
  Serial.println("Pressure\tHumdity\t\tTemp\t\tAltitude");


    // add a 2 second delay to slow down the output
    delay(2000);
    

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  delay(2000);
  // Clear the buffer.
  display.clearDisplay();
   // miniature bitmap display
  display.clearDisplay();
  display.drawBitmap(0, 0,  dfly, 128, 32, 1);
  display.display();
  delay (2000);
  display.clearDisplay();
}/*--(end setup )---*/

void loop() {
    Serial.print(bme.getPressure_MB()); Serial.print("\t\t");    				// Pressure in millibars
    Serial.print(bme.getHumidity()); Serial.print(" %\t\t");	  				// Humidity %
    Serial.print(bme.getTemperature_C()); Serial.print(" *C\t");				// Temp in Celsius Only
    Serial.print(bme.readAltitude(seaLevelhPa)); Serial.print(" m\t\n");		// Altitude
   readTime(); //displaying date and time
   dispBrand();
   readInfo();

}
void readInfo() {
   bme.readSensor(); 

    // add a 2 second delay to slow down the output
    delay(2000);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.clearDisplay();
    display.print("Pressure: ");display.print(bme.getPressure_MB()); display.print("mb");    			// Pressure in millibars
    display.setCursor(0, 8);
    display.print("Hum: ");display.print(bme.getHumidity()); display.print(" %");						// Humidity %
    display.setCursor(0, 16);
    display.print("Temp: ");display.print(bme.getTemperature_C()); display.print(" C");					// Temp in Celsius Only
    display.setCursor(0, 24);
    display.print("Alt: ");display.print(bme.readAltitude(seaLevelhPa)); display.print(" m");			// Altitude

    // add a 2 second delay to slow down the output
   display.display();
   delay (8000);
   display.clearDisplay();
    
}
void readTime()
{ 
  tmElements_t tm;
  (RTC.read(tm));
  Serial.print (tm.Hour);
  Serial.print (tm.Minute);
  Serial.print (tm.Day);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(32, 1);
  dispTime(tm.Hour);
  display.print(":");
  dispTime(tm.Minute);
  display.setCursor(1, 16);
  dispTime(tm.Day);
  display.print(" ");
  display.print(tm.Month[Mon]);
  display.print(" ");
  display.print(tmYearToCalendar(tm.Year)-2000);
  display.display();
   delay (8000);
   display.clearDisplay();
//  lcd.setCursor(12,1); // this code is used for displaying day of the week
//  lcd.print(tm.Wday[zile-2]); //it's disabled because for some reason it doesn't work on i2c display
}
void dispTime(int number) { //this adds a 0 before single digit numbers
  if (number >= 0 && number < 10) {
    display.write('0');
  }
  display.print(number);
}
void dispBrand() { 
   // miniature bitmap display
  display.clearDisplay();
  display.drawBitmap(0, 0,  dfly, 128, 32, 1);
  display.display();
  delay (3000);
  display.clearDisplay();
}

/* ( THE END ) */
