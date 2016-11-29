# <span style="color:#D93600">Salamander Arduino</span> ![IMAGE](salamander.png)

[**Versión en Español**] (README_ES.md)

Author:             Nanonix  
Creation Date:      12/11/2016  
Website:            [Nanonix] (http://www.nanonix.net)  
Version:            0.0.1

### Objetivos del proyecto

Los objetivos de este proyecto eran crear un aparato que pudiera ser llevado en una mochila para proveer de alguna información básica en caunto a temperatura y altitud (y la posibilidad de funciones extra más tarde) en una caja estanca, que estuviera alimentada por pilas. Además tendría que tener el potencial para que la batería se recargase mediante energía renovable. Mostraría los datos en una pantalla OLED e incorporaría un reloj.

#### Partes

Arduino Nano v3 (clon)  
BME280 Presión, temperatura y humedad (I2C)  
DTC1307 RTC (I2C)  
OLED 128x64 (I2C)
Alambre  
Placa de pruebas  
Soldadura  

#### Bibliotecas

Adafruit-GFX-Library-master  
Adafruit_SSD1306-master   	
Okti_Nanonix_BME280_I2C  
RealTimeClockDS1307-master  

#### Cosas a tener en cuenta

Cuando estaba comprobando el código para el sensor Adafruit BME280 me di cuenta de que no proveía de una lectura precisa. En su lugar, usé el de cactus.io (mi agradecimiento por su gran trabajo) y reescribí secciones del código para que mostrase la altitud. Esto puede encontrarse en el Repository. También mi BME280 estaba en la dirección 0x76 así que modifique la biblioteca Adafruit para reflejar ésta como la dirección por defecto.
