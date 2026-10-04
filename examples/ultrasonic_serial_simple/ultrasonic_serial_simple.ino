#include <NewPing.h>
 
#define  TRIGGER_PIN  7
#define  ECHO_PIN     8
#define MAX_DISTANCE 350 // Maximum sensor distance is rated at 400-500cm

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // Setup für NewPing (Pins und maximale Distanz).

int DistanceCm;
 
void setup() {
  Serial.begin(57600);
}
 
void loop()
{
  delay(100);
  DistanceCm = sonar.ping_cm();
  Serial.print("Ping: ");
  Serial.print(DistanceCm); 
  Serial.println(" cm");  
}
