#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h> // include i/o class header
#include <NewPing.h>

#define  PIN_BUZZER     4
#define  PIN_TRIGGER    7
#define  PIN_ECHO       8
#define  MAX_DISTANCE  50 // Maximum distance we want to ping for (in centimeters).
                          // Maximum sensor distance is rated at 400-500cm.
int DistanceCm;

NewPing sonar(PIN_TRIGGER, PIN_ECHO, MAX_DISTANCE);

hd44780_I2Cexp lcd; // declare lcd object: auto locate & config display for hd44780 chip

void setup()
{
  lcd.begin(16, 2);
  lcd.setCursor(0,0);  
  lcd.print("T300 ultrasonic");
}

void distance() {
   DistanceCm = sonar.ping_cm(); // 10 pings per second
   lcd.setCursor(0,1);
   lcd.print("Ping: ");
   lcd.print(DistanceCm); 
   lcd.print(" cm  ");    
}

void loop()
{
  distance();
  delay(100);   // waits 100 milliseconds between pings. 29 milliseconds is the shortest delay between 2 pings
}
