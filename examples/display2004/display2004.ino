#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h> // include i/o class header

hd44780_I2Cexp lcd; // declare lcd object: auto locate & config display for hd44780 chip

void setup()
{
  // initialize LCD with number of columns and rows:
  lcd.begin(20, 4);

  // Print a message to the LCD
  lcd.print("Hello, World!");
}

void loop()
{
  lcd.setCursor(0, 1);
  lcd.print(millis() / 1000);
  delay(1000);
}
