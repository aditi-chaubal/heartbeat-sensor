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

  // send variables to python code
  Serial.print(signal);
  Serial.print(",");
  Serial.println(tov);

 // detect heartbeat and ouput BPM
  newPulse.detectBeat(signal);
  
  //delay(300); //refractory period
}