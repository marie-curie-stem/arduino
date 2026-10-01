# arduino

![GitHub Release](https://img.shields.io/github/v/release/marie-curie-stem/arduino)
![GitHub License](https://img.shields.io/github/license/marie-curie-stem/arduino)

Vault for the initial project at Marie Curie.

## Ambient pressure with the Bosch BMP180, including temperature and relative height

Using the sensor BMP180 to measure the air pressure over I2C we display it on the 2004 display and also calculate the relative height with the barometric formulae. It looks like this:

![setup September 2026](BMP180_LCD2004/2026-09-30.jpg)

Here is the code, now 7 years old:

``` c
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h> // include i/o class header
/* First you need to include this library 
 *  Go to Sketch > Include Library > Manage Libraries...
 *  Filter your seach, enter hd44780 and install this library
 *  Connect display to SCL-SCL SDA-SDA and VCC-5V and GND-GND
 */
#include <SFE_BMP180.h>

SFE_BMP180 pressure;
hd44780_I2Cexp lcd; // declare lcd object: auto locate & config display for hd44780 chip

char status;
double T,T1,P,P1,p0,a;
int durchlauf = 0;

void setup()
{
  // initialize LCD with number of columns and rows:
  lcd.begin(20, 4);
  lcd.backlight(); 
  Wire.begin();
  lcd.setCursor(0,0);
  if (pressure.begin())
    lcd.print("BMP180 init success");
  else
  {
    // Oops, something went wrong, this is usually a connection problem,
    lcd.print("BMP180 init fail\n\n");
    while(1); // Pause forever.
  }
  for(int i=0;i<10;i++) {
  do {
    status = pressure.startTemperature();
  } while (status = 0);
  delay(100);
  do {
    status = pressure.getTemperature(T1);
  } while (status = 0);
  do {
    status = pressure.startPressure(3);
  } while (status = 0);
  delay(100);
  do {
    status = pressure.getPressure(P1,T1);
  } while (status = 0);
  p0 = P1;
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print(" Temp: ");
  lcd.print(T1,4);
  lcd.print(" 'C");
  lcd.setCursor(0,2);
  lcd.print("Druck: ");
  lcd.print(P1,3);
  lcd.print(" hPa  ");
  a = pressure.altitude(P1,p0);
  lcd.setCursor(0,3);
  lcd.print("Hoehe: ");
  lcd.print(a,3);
  lcd.print(" m  ");
  delay(100);
  }
}

void loop()
{
  status = pressure.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:
    delay(status);

    // Retrieve the completed temperature measurement:
    // Note that the measurement is stored in the variable T.
    // Function returns 1 if successful, 0 if failure.

    status = pressure.getTemperature(T);
    if (status != 0)
    {
      lcd.setCursor(0,0);
      lcd.print("Bosch BMP180 Sensor");
      
      // Start a pressure measurement:
      // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
      // If request is successful, the number of ms to wait is returned.
      // If request is unsuccessful, 0 is returned.

      status = pressure.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        // Retrieve the completed pressure measurement:
        // Note that the measurement is stored in the variable P.
        // Note also that the function requires the previous temperature measurement (T).
        // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
        // Function returns 1 if successful, 0 if failure.

        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          // Durchschnitt aus 3 Durchläufen
          T1 = 0.9*T1 + 0.1*T;
          P1 = 0.9*P1 + 0.1*P;
          if (durchlauf > 15)
          {
            durchlauf = 0;
            // Print out the measurement:
            lcd.setCursor(0,1);
            lcd.print(" Temp: ");
            lcd.print(T1,4);
            lcd.print(" 'C  ");
            lcd.setCursor(0,2);
            lcd.print("Druck: ");
            lcd.print(P1,3);
            lcd.print(" hPa  ");
            a = pressure.altitude(P1,p0);
            lcd.setCursor(0,3);
            lcd.print("Hoehe: ");
            lcd.print(a,3);
            lcd.print(" m  ");
          }
          durchlauf++;
        }
        else lcd.print("error retrieving pressure measurement\n");
      }
      else lcd.print("error starting pressure measurement\n");
    }
    else lcd.print("error retrieving temperature measurement\n");
  }
  else lcd.print("error starting temperature measurement\n");

  delay(100);  // Pause for 0.1 seconds.
}
```

Vidar code just entered this repository for a change!
