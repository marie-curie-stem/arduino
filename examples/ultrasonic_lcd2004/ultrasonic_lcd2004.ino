#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h> // include i/o class header
#include <NewPing.h>

#define  TRIGGER_PIN  11
#define  ECHO_PIN     10
#define MAX_DISTANCE 350 // Maximum distance we want to ping for (in centimeters).
                         // Maximum sensor distance is rated at 400-500cm.

int DistanceIn;
int DistanceCm;

unsigned long time;
int days = 0;
int hours = 0;
int minutes = 0;
boolean show_uptime = false;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

hd44780_I2Cexp lcd; // declare lcd object: auto locate & config display for hd44780 chip

void setup()
{
  Serial.begin(57600);  // start serial to PC
  Serial.println("Ultrasonic Distance Measurement");  
  pinMode(13, OUTPUT); // for status LED
  // initialize LCD with number of columns and rows:
  lcd.begin(20, 4);

  // Print a message to the LCD
  lcd.setCursor(0,0);  
  lcd.print("uptime 00d 00:00:00 ");
  lcd.setCursor(0,1); 
  lcd.print("ultrasonic distance:");
}

void uptime() {
  if( millis() - time > 60000 ) { // a minute has passed!
    time = millis();
    minutes++;
    if( minutes > 60) {
      minutes = 0;
      hours++;
    }
    if( hours > 24) {
      hours = 0;
      days++;
    }
    lcd.setCursor(0, 0);
    lcd.print("up ");
    lcd.print(days);
    lcd.print("d ");
    lcd.print(hours);
    lcd.print("h ");
    lcd.print(minutes);
    lcd.print("min   ");
    show_uptime = true;
  }
  if( millis() - time < 0 ) { // rollover happened after unsigned long 4294967295 milliseconds = 49.71 days
    time = millis();
  }
  if(( millis() - time > 2500 ) && show_uptime == true) { // uptime shown for 1.5 seconds
    show_uptime = false;
    lcd.setCursor(0,0);
    lcd.print("Place your IDtag");
  }
}

void distance() {
   DistanceIn = sonar.ping_in();
   lcd.setCursor(0,2); 
   lcd.print("Ping: ");
   lcd.print(DistanceIn);  // Konvertiert die Ping Zeit in die Entfernung und gibt das Resultat über die Serielleschnittstelle zurück 
                            // (0 = outside set distance range, no ping echo)
   lcd.print(" in     ");
  
   delay(100);  // Wartet 100 Milisekunden zwischen den Pings (ca. 10 Pings pro Sekunde). 29 Millisekunden ist der kürzest mögliche Delay zwischen zwei Pings.
   DistanceCm = sonar.ping_cm();
   lcd.setCursor(0,3);
   lcd.print("Ping: ");
   lcd.print(DistanceCm); 
   lcd.print(" cm  ");    
}

void proximity() {
  // mach etwas!
}

void loop()
{
  distance();
  proximity();
  uptime();
  delay(100);   // Wartet 100 Milisekunden zwischen den Pings (ca. 10 Pings pro Sekunde). 29 Millisekunden ist der kürzest mögliche Delay zwischen zwei Pings.
}
