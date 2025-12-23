#include <Arduino.h>

class pulse
{
public:
    int threshold = 550;                 
    const long beatInterval = 300;  

    long lastTime = 0;
    long currentTime = 0;
    bool latch = false;

    bool detectBeat(int signal)
    {
        bool status = false;

        // detect a rise across threshold
        if (!latch && signal >= threshold)
        {
            currentTime = millis();

            // ignore false beats that are too close together
            if (lastTime == 0 || (currentTime - lastTime) > beatInterval)
            {
                status = true;
                latch = true;

                if (lastTime != 0)
                {
                    long timeBetween = currentTime - lastTime;
                    int bpm = 60000 / timeBetween;

                    if (bpm > 40 && bpm < 180)
                    {
                        //Serial.println("BPM: " + String(bpm));
                    }
                }

                lastTime = currentTime;
            }
        }

        // Reset latch when signal falls below threshold
        if (signal < threshold)
        {
            latch = false;
        }

        return status;
    }
};