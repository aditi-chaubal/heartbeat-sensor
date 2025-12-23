#include <Arduino.h>
#include "pulseSensor.cpp"

int const pulse_sensor_pin = 0;

unsigned long startTime;
unsigned long tov;

void setup()
{
  Serial.begin(9600);
  startTime = millis();
 
}

// the loop function runs over and over again forever
pulse newPulse;


void loop() 
{
  int signal = analogRead(pulse_sensor_pin);
  tov = millis() - startTime;

  bool beat = newPulse.detectBeat(signal);
  

  // send variables to python code
  Serial.print(signal);
  Serial.print(",");
  Serial.print(tov);
  Serial.print(",");
  Serial.println(beat ? 1 : 0);

}