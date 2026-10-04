#include <LiquidCrystal_I2C.h>
#include <NewPing.h>

#define  PIN_BUZZER     4
#define  PIN_TRIGGER    7
#define  PIN_ECHO       8
#define  MAX_DISTANCE 350 // Maximum distance we want to ping for (in centimeters).
                          // Maximum sensor distance is rated at 400-500cm.
int DistanceCm;

NewPing sonar(PIN_TRIGGER, PIN_ECHO, MAX_DISTANCE);

LiquidCrystal_I2C lcd(0x27,16,2);

void setup()
{
  lcd.init();
  lcd.backlight();
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
