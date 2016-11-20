# <span style="color:#D93600">Salamander Arduino</span> ![IMAGE](salamander.png)

[**Versión en Español**] (README_ES.md)

Author:             Nanonix  
Creation Date:      12/11/2016  
Website:            [Nanonix] (http://www.nanonix.net)  
Version:            0.0.1

### Project Aims

The aims of this project were to create a device which could be worn on a backpack to provide some basic information regarding temperature and altitude (and the possibility of extra functions later) in a waterproof enclosure, which is battery powered. In addition to this it would have to have the potential for the battery to be recharged via renewable energy. This would display the data on an OLED screen and incorporate a clock.

#### Parts

Arduino Nano v3 (clone)  
BME280 Pressure, Temp and Humidity (I2C)  
DTC1307 RTC (I2C)  
OLED 128x64 (I2C)
Wire  
Prefboard  
Solder  

#### Libraries

Adafruit-GFX-Library-master  
Adafruit_SSD1306-master   	
Okti_Nanonix_BME280_I2C  
RealTimeClockDS1307-master  

#### Things to note

When originally testing the code for the adafruit BME280 sensor I found that it did not provide and accurate reading, I instead used the one from cactus.io (with thanks for all the hardwork) and rewrote sections of it to display the altitude. This can be found on the repository. Also my BME280 was on address 0x76 so I modified the adafruit library to reflect this as the default address.
