#include <Arduino.h>
#include "pulseSensor.cpp"

int const pulse_sensor_pin = 0;

void setup() 
{
  Serial.begin(9600);
 
}

// the loop function runs over and over again forever
pulse newPulse;

/*
void loop() 
{
  int signal = analogRead(pulse_sensor_pin);
  if (newPulse.detectBeat(signal) == true)
  {
    Serial.println (newPulse.calculateBPM());
  }
  
  delay(10);
  
}
*/

void loop()
{
  int signal = analogRead(pulse_sensor_pin);
  newPulse.detectBeat(signal);
}