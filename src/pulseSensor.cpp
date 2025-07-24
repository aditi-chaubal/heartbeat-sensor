#include <Arduino.h>

class pulse
{
public:

    int threshold;
    int counter = 0;
    long lastTime = 0;
    long currentTime = 0;

    bool detectBeat(int signal) 
    {
        bool status = false;
        if (signal == 550)
        {
            counter = counter + 1;
            if (counter % 2 == 0)
            {
                status = true;
                lastTime = currentTime;
                currentTime = millis();
            }
            Serial.println("signal: " + String(signal) + " Heartbeat detected"); 
        }
        return status;
    }

    int calculateBPM()
    {
        if (lastTime == 0)
        {
            return 0;
        }
        else
        {
            long timeBetween = currentTime - lastTime;
            int bpm = 60000 / timeBetween;
            return bpm;
        } 
    }
    
};