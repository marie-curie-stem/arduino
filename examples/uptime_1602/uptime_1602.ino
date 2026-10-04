// function uptime() returns a string with the time the arduino is running.
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h> // include i/o class header

unsigned long time_ms; // runs over after 4294967295 milliseconds or 49days 17:02:47.295
unsigned long runtime; // seconds this system actually runs, good for 1193046 hours 
int rollover = 0; //      or 49710 days or 136 years

hd44780_I2Cexp lcd; // declare lcd object:

String uptime() {
  if( millis() < time_ms ) { // rollover happened after unsigned long 4294967295 milliseconds = 49.71 days
    rollover++;
    time_ms = millis();
  }
  runtime = 4294967*rollover + time_ms/1000; // divided by 1000 since runtime is seconds and time_ms is milliseconds
  long  days = runtime / 86400;
  long hours = (runtime - days*86400) / 3600;
  int minutes = (runtime - days*86400 - hours*3600) / 60;
  int seconds = (runtime - days*86400 - hours*3600 - minutes*60);
  String upt = "up ";
  upt += days;
  upt += "d " + twodig(hours) + ":" + twodig(minutes) +  ":" + twodig(seconds) + " ";
  time_ms = millis();
  return upt;
}

String twodig (int number) {
  String t2dig = "";
  if (number < 10) { t2dig = "0"; }
  t2dig += number;
  return t2dig;
}

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);  
  lcd.print("up 00d 00:00:00 ");
}

void loop() {
  Serial.println( uptime() );
  lcd.setCursor(0,0);
  lcd.print( uptime() );
  lcd.setCursor(0,1);
  lcd.print( runtime );
  delay(1234);
}
