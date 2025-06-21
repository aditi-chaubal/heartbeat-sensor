#include <Arduino.h>

int const pulse_sensor_pin = 0;
int signal;

void setup() {
  Serial.begin(9600);
 
}

// the loop function runs over and over again forever
void loop() {
  signal = analogRead(pulse_sensor_pin);
  float time = millis();
  Serial.print(time);
  Serial.print(",");
  Serial.println(signal);
  delay(10);
}